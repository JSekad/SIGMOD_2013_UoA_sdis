#include "../include/core.h"
#include <cstring>
#include <cstdlib>
#include <cstdio>


#include "../../../include/scheduler.h"
#include "../../../include/query.h"
#include "../../../include/doc.h"
#include "../../../include/vector.h"
#include "../../../include/bktree.h"
#include "../../../include/distance.h"
#include "../../../include/hashTable.h"

#include "../../../include/entry_list.h"


#include <unistd.h>


vector *queries;
vector *documents;
hashTable *exactMatchTable;
node *bkTreeForEdit;
vector* bkTreesForHamming;
vector* results;
int currentDoc=0;
tpool_t *pool,*pool2;

//pthread_barrier_t   barrier; // the barrier synchronization object
pthread_mutex_t  mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex3 = PTHREAD_MUTEX_INITIALIZER;

Entry_list * ResultList=NULL;
Entry_list *ResultList2=NULL;
Entry_list *ResultList3=NULL;


struct arg_struct_exact{

    hashTable *exactMatchTable;
    Entry_list *list_of_words;
//    Entry_list *ResultList;

};

struct arg_struct_edit{
    node* bkTreesForEdit;
    Entry_list *list_of_words;
    //   Entry_list *ResultList;
};




struct arg_struct_hamming{
    vector* bkTreesForHamming;
    Entry_list *list_of_words;
    //   Entry_list *ResultList;
};





struct argument{
    int doc_id;
    char *doc_str;
};


struct returnStruct{
    ErrorCode code;
};


struct returnStruct *res;




using namespace std;

ErrorCode InitializeIndex(){

    res=(struct returnStruct*)malloc(sizeof(struct returnStruct));
//    pthread_barrier_init (&barrier, NULL, 3);
    pool2=tpool_create(3);
    void *ok = NULL;
    queries =(vector*) malloc(sizeof(vector));
    vector_init(queries,STARTING_VERTORS_CAPACITY);
    documents =(vector*) malloc(sizeof(vector));
    vector_init(documents,STARTING_VERTORS_CAPACITY);
    // printf("Initial Index\n");

    exactMatchTable = CreateHashTable();
    bkTreeForEdit = NULL;
    bkTreesForHamming=(vector*)malloc(sizeof(vector));
    vector_init(bkTreesForHamming,27);

    // printf("Initial Index\n");

    for(int i=0;i<27;i++){
        vectorPushBack(bkTreesForHamming,ok);
    }
    results=(vector*)malloc(sizeof(vector));
    vector_init(results,STARTING_VERTORS_CAPACITY);
    // printf("\nEXITING Index\n");
    return EC_SUCCESS;
}


ErrorCode DestroyIndex(){
    for(int i=0;i<queries->total;i++){
        destroyQuery((query*)queries->items[i]);
    }
    vectorFree(queries);
    for(int i=0;i<bkTreesForHamming->total;i++){
        node * n= (node *)bkTreesForHamming->items[i];
        delete_tree2(n);
    }
    vectorFree(bkTreesForHamming);
    for(int i=0;i<results->total;i++){
        result * n= (result *)results->items[i];
        destroyResult(n);
    }
    vectorFree(results);
    for(int i=0;i<documents->total;i++){
        doc * n= (doc *)documents->items[i];
        DestroyDoc(n);
    }
    vectorFree(documents);
    DestroyHashTable(exactMatchTable);
//    tpool_wait(pool2);
    //sleep(4);
    printf("IAM SLEEPING\n");
    tpool_destroy(pool2);
    return EC_SUCCESS;
}


