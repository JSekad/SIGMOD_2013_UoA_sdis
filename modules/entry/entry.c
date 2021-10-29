#include "../../include/entry_list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>



entry * CreateEntry(char *string,Payload payload){
    
    printf("CreateEntry\n");
        
    entry *new_entry=(entry *)malloc(sizeof(entry));

    new_entry->prev=NULL;
    new_entry->next=NULL;
    
    if (payload!=NULL) {
        new_entry->payload=payload;
    }
    if (string!=NULL)  {
         new_entry->w=(char*)malloc(sizeof(char)*(strlen(string)+1));
         strcpy(new_entry->w,string);
    }

    printf("CreateEntry  %s\n",new_entry->w);

    return new_entry;


}

void DestroyEntry(entry *e){

    //free(e->payload);
    free(e->w);
    free(e);
    
}



entry * InsertNextEntry (entry *previous,entry *next){
    previous->next=(struct NodeTag *)next;
    next->prev=(struct NodeTag *)previous;

}
