#include "../../include/entry_list.h"
#include <stddef.h>




int main(){

    entry_list *l=CreateEntryList();
    char *c="the name";
    Payload *p=NULL;
    entry *e=CreateEntry(c,p);


    InsertLastEntryList(l,e);


    PrintEntryList(l);


    
     
    char *c2="the name 2";
    void *p2;
    entry *e2=CreateEntry(c2,p2);
    
    InsertLastEntryList(l,e2);

    PrintEntryList(l);  

    DeleteEntryEntryList(l,e2);  


    char *c3="the name 3";
    void *p3;
    entry *e3=CreateEntry(c3,p3);
    
    InsertFirstEntryList(l,e3);



    PrintEntryList(l); 
    
    DeleteFirstEntryList(l);

    PrintEntryList(l);

    DestroyEntryList(l);

     
    

    return 0;
    

    




}