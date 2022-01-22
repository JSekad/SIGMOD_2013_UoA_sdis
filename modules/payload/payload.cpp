#include "../../include/payload.h"
#include <cstdlib>
#include <cstdio>


ids *CreateId(int id) {
  
    ids *newids =(ids*)malloc(sizeof(ids));
    newids->idnumber = id;
    newids->next=NULL;
    newids->prev=NULL;
    
    return newids;

}

void DestroyId(ids * idstodestroy) {

    free(idstodestroy);    
     
}






Payload CreatePayload(int id,int dist,int type){
    
    if(id==-1 && dist==-1 && type==-1){
        return NULL;
    }
    Payload pld=(Payload)malloc(sizeof(payld));
    pld->distance = dist;
    pld->matchtype =type;
    pld->iDList=CreateId(id);
    pld->lastiDlist=pld->iDList;
    pld->numOfNodes=1;
    return pld;
}

void changePayloadThreshHold(Payload* pld,int i){
    (*pld)->thresholdFount=i;
}

ids * getFirstIdOfPayload(Payload payload){
    payload->current=payload->iDList;
    return payload->current;
};

ids * getNextIdOfPayload(Payload payload){
    payload->current=payload->current->next;
    return payload->current == NULL ? NULL : payload->current;
};





void DestroyPayload(Payload p) {
    
    if (p->numOfNodes > 0) {

        ids *current =   p->iDList;

        while (current->next!=NULL) {
            ids *next =  current->next;
            DestroyId(current);
            current = next;
        }

        DestroyId(current);
    }

    free(p);
    
}



void updatePayload(Payload *payload,int id){
     InsertLastPayload(payload,id);

}

void InsertLastPayload(Payload *payload,int id) {
    ids *i= CreateId(id);
    
    if ((*payload)->numOfNodes > 0) {
        (*payload)->lastiDlist->next=i;
        (*payload)->lastiDlist= i; 
        (*payload)->lastiDlist->next= NULL;
        (*payload)->numOfNodes++;
        return;
    }

    if ((*payload)->numOfNodes == 0) {

        (*payload)->lastiDlist = i;
        (*payload)->iDList = i;
        i->next = NULL;
        i->prev = NULL;
        (*payload)->numOfNodes++;
        return;
    }

}



void PrintPayload(Payload *L) {
    printf("(");

    ids *N = (ids *) (*L)->iDList;
    if (!N) {
        printf("())\n");
        return;
    }
    while (N->next != NULL) {

        printf("%d", N->idnumber);
        if (N->next != NULL) printf(",");
        N = (ids *) N->next;
    }
    printf("%d", N->idnumber);
    if (N->next != NULL) printf(",");

    printf(")\n");
}