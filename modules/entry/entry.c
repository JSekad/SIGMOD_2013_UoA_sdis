#include "../../include/entry_list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>



entry * CreateEntry(char *string,void *payload){
    
        printf("CreateEntry\n"); 
        
    entry *new_entry=malloc(sizeof(entry));


    
    if (payload!=NULL) {
        new_entry->payload=payload;
    }
    if (string!=NULL)  {
         new_entry->w=malloc(sizeof(string));
         strcpy(new_entry->w,string);
    }

    printf("CreateEntry\n"); 

    return new_entry;


}

void DestroyEntry(entry *e){

    free(e->payload);
    free(e->w);
    free(e);
    
}



entry * InsertNextEntry (entry *previous,entry *next){
    previous->next=(struct NodeTag *)next;
    next->prev=(struct NodeTag *)previous;

}
