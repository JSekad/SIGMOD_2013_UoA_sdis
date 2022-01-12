#ifndef ENTRY_LIST
#define ENTRY_LIST
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "entry.h"

typedef struct Nodee{
    int numOfNodes;
    entry current;
    entry first;                                             /*hide dummy*/
    entry last;
} Entry_list;

typedef Entry_list * entry_list;


Entry_list *CreateEntryList();

void InsertLastEntryList(Entry_list *, ent *);

void DestroyEntryList(Entry_list **);

entry * getFirstEntryOfList(Entry_list*);

entry * getNextEntryOfList(Entry_list*);


ent* searchEntryList(Entry_list*,word);

void PrintEntryList(Entry_list *);

#endif

