#ifndef HASH_TABLE
#define HASH_TABLE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "entry_list.h"
#include "core.h"
#include <stdbool.h>

#define SIZEOFHASH ((((MAX_DOC_LENGTH/4)-(MAX_DOC_LENGTH/31))*8)/10)

typedef struct  {


    Entry_list *entrylist[SIZEOFHASH];


    int sizeOfHash;
    int sizeofInput;
    int current;

} hashTable;


typedef enum{
    UPDATE,
    NOUPDATE,
} HasInsertionType;



hashTable  *CreateHashTable( );

void DestroyHashTable(hashTable *);

int HashFuction(hashTable *table,char* key);

int insertEntry(hashTable *table,ent * ,HasInsertionType );

entry* Exists(hashTable *,word w);


void PrintHashTable(hashTable *);

Entry_list * MatchDocumentHashTable(hashTable *,Entry_list *);

entry getFirstEntryFromHash(hashTable *);


entry getNextEntryFromHash(hashTable *);

// ent * getEntry(word);

#endif