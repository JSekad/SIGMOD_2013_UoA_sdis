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


/* COMMENT FOR FUTURE USE

void DeleteEntryList(Entry_list *, ent *);

void InsertFirstEntryList(Entry_list *, ent *);

void PrintEntryList(Entry_list *);

ent *searchEntryList(Entry_list *, word);

void InsertAfterEntryList(Entry_list *, ent *, ent *);

void DeleteLastEntryList(Entry_list *);

void DeleteFirstEntryList(Entry_list *);

void DeleteEntryEntryList(Entry_list *, ent *);
 */

