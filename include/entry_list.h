#include "entry.h"

typedef struct {
    int numOfNodes;
    ent *first;                                             /*hide dummy*/
    ent *last;
} entry_list;


entry_list *CreateEntryList(void);

void DeleteEntryList(entry_list *, ent *);

void InsertLastEntryList(entry_list *, ent *);

void InsertFirstEntryList(entry_list *, ent *);

void PrintEntryList(entry_list *);

ent *searchEntryList(entry_list *, word);

void InsertAfterEntryList(entry_list *, ent *, ent *);

void DeleteLastEntryList(entry_list *);

void DeleteFirstEntryList(entry_list *);

void DeleteEntryEntryList(entry_list *, ent *);

void DestroyEntryList(entry_list *);