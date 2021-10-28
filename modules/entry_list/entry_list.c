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
    if (L->numOfNodes>0){
        entry *m=L->last;
        m->next=e;
        L->last=e;
        e->prev=m;
        L->numOfNodes++;
        return;
     }
    
    if (L->numOfNodes==0){
        L->last=e;
        L->first=e;
        e->next=NULL;
        e->prev=NULL;
        L->numOfNodes++;
        return;
    }

    

}



void InsertFirstEntryList(entry_list *L, entry *e)
{   
    if (L->numOfNodes>0){
        entry *m=L->first;
        m->prev=e;
        L->first=e;
        e->next=m;
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

entry *search(entry_list *L,word A)                    
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
         free(d);
         return;}
    if (L->numOfNodes>1){
        ((entry *)L->first)->prev=NULL;
        L->numOfNodes--;
        free(d);
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
         e=e->next;   
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
