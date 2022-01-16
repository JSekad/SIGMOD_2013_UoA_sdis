#include "../include/core.h"
#include <cstring>
#include <cstdlib>
#include <cstdio>

#include "../../../include/query.h"
#include "../../../include/doc.h"
#include "../../../include/vector.h"
#include "../../../include/bktree.h"
#include "../../../include/distance.h"
#include "../../../include/hashTable.h"
#include <unistd.h>


vector *queries;
vector *documents;
hashTable *exactMatchTable;
node *bkTreeForEdit;
vector* bkTreesForHamming;
vector* results;
int currentDoc=0;


using namespace std;

ErrorCode InitializeIndex(){
    void* ok = NULL;
    queries =(vector*) malloc(sizeof(vector));
    vector_init(queries,STARTING_VERTORS_CAPACITY);
    documents =(vector*) malloc(sizeof(vector));
    vector_init(documents,STARTING_VERTORS_CAPACITY);
    printf("Initial Index\n");
    
    exactMatchTable = CreateHashTable();
    bkTreeForEdit = NULL;
    bkTreesForHamming=(vector*)malloc(sizeof(vector));
    vector_init(bkTreesForHamming,27);
    
    printf("Initial Index\n");
    
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
    return EC_SUCCESS;
}


ErrorCode StartQuery(QueryID query_id, const char* query_str, MatchType match_type, unsigned int match_dist)
{
    //printf("%s %d\n",query_str,match_type);

    query *q;
    result *r;
    size_t len;
    /***CONST TO DYNAMIC***/
    char* tempWord = (char*)malloc(sizeof (char)*(strlen(query_str)+1));
    strcpy(tempWord,query_str);

    //IF EXACT MATCH
    if (match_type==MT_EXACT_MATCH){
        
        initQuery(&q,query_id,0,match_dist,tempWord);
        initResult(&r,query_id,q->numOfWords);
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
        //IF HAMMING MULTIPLE TREES
    }else if(match_type==MT_HAMMING_DIST){
        initQuery(&q,query_id,1,match_dist,tempWord);
        initResult(&r,query_id,q->numOfWords);
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
        //IF EDIT
    }else if(match_type==MT_EDIT_DIST) {

        initQuery(&q,query_id,2,match_dist,tempWord);
        initResult(&r,query_id,q->numOfWords);
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

    free(tempWord);

}

ErrorCode EndQuery(QueryID query_id)
{
   
    query * q=(query *)vectorGet(queries,(int)query_id-1);
    if(q->idNumber==(int)query_id){
        q->flag=0;
        vectorSet(queries,(int)query_id-1,q);
    }
    return EC_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////////////////////

ErrorCode MatchDocument(DocID doc_id, const char* doc_str)
{
    ids * tempid=NULL;
    query* q=NULL;
    result* r=NULL;
    node *bkTreeForHamming;
    Entry_list * ResultList=NULL;
    char* tempWord = (char*)malloc(sizeof (char)*(strlen(doc_str)+1));
    strcpy(tempWord,doc_str);
    doc* d = initializedoc(doc_id,tempWord);
    sort_list sl=NULL;

    //LIST OF ENTRIES OFF DOCUMENT CHECK IN HASHTABLE

    //RETURN RESULTS ENTY LIST 1

    ResultList = MatchDocumentHashTable(exactMatchTable,d->list_of_words);

    if (ResultList==NULL){
        ResultList=CreateEntryList();
    }


    //LIST OF ENTRIES OF DOCUMENT CHECK IN HAMING BKTREE

    //RETURN RESULTS ENTY LIST 1 EXTEND


    entry *e=getFirstEntryOfList(d->list_of_words);
    while  (e!=NULL){
        size_t len;
        len=strlen((*e)->w);
        bkTreeForHamming= (node*) vectorGet(bkTreesForHamming,(int)len-4);
        if(bkTreeForHamming!=NULL) {
            for (int threshold = 1; threshold < 4; threshold++) {
                get_words_sub(&ResultList, &bkTreeForHamming, (*e)->w, threshold, HAMMING_DIST);
            }
        }

        e=getNextEntryOfList(d->list_of_words);
    }


    //LIST OF ENTRIES OF DOCUMENT CHECK IN EDIT BKTREE

    //RETURN RESULTS ENTY LIST 1 EXTEND

    e=getFirstEntryOfList(d->list_of_words);
    while  (e!=NULL){

        for(int threshold=1;threshold<4;threshold++){
            get_words_sub(&ResultList,&bkTreeForEdit,(*e)->w,threshold,EDIT_DIST);
        }

        e=getNextEntryOfList(d->list_of_words);
    }
    


    //FIND THE RESULTS OF DOCUMENT AND PARSE IT IN THE STRUCT

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
        free(tempWord);
        return EC_FAIL;
    }
    DestroyEntryList(&ResultList);
    free(tempWord);
    return EC_SUCCESS;
}


//////////////////////////////////////////////////////////////////////////////////////////////

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