ErrorCode StartQuery(QueryID query_doc_id, const char* query_str, MatchType match_type, unsigned int match_dist)
{
    //printf("%s %d\n",query_str,match_type);
    // printf("IN START QUERRY \n");


    query *q;
    result *r;
    size_t len;
    /***CONST TO DYNAMIC***/
    char* tempWord = (char*)malloc(sizeof (char)*(strlen(query_str)+1));
    strcpy(tempWord,query_str);

    //IF EXACT MATCH
    if (match_type==MT_EXACT_MATCH){

        initQuery(&q,query_doc_id,0,match_dist,tempWord);
        initResult(&r,query_doc_id,q->numOfWords);
        entry* temp = getFirstEntryOfList(q->words);
        insertEntry(exactMatchTable,*temp,UPDATE);
        temp=getNextEntryOfList(q->words);
        while(temp!=NULL){
            insertEntry(exactMatchTable,*temp,UPDATE);
            temp=getNextEntryOfList(q->words);
        }
        vectorPushBack(results,r);
        vectorPushBack(queries,q);
        free(tempWord);
        //      printf("EXITING  QUERRY WITH SUCCESS \n");


        return EC_SUCCESS;
        //IF HAMMING MULTIPLE TREES
    }else if(match_type==MT_HAMMING_DIST){
        initQuery(&q,query_doc_id,1,match_dist,tempWord);
        initResult(&r,query_doc_id,q->numOfWords);
        entry* temp = getFirstEntryOfList(q->words);
        len=strlen((*temp)->w);
        // printf("in trees asking for vector\n");
        node *bkTreeForHamming= (node*) vectorGet(bkTreesForHamming,(int)len-4);

        add_node(&bkTreeForHamming,(*temp)->w,temp,HAMMING_DIST);
        vectorSet(bkTreesForHamming,(int)len-4,bkTreeForHamming);
        temp=getNextEntryOfList(q->words);
        while(temp!=NULL){
            len=strlen((*temp)->w);
            bkTreeForHamming= (node*) vectorGet(bkTreesForHamming,(int)len-4);
            add_node(&bkTreeForHamming,(*temp)->w,temp,HAMMING_DIST);
            vectorSet(bkTreesForHamming,(int)len-4,bkTreeForHamming);
            temp=getNextEntryOfList(q->words);
        }


        vectorPushBack(results,r);
        vectorPushBack(queries,q);
        free(tempWord);
        //  printf("EXITING  QUERRY WITH SUCCESS \n");
        return EC_SUCCESS;
        //IF EDIT
    }else if(match_type==MT_EDIT_DIST) {

        initQuery(&q,query_doc_id,2,match_dist,tempWord);
        initResult(&r,query_doc_id,q->numOfWords);
        entry* temp = getFirstEntryOfList(q->words);
        add_node(&bkTreeForEdit,(*temp)->w,temp,EDIT_DIST);
        temp=getNextEntryOfList(q->words);
        while(temp!=NULL){
            add_node(&bkTreeForEdit,(*temp)->w,temp,EDIT_DIST);
            temp=getNextEntryOfList(q->words);
        }
        vectorPushBack(results,r);
        vectorPushBack(queries,q);
        free(tempWord);
        //  printf("EXITING  QUERRY WITH SUCCESS \n");


        return EC_SUCCESS;

    }else {

        //  printf("EXITING  QUERRY WITH FAIL \n");

        return EC_FAIL;
    }

    free(tempWord);

}

