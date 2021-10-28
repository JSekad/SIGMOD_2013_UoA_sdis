#include <stdio.h>
#include "../../include/entry_list.h"
#include <string.h>
#include <stdlib.h>

entry_list *CreateEntryList()
{
    entry_list *N;
    N=(entry_list *)malloc(sizeof(entry));
    N->first=NULL;
    N->last=NULL;
    N->numOfNodes=0;
    return N;
}


void DestroyEntryList(entry_list *L){
  if (L->numOfNodes>0){  
    entry *current=(entry *)L->first;
    while(current->next){
        entry *next=(entry *)current->next; 
        free(current);
        current=next;
        
        
    }
    free(current);}
    
    free(L);

}
void PrintEntryList(entry_list *L)
{
    printf("(");
    entry *N=(entry *)L->first;
    while(N->next != NULL) {
        N=(entry *)N->next;
        printf("%s", N->w);
        if (N->next!=NULL) printf(",");
    }
    printf("%s", N->w);
    if (N->next!=NULL) printf(",");

    printf(")\n");
}

void InsertLastEntryList(entry_list *L, entry *e)
{   
    if (L->numOfNodes>0){
        entry *m=(entry *)L->last;
        InsertNextEntry((entry *)m->next,e);
        L->last=e;
        L->numOfNodes++;
        return;
     }
    
    if (L->numOfNodes==0){
        L->last=e;
        L->first=e;
        e->next=NULL;
        e->prev=NULL;
        L->numOfNodes++;
    }

    

}

entry *search(entry_list *L,word A)                    /* pointer returning first node*/
{entry *N=(entry *)L->first;
    while (N->next!=NULL)
    {
        N=N->next;
        if (!strcmp(N->w,A)) return N;
    }

    return NULL;
}
void InsertAfter(entry_list *L,word A,entry *node)
{
    entry *temp,*new;
    temp=node->next;
    new=(entry*)malloc(sizeof(entry));
    strcpy(new->w,A);
    new->next=temp;
    node->next=new;
}

void DeleteLastEntryList(entry_list *L)
{  entry *d=(entry *)L->last;
     
    L->last=d->prev; 
    if (L->numOfNodes==1){
         L->first=NULL; 
         L->numOfNodes--;   
         free(d);
         return;}
    if (L->numOfNodes>1){
        ((entry *)L->last)->next=NULL;
        L->numOfNodes--;
        free(d);
        return;
    }     
}


void Delete(entry_list *L,entry *node)
{  entry *prev,*next;
   entry *e=L->first;  

    while(strcmp(e->w,node->w)){  
         e=e->next;   
    }

    ((entry *)e->prev)->next=e->next; 
    DestroyEntry(e);
    L->numOfNodes--;
    
    
}
