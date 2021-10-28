#include "../../include/entry_list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>



entry * CreateEntry(char *string,Payload payload){
    
    
    printf("CreateEntry\n"); 
        
    entry *new_entry=malloc(sizeof(entry));

    
    
   new_entry->next=NULL;
   new_entry->payload=payload;
   new_entry->prev=NULL;
   new_entry->w=malloc(sizeof(string));
   strcpy(new_entry->w,string);

    printf("CreateEntry exiting \n"); 

    return new_entry;


}

void DestroyEntry(entry *e){

    

   // free(e->payload);
    free(e->w);
    free(e);
    
}



entry * InsertNextEntry (entry *previous,entry *next){
    previous->next=(struct NodeTag *)next;
    next->prev=(struct NodeTag *)previous;

}
