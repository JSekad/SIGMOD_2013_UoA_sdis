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



Entry_list * ResultList=NULL;
Entry_list *ResultList2=NULL;
Entry_list *ResultList3=NULL;


struct arg_struct_exact{

    hashTable *exactMatchTable;
    Entry_list *list_of_words;


};

struct arg_struct_edit{
    node* bkTreesForEdit;
    Entry_list *list_of_words;

};




struct arg_struct_hamming{
    vector* bkTreesForHamming;
    Entry_list *list_of_words;

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
    pool2=tpool_create(2);
    void *ok = NULL;
    queries =(vector*) malloc(sizeof(vector));
    vector_init(queries,STARTING_VERTORS_CAPACITY);
    documents =(vector*) malloc(sizeof(vector));
    vector_init(documents,STARTING_VERTORS_CAPACITY);

    exactMatchTable = CreateHashTable();
    bkTreeForEdit = NULL;
    bkTreesForHamming=(vector*)malloc(sizeof(vector));
    vector_init(bkTreesForHamming,27);

    for(int i=0;i<27;i++){
        vectorPushBack(bkTreesForHamming,ok);
    }
    results=(vector*)malloc(sizeof(vector));
    vector_init(results,STARTING_VERTORS_CAPACITY);
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

    tpool_destroy(pool2);
    return EC_SUCCESS;
}


ErrorCode StartQuery(QueryID query_doc_id, const char* query_str, MatchType match_type, unsigned int match_dist)
{

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

        return EC_SUCCESS;

    }else if(match_type==MT_HAMMING_DIST){
        initQuery(&q,query_doc_id,1,match_dist,tempWord);
        initResult(&r,query_doc_id,q->numOfWords);
        entry* temp = getFirstEntryOfList(q->words);
        len=strlen((*temp)->w);

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

        return EC_SUCCESS;
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

        return EC_SUCCESS;

    }else {

        return EC_FAIL;
    }

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
    struct NodeTag *e=(((arg_struct_edit*)arg)->list_of_words)->first;
    while  (e!=NULL){
        for (int threshold = 1; threshold < 4; threshold++) {
            get_words_sub(&ResultList3, &bkTreeForEdit, e->w, threshold, EDIT_DIST);
        }
        e=e->next;
    }
}


void  MatchDocumentHamming(void *arg){
    struct NodeTag* e=(((arg_struct_hamming* )arg)->list_of_words)->first;

    while  (e!=NULL){
        size_t len;
        len=strlen(e->w);
        node *bkTreeForHamming= (node*)vectorGet(bkTreesForHamming,(int)len-4);
        if(bkTreeForHamming!=NULL) {
            for (int threshold = 1; threshold < 4; threshold++) {
                get_words_sub(&(ResultList2), &bkTreeForHamming, e->w, threshold, HAMMING_DIST);
            }
        }
        e=e->next;
    }
}


void  MatchDocumentHashTable(void * arg){

    struct NodeTag *e=(((arg_struct_exact* )arg)->list_of_words)->first;

    while  (e!=NULL){

        entry *cure=Exists(exactMatchTable,e->w);

        if (cure!=NULL){

            InsertLastEntryList(ResultList,*cure);
        }
        e=(e)->next;

    }

}

