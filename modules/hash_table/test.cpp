#include "../../include/acutest.h"
#include "../../include/hashTable.h"



void test_create_HashTable(void){

    hashTable *table=CreateHashTable();
     
   
  //  TEST_CHECK(create_entry(NULL,&testent) == Failed);

    DestroyHashTable(table);


}


void test_destroy_hashTable(void){


        hashTable *table=CreateHashTable();

        
        DestroyHashTable(table);


}



void test_insert_hashTable(void){




      hashTable *table=CreateHashTable();
      
       Payload p=NULL;
       ent *e=CreateEntry("niaou",p);

       ent *e2=CreateEntry("niaou",p);
       
       insertEntry(table,e,NOUPDATE);

       insertEntry(table,e2,NOUPDATE);


       DestroyEntry(&e); 
       DestroyEntry(&e2);   
       DestroyHashTable(table);



             
   



}

void test_exists_hashTable(void){
       hashTable *table=CreateHashTable();
      
       Payload p=NULL;
       ent *e=CreateEntry("niaou",p);
       ent *e2=CreateEntry("niaou",p);


       insertEntry(table,e,NOUPDATE);
       insertEntry(table,e2,NOUPDATE);
       

       TEST_CHECK(Exists(table,e->w)!=NULL);  

       
    
       
    
       DestroyEntry(&e);  
       DestroyEntry(&e2);  

       DestroyHashTable(table);


}



void  test_print_hashTable(void){

       hashTable *table=CreateHashTable();
      
       Payload p=NULL;
       ent *e=CreateEntry("niaou",p);
       ent *e2=CreateEntry("niaou2",p);
       ent *e3=CreateEntry("niaou3",p);
       ent *e4=CreateEntry("niaou4",p);
       ent *e5=CreateEntry("niaou5",p);

       insertEntry(table,e, NOUPDATE);
       insertEntry(table,e2,NOUPDATE);
       insertEntry(table,e3,NOUPDATE);
       insertEntry(table,e4,NOUPDATE);
       insertEntry(table,e5,NOUPDATE);


       PrintHashTable(table);



       DestroyEntry(&e);  
       DestroyEntry(&e2);  
       DestroyEntry(&e3);
       DestroyEntry(&e4);
       DestroyEntry(&e5);
       
       DestroyHashTable(table);
       
       

}




void  test_getFirstEntryFromHash(void){

       hashTable *table=CreateHashTable();
      
       Payload p=NULL;
       ent *e=CreateEntry("niaou",p);
       ent *e2=CreateEntry("niaou2",p);
       ent *e3=CreateEntry("niaou3",p);
       ent *e4=CreateEntry("niaou4",p);
       ent *e5=CreateEntry("niaou5",p);

       insertEntry(table,e, NOUPDATE);
       insertEntry(table,e2,NOUPDATE);
       insertEntry(table,e3,NOUPDATE);
       insertEntry(table,e4,NOUPDATE);
       insertEntry(table,e5,NOUPDATE);


       PrintHashTable(table);
       entry nentry=getFirstEntryFromHash(table);

       printf("%s\n",nentry->w);
       
       DestroyEntry(&nentry);

       DestroyEntry(&e);  
       DestroyEntry(&e2);  
       DestroyEntry(&e3);
       DestroyEntry(&e4);
       DestroyEntry(&e5);
       
       DestroyHashTable(table);
       
       

}


void  test_getNextEntryFromHash(void){

       hashTable *table=CreateHashTable();
      
       Payload p=NULL;
       ent *e=CreateEntry("niaou",p);
       ent *e2=CreateEntry("niaou2",p);
       ent *e3=CreateEntry("niaou3",p);
       ent *e4=CreateEntry("niaou4",p);
       ent *e5=CreateEntry("niaou5",p);

       insertEntry(table,e, NOUPDATE);
       insertEntry(table,e2,NOUPDATE);
       insertEntry(table,e3,NOUPDATE);
       insertEntry(table,e4,NOUPDATE);
       insertEntry(table,e5,NOUPDATE);


       PrintHashTable(table);
       entry nentry=getFirstEntryFromHash(table);

       printf("%s\n",nentry->w);
       
       DestroyEntry(&nentry);
       
       while ((nentry=getNextEntryFromHash(table))!=NULL){
             printf("in the wile loop\n");
             printf("%s\n",nentry->w);
             DestroyEntry(&nentry); 
       }

       DestroyEntry(&e);  
       DestroyEntry(&e2);  
       DestroyEntry(&e3);
       DestroyEntry(&e4);
       DestroyEntry(&e5);
       
       DestroyHashTable(table);
       
       

}


