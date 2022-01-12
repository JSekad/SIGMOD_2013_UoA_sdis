#include "../../include/query.h"


int initQuery(query** q,int idNumber,int matchTypeId,int distance,char* concatWords){
    int counter = 0;
    (*q)=(query*)malloc(sizeof (query));
    (*q)->distance=distance;
    (*q)->idNumber=idNumber;
    (*q)->flag=1; //ENERGO
    (*q)->matchTypeId=matchTypeId;
    (*q)->words=CreateEntryList();

    char* token = strtok(concatWords," ");

    while (token !=NULL){
        if(strlen(token)<=31) {
            counter++;
            Payload p = CreatePayload(idNumber, distance, matchTypeId);
            entry e = CreateEntry(token, p);
            InsertLastEntryList((*q)->words, e);
            DestroyPayload(p);
            DestroyEntry(&e);
        }
        token = strtok(NULL," ");
    }
    (*q)->numOfWords=counter;
    return 0;
}

int destroyQuery(query* q){
    DestroyEntryList(&(q->words));
    free(q);
    return 0;
};


int initResult(result ** r,int id,int numofwords){
    *r=(result*)malloc(sizeof(result));
    (*r)->id=id;
    (*r)->numOfWods=numofwords;
    (*r)->words=(int*)malloc(sizeof (int)*numofwords);
    for(int i=0;i<numofwords;i++){
        (*r)->words[i]=0;
    }
    return 0;
};




int destroyResult(result * r){

    free(r->words);
    free(r); 
    return 0;
};



void PrintQuery(query* q){
    printf("Query id %d/nquery matchtype :%d/nquery distance :%d/nquery numofWords : %d/n",(q)->idNumber,(q)->matchTypeId,(q)->distance,(q)->numOfWords);
    PrintEntryList((q)->words);
}