ErrorCode MatchDocument(DocID doc_id, const char* doc_str)
{
    sort_list sl=NULL;
    ids * tempid=NULL;
    query* q=NULL;
    result* r=NULL;

    ResultList=CreateEntryList();
    ResultList2=CreateEntryList();
    ResultList3=CreateEntryList();

    arg_struct_doc *docarg=(arg_struct_doc*)malloc(sizeof(arg_struct_doc));
    docarg->id= doc_id;

    docarg->wordsofdoc = (char*)malloc(sizeof (char)*(strlen((doc_str))+1));
    strcpy(docarg->wordsofdoc,doc_str);

    doc* d=(doc*)initializedoc(docarg->id,docarg->wordsofdoc);

    arg_struct_exact *exarg=(arg_struct_exact*)malloc(sizeof(arg_struct_exact));
    arg_struct_hamming *hamarg=(arg_struct_hamming*)malloc(sizeof(arg_struct_hamming));
    arg_struct_edit *editarg=(arg_struct_edit*)malloc(sizeof(arg_struct_edit));

    exarg->exactMatchTable=exactMatchTable;
    exarg->list_of_words=d->list_of_words;

    hamarg->bkTreesForHamming=bkTreesForHamming;
    hamarg->list_of_words=d->list_of_words;

    editarg->bkTreesForEdit=bkTreeForEdit;
    editarg->list_of_words=d->list_of_words;

    tpool_add_work(pool2,MatchDocumentHashTable,exarg);

    tpool_add_work(pool2,MatchDocumentHamming,hamarg);

    tpool_add_work(pool2,MatchDocumentEdit,editarg);

    pthread_mutex_lock(&(pool2->work_mutex));
    pthread_cond_wait(&(pool2->working_cond), &(pool2->work_mutex));
    pthread_mutex_unlock(&(pool2->work_mutex));

    appendList(&ResultList,&ResultList2);
    appendList(&ResultList,&ResultList3);

    free(exarg);
    free(hamarg);
    free(editarg);


    //FIND THE RESULTS OF DOCUMENT AND PARSE IT IN THE STRUCT
    entry *e=NULL;
   if(ResultList->numOfNodes>0) {
        e = getFirstEntryOfList(ResultList);
        while (e != NULL) {
            if ((*e)->payload == NULL) {
                printf("NULL\n");
            }

            tempid = getFirstIdOfPayload((*e)->payload);
            while(tempid!=NULL){
                q = (query *) vectorGet(queries, tempid->idnumber-1);

                if ( q->flag == 1) {
                    r = (result *) vectorGet(results, tempid->idnumber-1);

                    int wordcount=0;
                    ent* temp = q->words->first;
                    while(temp!=NULL){
                        if(!strcmp(temp->w,(*e)->w)){
                            r->words[wordcount]=1;
                        }
                        temp=temp->next;
                        wordcount++;
                    }
                    vectorSet(results, tempid->idnumber - 1, r);
                }
                tempid=getNextIdOfPayload((*e)->payload);        
            }
            e = getNextEntryOfList(ResultList);
        }


        for (int i = 0; i < vectorTotal(results); i++) {
            r = (result *) vectorGet(results, i);
            int ccounter=0;
            for(int j=0;j<r->numOfWods;j++){
                ccounter=ccounter+r->words[j];
            }
            if(ccounter==r->numOfWods) {
                unsigned int *integ = (unsigned int *) malloc(sizeof(unsigned int));
                *integ = (unsigned int) i + 1;
//                printf("%u\t", *integ);
                vectorPushBack(d->qIdResults, integ);
            }
        }
        vectorPushBack(documents,d);
        //PUSH DOCUMENT IN VECTOR DOCUMENTS

        for (int i = 0; i < vectorTotal(results); i++) {
            r = (result *) vectorGet(results, i);
            q = (query *) vectorGet(queries, i);
            for(int j=0;j<r->numOfWods;j++){
                r->words[j]=0;
            }
            vectorSet(results, i, r);
        }
        //REINITIALIZE RESULTS VECTOR
    }else{
         DestroyEntryList(&ResultList);
         free(docarg->wordsofdoc);
       docarg->wordsofdoc=NULL;
       free(docarg);
       ResultList2->first=NULL;
       ResultList2->last=NULL;
       ResultList2->current=NULL;
       free(ResultList2);
       ResultList3->first=NULL;
       ResultList3->last=NULL;
       ResultList3->current=NULL;
       free(ResultList3);
        // DestroyEntryList(&ResultList3);
 
        vectorPushBack(d->qIdResults, NULL);
       
        return EC_FAIL;
    }
     DestroyEntryList(&ResultList);
    free(docarg->wordsofdoc);
    docarg->wordsofdoc=NULL;
    free(docarg);
    ResultList2->first=NULL;
    ResultList2->last=NULL;
    ResultList2->current=NULL;
    free(ResultList2);
    ResultList3->first=NULL;
    ResultList3->last=NULL;
    ResultList3->current=NULL;
    free(ResultList3);
    //  DestroyEntryList(&ResultList2);
    //   DestroyEntryList(&ResultList3);
   
    

    return EC_SUCCESS;
}


ErrorCode GetNextAvailRes(DocID* p_doc_id, unsigned int* p_num_res, QueryID** p_query_ids)
{
   unsigned int* temp=NULL;
    doc* d = (doc*)vectorGet(documents,currentDoc);
    *p_doc_id= (unsigned int)d->docid;

    *p_num_res=(unsigned int)d->qIdResults->total;
    temp=(unsigned int*)malloc(sizeof(unsigned int)*(d->qIdResults->total));
    for (int i=0;i<d->qIdResults->total;i++){
        temp[i]=*((unsigned int*)vectorGet(d->qIdResults,i));
    }
    *p_query_ids=temp;
    currentDoc++;
    return EC_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////////////////////
