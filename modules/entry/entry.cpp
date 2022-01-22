#include "../../include/entry.h"



ent *CreateEntry(char *string, Payload payload) {

  
    ent *new_entry = (ent *) malloc(sizeof(ent));

    new_entry->prev = NULL;
    new_entry->next = NULL;
    new_entry->payload=NULL;
    new_entry->w=NULL;
     
    if (payload != NULL) {
        if (payload->numOfNodes>1){
            ids* current=getFirstIdOfPayload(payload);
            new_entry->payload =CreatePayload(current->idnumber,payload->distance,payload->matchtype);
            for (int i=1;i<payload->numOfNodes;i++){
                current=getNextIdOfPayload(payload);
                updatePayload(&(new_entry->payload),current->idnumber);
            }         
        }else{
           new_entry->payload =CreatePayload(payload->iDList->idnumber,payload->distance,payload->matchtype);
        }
        
    }
    if (string != NULL) {
        new_entry->w = (char *) malloc(sizeof(char) * (strlen(string) + 1));
        strcpy(new_entry->w, string);
    }
    

    if (new_entry->w==NULL) {
        free(new_entry);
        return NULL;
    }

    return new_entry;


}

void DestroyEntry(ent **e) {
  
    
    if ((*e)->payload)   DestroyPayload((*e)->payload);
    free((*e)->w);
    free((*e));
    (*e)=NULL;
}


