#include <stdio.h>
#include "../include/api.h"

int main(){


    entry_list *l=CreateEntryList();
    char *c="the name";
    void *p;
    entry *e=CreateEntry(c,p);


    InsertLastEntryList(l,e);


    PrintEntryList(l);


    printf("all done well\n");



    entry *e2;

    ErrorCode code= create_entry(e->w,e2);
    
    printf("after create entry\n");

    if (code==EC_SUCCESS){
        InsertLastEntryList(l,e2);
       
    }
    else{
        printf("something went wrong\n");
    }
   

    




}