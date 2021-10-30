#include "../../include/entry_list.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>




int main(){

    entry_list *l=CreateEntryList();
   

    char *c="the name";
    Payload *p=NULL;
    entry *e=CreateEntry(c,p);

    char *c2="the name 2";
    Payload *p2;
    entry *e2=CreateEntry(c2,p2);
    
    char *c3="the name 3";
    Payload *p3;
    entry *e3=CreateEntry(c3,p3);


     printf("size of list %ld\n",sizeof(l));
     printf("size of entry %ld\n",sizeof(e));


      InsertLastEntryList(l,e);


//     PrintEntryList(l);


    
     
    
    
    
      InsertLastEntryList(l,e2);

  //  PrintEntryList(l);  

 //   DeleteEntryEntryList(l,e2);  


    
    
//    InsertFirstEntryList(l,e3);



    PrintEntryList(l); 
   
    DeleteFirstEntryList(l);

    DeleteFirstEntryList(l);

    PrintEntryList(l);

    DestroyEntryList(l);



     


    DestroyEntry(e2);

   

    DestroyEntry(e3);



    DestroyEntry(e);

    
 
    

    return 0;
    

    


}