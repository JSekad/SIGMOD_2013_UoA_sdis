#include <stdio.h>
#include "../include/api.h"

int main(){


    entry_list *l=CreateEntryList();
    char *c="the name";
    void *p;
    entry *e=CreateEntry(c,p);


    printf("%s\n",e->w);
    InsertLastEntryList(l,e);


    PrintEntryList(l);


    printf("all done well\n");



    entry *e2;


    if (Working == create_entry(e->w,&e2)){
        printf("OKKKK\n");
        //printf("%s",e2->w);

    }
    
    printf("after create entry\n");

//    if (code==EC_SUCCESS){
//        InsertLastEntryList(l,e2);
//
//    }
//    else{
//        printf("something went wrong\n");
//    }
   

    




}