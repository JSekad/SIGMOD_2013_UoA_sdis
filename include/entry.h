#ifndef ENTRY
#define ENTRY
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "payload.h"


typedef char *word;


typedef struct NodeTag {
    Payload payload;
    word w;                                            /*hide dummy*/
    struct NodeTag *next;
    struct NodeTag *prev;
} ent;

typedef ent *entry;



//AN TO ENTRY THELEIS NA TO KRATHSEIS KAI GIA DOCUMENT APLA PERNAS NULL STO PAYLOAD
ent *CreateEntry(char *, Payload);

void DestroyEntry(ent **);


#endif



