
#ifndef PAYLOAD
#define PAYLOAD

typedef struct Ids{
    int idnumber;
    Ids* next;
    Ids* prev;
}ids;

typedef struct Ids idnode;


typedef struct payload{
     
    ids * iDList;
    ids * lastiDlist;
    int distance;
    int thresholdFount;
    int matchtype;
    ids *current;
    int numOfNodes;
}payld;




typedef payld *Payload;


ids *CreateId(int id);
  
void DestroyId(ids * idstodestroy);

Payload CreatePayload(int,int,int);

void changePayloadThreshHold(Payload* pld,int i);


void updatePayload(Payload *,int  );

ids * getFirstIdOfPayload(Payload payload);

ids * getNextIdOfPayload(Payload payload);

void InsertLastPayload(Payload *,int );

void PrintPayload(Payload *L);


void DestroyPayload(Payload p) ;

#endif