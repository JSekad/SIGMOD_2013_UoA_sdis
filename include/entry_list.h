#include "entry.h"

typedef struct  {
    int numOfNodes;
     entry *first;                                             /*hide dummy*/
     entry *last;
} entry_list;


entry_list *CreateEntryList(void);
void  DeleteEntryList(entry_list *,entry *);
void InsertLastEntryList(entry_list * ,entry *);
void InsertFirstEntryList(entry_list * ,entry *);
void PrintEntryList(entry_list *);
entry *searchEntryList(entry_list *,word);
void InsertAfterEntryList(entry_list *,entry*,entry *);
void DeleteLastEntryList(entry_list *);
void DeleteFirstEntryList(entry_list *);
void DeleteEntryEntryList(entry_list *,entry*);
void DestroyEntryList(entry_list *);