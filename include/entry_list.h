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

typedef struct Noderec {
    unsigned int id;
    struct Noderec *next;
} rec;

typedef rec * record;

typedef struct NodeSortList{
    unsigned int total;
    record first;
    record last;
} Sort_list;

typedef Sort_list * sort_list;

rec *CreateRecord(unsigned int);

void DestroyRecord(rec **);

Sort_list *CreateSortList();

void DestroySortList(Sort_list **L);

void InsertSortedInList(Sort_list *L,unsigned int id);

void InsertNonsortedInList(Sort_list *L,unsigned int id);

Entry_list *CreateEntryList();

void InsertLastEntryList(Entry_list *, ent *);

void DestroyEntryList(Entry_list **);

entry * getFirstEntryOfList(Entry_list*);

entry * getNextEntryOfList(Entry_list*);


ent* searchEntryList(Entry_list*,word);

void PrintEntryList(Entry_list *);

#endif

