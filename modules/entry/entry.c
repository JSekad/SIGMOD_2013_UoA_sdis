#include "../../include/entry_list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


ent *CreateEntry(char *string, Payload payload) {


    ent *new_entry = (ent *) malloc(sizeof(ent));

    new_entry->prev = NULL;
    new_entry->next = NULL;
    new_entry->payload=NULL;
    new_entry->w=NULL;

    if (payload != NULL) {
        new_entry->payload = payload;
    }
    if (string != NULL) {
        new_entry->w = (char *) malloc(sizeof(char) * (strlen(string) + 1));
        strcpy(new_entry->w, string);
    }

    printf("Entry \"%s\" created\n", new_entry->w);

    return new_entry;


}

void DestroyEntry(ent **e) {
    //free(e->payload);
    free((*e)->w);
    free((*e));
    (*e)=NULL;
}


ent *InsertNextEntry(ent *previous, ent *next) {
    previous->next = (struct NodeTag *) next;
    next->prev = (struct NodeTag *) previous;

}