ErrorCode EndQuery(QueryID query_doc_id)
{

    query * q=(query *)vectorGet(queries,(int)query_doc_id-1);
    if(q->idNumber==(int)query_doc_id){
        q->flag=0;
        vectorSet(queries,(int)query_doc_id-1,q);
    }
    return EC_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////////////////////


void   MatchDocumentEdit(void *arg){

    // ResultList3=CreateEntryList();
    //printf("In MatchDocumentEdit Start\n");

    struct NodeTag *e=(((arg_struct_edit*)arg)->list_of_words)->first;

    while  (e!=NULL){


        for (int threshold = 1; threshold < 4; threshold++) {
            //  pthread_mutex_lock(&m3);

            get_words_sub(&ResultList3, &bkTreeForEdit, e->w, threshold, EDIT_DIST);

            //   pthread_mutex_unlock(&m3);

        }

        e=e->next;
        // printf("\nprint entry  %s\n",(*e)->w);
        // e=getNextEntryOfList(((arg_struct_edit*)arg)->list_of_words);
    }


    //printf("\n EXIT EDIT \n");

    //  printf("Match DocumentEdit\n");

    //  return ResultList3;


}







void  MatchDocumentHamming(void *arg){



    //printf("In MatchDocumentHamming Start\n");
   // PrintEntryList(((arg_struct_hamming*)arg)->list_of_words);

    struct NodeTag* e=(((arg_struct_hamming* )arg)->list_of_words)->first;
    // ResultList2=CreateEntryList();

    //ResultList2=CreateEntryList();
    while  (e!=NULL){
        //printf("next entry before Exists   in MatchDocumenthashTable ------ %s\n",e->w);
        size_t len;
        len=strlen(e->w);
        node *bkTreeForHamming= (node*)vectorGet(bkTreesForHamming,(int)len-4);
        if(bkTreeForHamming!=NULL) {
            for (int threshold = 1; threshold < 4; threshold++) {
                // pthread_mutex_lock(&m3);

                get_words_sub(&(ResultList2), &bkTreeForHamming, e->w, threshold, HAMMING_DIST);
                //  pthread_mutex_unlock(&m3);

            }
        }
        e=e->next;
        // e=getNextEntryOfList(((arg_struct_hamming*)arg)->list_of_words);
    }
    //PrintEntryList(ResultList2);

    //printf("\n EXIT HAM \n");

    // return ResultList2;


}


void  MatchDocumentHashTable(void * arg){



    //  sleep(1);
    //  ResultList=CreateEntryList();

    //printf("\nIn MatchDocumentHashTable Start\n");

    //PrintEntryList(((arg_struct_exact*)arg)->list_of_words);

    struct NodeTag *e=(((arg_struct_exact* )arg)->list_of_words)->first;
//    printf("e in MatchDocument %s\n",e->w);
    while  (e!=NULL){

        entry *cure=Exists(exactMatchTable,e->w);

        if (cure!=NULL){

            InsertLastEntryList(ResultList,*cure);

            changePayloadThreshHold(&(ResultList->last->payload),0);

        }
        e=(e)->next;

       // if (e!=NULL)  PrintEntryList(ResultList);
    }

    //printf("\n EXIT HASH \n");
//   printf("\nExiting MatchDocumentHashTable \n");
    //PrintEntryList(ResultList);
//    printf("\nalready printed the list\n");
    //  return ResultList;

}






ErrorCode MatchDocument(DocID doc_id, const char* doc_str)
{   //printf("\nIn MatchDocument\n");

    // pthread_mutex_lock(&mutex1);
    sort_list sl=NULL;
    ids * tempid=NULL;
    query* q=NULL;
    result* r=NULL;
//    node *bkTreeForHamming;
    ResultList=CreateEntryList();
    ResultList2=CreateEntryList();
    ResultList3=CreateEntryList();


//      char* tempWord = (char*)malloc(sizeof (char)*(strlen(((struct argument*)arg)->doc_str)+1));
//      strcpy(tempWord,((struct argument*)arg)->doc_str);
//     doc* d = initializedoc(((struct argument*)arg)->doc_doc_id,tempWord);



    arg_struct_doc *docarg=(arg_struct_doc*)malloc(sizeof(arg_struct_doc));
    docarg->id= doc_id;


    // char *tempWord=(char*)malloc(sizeof(char)*(strlen(doc_str))+1);
    // char *tempWord2=(char*)malloc(sizeof(char)*(strlen(((argument*)arg)->doc_str))+1);
    // char *tempWord3=(char*)malloc(sizeof(char)*(strlen(((argument*)arg)->doc_str))+1);

    // strcpy(tempWord,doc_str);
    // strcpy(tempWord2,((argument*)arg)->doc_str);
    // strcpy(tempWord3,((argument*)arg)->doc_str);

    docarg->wordsofdoc = (char*)malloc(sizeof (char)*(strlen((doc_str))+1));
    strcpy(docarg->wordsofdoc,doc_str);

    doc* d=(doc*)initializedoc(docarg->id,docarg->wordsofdoc);

//    printf("d1 list of words\n");
//    PrintEntryList((Entry_list*)d->list_of_words);
//    printf("d2 list of words\n");
//    PrintEntryList((Entry_list*)d2->list_of_words);
//    printf("d3 listof words\n");
//    PrintEntryList((Entry_list*)d3->list_of_words);

    arg_struct_exact *exarg=(arg_struct_exact*)malloc(sizeof(arg_struct_exact));
    arg_struct_hamming *hamarg=(arg_struct_hamming*)malloc(sizeof(arg_struct_hamming));
    arg_struct_edit *editarg=(arg_struct_edit*)malloc(sizeof(arg_struct_edit));

    exarg->exactMatchTable=exactMatchTable;
    exarg->list_of_words=d->list_of_words;
    // exarg->ResultList=CreateEntryList();

    //  PrintEntryList(d->list_of_words);

    hamarg->bkTreesForHamming=bkTreesForHamming;
    hamarg->list_of_words=d->list_of_words;
    //  hamarg->ResultList=CreateEntryList();

//PrintEntryList(d->list_of_words);


    editarg->bkTreesForEdit=bkTreeForEdit;
    editarg->list_of_words=d->list_of_words;
    // editarg->ResultList=CreateEntryList();



    tpool_add_work(pool2,MatchDocumentHashTable,exarg);


    tpool_add_work(pool2,MatchDocumentHamming,hamarg);

    tpool_add_work(pool2,MatchDocumentEdit,editarg);

    //printf("before poool wait \n");


    pthread_mutex_lock(&(pool2->work_mutex));
    pthread_cond_wait(&(pool2->working_cond), &(pool2->work_mutex));
    pthread_mutex_unlock(&(pool2->work_mutex));


//    pthread_barrier_wait (&barrier);

    //printf("after poool wait \n");

//       PrintEntryList(ResultList2);
//      PrintEntryList(ResultList3);

    appendList(&ResultList,&ResultList2);
    appendList(&ResultList,&ResultList3);

    //PrintEntryList(ResultList);
//    printf("After second Appending List \n");
//    PrintEntryList(ResultList);

    //FIND THE RESULTS OF DOCUMENT AND PARSE IT IN THE STRUCT
    entry *e=NULL;
    sl=CreateSortList();

    if(ResultList->numOfNodes>0) {
        e = getFirstEntryOfList(ResultList);
        while (e != NULL) {
            if ((*e)->payload == NULL) {
                printf("NULL\n");
            }

            tempid = getFirstIdOfPayload((*e)->payload);
            while(tempid!=NULL){
                q = (query *) vectorGet(queries, tempid->idnumber-1);

                if (q->idNumber == tempid->idnumber
                    && q->flag == 1
                    && q->distance == (*e)->payload->thresholdFount
                    && q->matchTypeId == (*e)->payload->matchtype) {
                    r = (result *) vectorGet(results, tempid->idnumber-1);


                    int ccounter0=0;
                    for(int j=0;j<r->numOfWods;j++){
                        ccounter0=ccounter0+r->words[j];
                    }
                    if(ccounter0!=r->numOfWods) {
                        InsertNonsortedInList(sl,(unsigned int) tempid->idnumber);
                        int wordcount = 0;
                        ent *temp = q->words->first;
                        while (temp != NULL) {
                            if (!strcmp(temp->w, (*e)->w)) {
                                r->words[wordcount] = 1;
                            }
                            temp = temp->next;
                            wordcount++;
                        }
                        int ccounter = 0;
                        for (int j = 0; j < r->numOfWods; j++) {
                            ccounter = ccounter + r->words[j];
                        }
                        if (ccounter == r->numOfWods) {
                            InsertSortedInList(d->qIdResults,(unsigned int) tempid->idnumber);
                        }
                        vectorSet(results, tempid->idnumber - 1, r);
                    }
                }
                tempid=getNextIdOfPayload((*e)->payload);
            }
            e = getNextEntryOfList(ResultList);
        }


        vectorPushBack(documents,d);

        rec* temprec =sl->first;
        while (temprec != NULL) {
            r = (result *) vectorGet(results, temprec->id-1);
            for(int j=0;j<r->numOfWods;j++){
                r->words[j]=0;
            }
            vectorSet(results, temprec->id - 1, r);

            temprec=temprec->next;
        }

        DestroySortList(&sl);
    }else{
//        vectorPushBack(d->qIdResults, NULL);

        return EC_FAIL;
    }
    DestroyEntryList(&ResultList);

    return EC_SUCCESS;
}


// ErrorCode MatchDocument(DocID doc_doc_id, const char* doc_str)
// {

//   //printf("\nInto  Match Document\n\n");

//     struct argument *arg=(struct argument*)malloc(sizeof(struct argument));
//     //res=(struct returnStruct*)malloc(sizeof(struct returnStruct));

//     arg->doc_id=doc_doc_id;
//     arg->doc_str = (char*)malloc(sizeof (char)*(strlen(doc_str)+1));
//     strcpy(arg->doc_str,doc_str);

//     MatchDocument2()




//     //doc_doc_id=arg->doc_doc_id;

//     //sleep(1);
//     //struct returnStruct* current=res;
//    //free(arg);
//     //free(current);


//     // sleep(1);
//   //   printf("exiting Matchdocument with code %d\n",res->code);

//     //tpool_wait(scheduler);

//      return res->code;

//    //return EC_SUCCESS;
// }





///////////////////////////////////////////////////////////////////////////////////////////////


ErrorCode GetNextAvailRes(DocID* p_doc_id, unsigned int* p_num_res, QueryID** p_query_ids)
{
    unsigned int* temp=NULL;
    unsigned int temp2;
    doc* d = (doc*)vectorGet(documents,currentDoc);
    *p_doc_id= (unsigned int)d->docid;

    *p_num_res=(unsigned int)d->qIdResults->total;
    temp=(unsigned int*)malloc(sizeof(unsigned int)*(d->qIdResults->total));
    int i = 0;
    rec* temprec = d->qIdResults->first;
    while(temprec!=NULL){
        temp[i]=temprec->id;
        temprec=temprec->next;
        i++;
    }
    *p_query_ids=temp;
    currentDoc++;
    return EC_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////////////////////
