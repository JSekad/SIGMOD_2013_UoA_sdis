#ifndef DOC
#define DOC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entry.h"


#include "hashTable.h"
#include "vector.h"

typedef struct docs{
    int docid;
    int numofwords;
    Entry_list* list_of_words;
    Sort_list * qIdResults;
}doc;

doc* initializedoc(int,char*);


 void DestroyDoc(doc *);


#endif