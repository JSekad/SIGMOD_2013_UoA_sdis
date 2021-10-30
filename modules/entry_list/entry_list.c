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
        DestroyEntry(current);
        current=next;
        
        
    }

    DestroyEntry(current);}

    free(L);

}



void PrintEntryList(entry_list *L){
    
    printf("(");

    entry *N=(entry *)L->first;
    if (!N){
         printf("())\n");
        return; 
    } 
    while(N->next != NULL) {
       
        printf("%s", N->w);
        if (N->next!=NULL) printf(",");
         N=(entry *)N->next;
    }
    printf("%s", N->w);
    if (N->next!=NULL) printf(",");

    printf(")\n");
}

void InsertLastEntryList(entry_list *L, entry *e)
{ 
  printf("L->numOfNodes %d\n",L->numOfNodes);
  entry *m=CreateEntry(e->w,e->payload);

    if (L->numOfNodes>0){
        printf("in numOfNodes>0 %d\n",L->numOfNodes);
        m->prev=L->last;
        L->last->next=m;
        L->last=m;
        m->next=NULL;
        L->numOfNodes++;
        return;
     }
    
    if (L->numOfNodes==0){
        printf("in numOfNodes==0  %d\n",L->numOfNodes);
        
        L->last=m;
        L->first=m;
        m->next=NULL;
        m->prev=NULL;
        L->numOfNodes++;
        return;
    }

    

}



void InsertFirstEntryList(entry_list *L, entry *e)
{   entry *new_entry=CreateEntry(e->w,e->payload);
    if (L->numOfNodes>0){
        entry *m=L->first;
        m->prev=new_entry;
        L->first=new_entry;
        new_entry->next=m;
        L->numOfNodes++;
        return;
     }
    
    if (L->numOfNodes==0){
        L->last=new_entry;
        L->first=new_entry;
        new_entry->next=NULL;
        new_entry->prev=NULL;
        L->numOfNodes++;
    }

    

}

entry *searchEntryList(entry_list *L,word w)                  
{entry *N=(entry *)L->first;
    while (N->next!=NULL)
    {
        N=N->next;
        if (!strcmp(N->w,w)) return N;
    }
    if (!strcmp(N->w,w)) return N;

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
         L->last=NULL; 
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

void DeleteFirstEntryList(entry_list *L)
{  entry *d=(entry *)L->first;
     
    L->first=d->next; 
    if (L->numOfNodes==1){
         L->first=NULL;
         L->last=NULL; 
         L->numOfNodes--;   
         DestroyEntry(d);
         return;}
    if (L->numOfNodes>1){
        ((entry *)L->first)->prev=NULL;
        L->numOfNodes--;
        DestroyEntry(d);
        return;
    }     
}




void DeleteEntryEntryList(entry_list *L,entry *node)
{   printf("Entry List\n");
   entry *e=(entry *)L->first;  
    

    if (L->numOfNodes==1){
        if (!strcmp(e->w,node->w)){
           
            
            DestroyEntry(e);
            L->numOfNodes--;
            L->first=NULL;
            L->last=NULL;
        }
         
        return;
    } 
   
    printf("Entry List 2\n");
    

    while(strcmp(e->w,node->w) ){ 
        printf("strcmp %s %s\n",e->w,node->w); 
        if (! (e=e->next)) return;    
    }

    printf("Entry List 3\n");
    

    if ((e->prev) && (e->next)){

        e->prev->next=e->next;
        e->next->prev=e->prev;
        DestroyEntry(e);
        L->numOfNodes--;
        return;
    
    }

    if (!e->prev){
        e->next->prev=e->prev;
        DestroyEntry(e);
        L->numOfNodes--;
        return;

    } 

    if (!e->next){
        e->prev->next=e->next;
        DestroyEntry(e);
        L->numOfNodes--;
        return;

    }
        
    
}
