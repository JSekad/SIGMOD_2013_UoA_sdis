#include "../include/entry.h"
#include <stdio.h>
#include "../include/entry_list.h"
#include <string.h>
#include <stdlib.h>

Entry_List *Create()
{
    Entry *N;
    N=(Entry *)malloc(sizeof(Entry));
    N->Link=NULL;
    return N;
}
void Destroy(Entry_List *L){
    Entry *current=L->first;
    while(current->Link){
        Entry *next=current->Link; 
        free(current);
        current=next;
        
        
    }
    free(L);

}
void PrintList(Entry_List *L)
{
    printf("(");
    Entry *N=L->first;
    while(N->Link != NULL) {
        N=N->Link;
        printf("%s", N->word);
        if (N->Link!=NULL) printf(",");
    }
    printf(")\n");
}

void InsertLast(Entry_List *L, Item A)
{   Entry *M=L->first;
    Entry *N;
    N=(Entry *)malloc(sizeof(Entry));
    strcpy(N->word, A);
    N->Link=NULL;
    if (M->Link == NULL) {
        M->Link=N;
    } else {
        M=M->Link;
        while (M->Link != NULL) M=M->Link;
        M->Link=N;
    }
}

Entry *search(Entry_List *L,Item A)                    /* pointer returning first node*/
{Entry *N=L->first;
    while (N->Link!=NULL)
    {
        N=N->Link;
        if (!strcmp(N->word,A)) return N;
    }
    return NULL;
}
void InsertAfter(Entry_List *L,Item A,Entry *node)
{
    Entry *temp,*new;
    temp=node->Link;
    new=(Entry*)malloc(sizeof(Entry));
    strcpy(new->word,A);
    new->Link=temp;
    node->Link=new;
}

void DeleteLast(Entry_List *L)
{  Entry *d=L->last;

    

    
    free(d);
}

void Delete(Entry_List *L,Entry *node)
{  Entry *prev,*next;

    while((L=L->Link)!=node)
    {   prev=L;

    }

    next=L->Link;
    free(L);
    prev->Link=next;
}
