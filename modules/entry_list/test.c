#include "../../include/entry_list.h"




int main(){

    entry_list *l=CreateEntryList();
    char *c="the name";
    void *p;
    entry *e=CreateEntry(c,p);


    InsertLastEntryList(l,e);


    PrintEntryList(l);


    DeleteLastEntryList(l);

    
    DestroyEntryList(l);


    

    return 0;
    

    




}