void test_match_document_HashTable(void){

       hashTable *table=CreateHashTable();
      
       Payload p=CreatePayload(1,2,3);
       ent *e=CreateEntry("niaou",p);
       ent *e2=CreateEntry("niaou2",p);
       ent *e3=CreateEntry("niaou3",p);
       ent *e4=CreateEntry("niaou4",p);
       ent *e5=CreateEntry("niaou5",p);

       insertEntry(table,e, UPDATE);
       insertEntry(table,e2,UPDATE);
       insertEntry(table,e3,UPDATE);
       insertEntry(table,e4,UPDATE);
       insertEntry(table,e5,UPDATE);


       Entry_list *l = CreateEntryList();
        
       InsertLastEntryList(l,e);  
       InsertLastEntryList(l,e2);
       InsertLastEntryList(l,e3);
       InsertLastEntryList(l,e4); 
       
       ent *e10=CreateEntry("niaou10",p);
       ent *e11=CreateEntry("niaou11",p);
       ent *e12=CreateEntry("niaou12",p);

       InsertLastEntryList(l,e10);  
       InsertLastEntryList(l,e11);
       InsertLastEntryList(l,e12);
        
       
       
       
       
       Entry_list *resl=MatchDocumentHashTable(table,l); 
      




     TEST_CHECK(resl->numOfNodes==4);


     PrintEntryList(resl);








        
      DestroyEntryList(&l);
      DestroyEntryList(&resl);
      



       DestroyEntry(&e);  
       DestroyEntry(&e2);  
       DestroyEntry(&e3);
       DestroyEntry(&e4);
       DestroyEntry(&e5);
       DestroyEntry(&e10);
       DestroyEntry(&e11);
       DestroyEntry(&e12);
       
      
      
       DestroyHashTable(table);
       DestroyPayload(p);
       

       
}


void test_match_document_HashTable2(void){

       hashTable *table=CreateHashTable();
      
       Payload p=CreatePayload(1,2,3);
       ent *e=CreateEntry("niaou",p);
       ent *e2=CreateEntry("niaou",p);
       ent *e3=CreateEntry("niaou",p);
       ent *e4=CreateEntry("niaou",p);
       ent *e5=CreateEntry("niaou",p);

       insertEntry(table,e, UPDATE);
       insertEntry(table,e2,UPDATE);
       insertEntry(table,e3,UPDATE);
       insertEntry(table,e4,UPDATE);
       insertEntry(table,e5,UPDATE);


       Entry_list *l = CreateEntryList();
        
       InsertLastEntryList(l,e);  
   //    InsertLastEntryList(l,e2);
   //    InsertLastEntryList(l,e3);
   //    InsertLastEntryList(l,e4); 
       
       ent *e10=CreateEntry("niaou10",p);
       ent *e11=CreateEntry("niaou11",p);
       ent *e12=CreateEntry("niaou12",p);

       InsertLastEntryList(l,e10);  
       InsertLastEntryList(l,e11);
       InsertLastEntryList(l,e12);
        
       
       
       
       
       Entry_list *resl=MatchDocumentHashTable(table,l); 
      
     printf("num of nodes in the resl :%d\n",resl->numOfNodes);
  

     printf("num of nodes in the payload :%d\n",resl->first->payload->numOfNodes);

     TEST_CHECK(resl->first->payload->numOfNodes==5);
      
     PrintPayload(&(resl->first->payload));
     PrintEntryList(resl);








        
      DestroyEntryList(&l);
      DestroyEntryList(&resl);
      



       DestroyEntry(&e);  
       DestroyEntry(&e2);  
       DestroyEntry(&e3);
       DestroyEntry(&e4);
       DestroyEntry(&e5);
       DestroyEntry(&e10);
       DestroyEntry(&e11);
       DestroyEntry(&e12);
       
      
      
       DestroyHashTable(table);
       DestroyPayload(p);
       

       
}







TEST_LIST = {
      { "create_hashTable", test_create_HashTable },
       { "destroy_hashTable", test_destroy_hashTable },
    { "insert_hashTable", test_insert_hashTable },
      {"exists_hashTable", test_exists_hashTable},
      {"print_hashTable", test_print_hashTable},
      { "getFirstEntryFromHash", test_getFirstEntryFromHash },
       { "getNextEntryFromHash", test_getNextEntryFromHash},
      { "match_document_entry_list", test_match_document_HashTable},
 	     { "match_document_entry_list2", test_match_document_HashTable2},
        { NULL, NULL } // τερματίζουμε τη λίστα με NULL
 };