#include "../include/entry.h"
#include <stdio.h>
#include "../include/entry_list.h"
#include <string.h>
#include <stdlib.h>

entry_list *Create()
{
    entry *N;
    N=(entry *)malloc(sizeof(entry));
    N->Link=NULL;
    return N;
}
void Destroy(entry_list *L){
    entry *current=L->first;
    while(current->Link){
        entry *next=current->Link; 
        free(current);
        current=next;
        
        
    }
    free(L);

}
void PrintList(entry_list *L)
{
    printf("(");
    entry *N=L->first;
    while(N->Link != NULL) {
        N=N->Link;
        printf("%s", N->w);
        if (N->Link!=NULL) printf(",");
    }
    printf(")\n");
}

void InsertLast(entry_list *L, word A)
{   entry *M=L->first;
    entry *N;
    N=(entry *)malloc(sizeof(entry));
    strcpy(N->w, A);
    N->Link=NULL;
    if (M->Link == NULL) {
        M->Link=N;
    } else {
        M=M->Link;
        while (M->Link != NULL) M=M->Link;
        M->Link=N;
    }
}

entry *search(entry_list *L,word A)                    /* pointer returning first node*/
{entry *N=L->first;
    while (N->Link!=NULL)
    {
        N=N->Link;
        if (!strcmp(N->w,A)) return N;
    }
    return NULL;
}
void InsertAfter(entry_list *L,word A,entry *node)
{
    entry *temp,*new;
    temp=node->Link;
    new=(entry*)malloc(sizeof(entry));
    strcpy(new->w,A);
    new->Link=temp;
    node->Link=new;
}

void DeleteLast(entry_list *L)
{  entry *d=L->last;


    
    free(d);
}

void Delete(entry_list *L,entry *node)
{  entry *prev,*next;

    while((L=L->Link)!=node)
    {   prev=L;

    }

    next=L->Link;
    free(L);
    prev->Link=next;
}
