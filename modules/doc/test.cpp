#include "../../include/acutest.h"
#include "../../include/doc.h"

char doc_str[]="15 http dbpedia resource http dbpedia resource http dbpedia resource http dbpedia resource http dbpedia resource";


 void test_create_doc(void){

     doc *d=initializedoc(1,doc_str);
     
     int n=d->list_of_words->numOfNodes;
     printf("num of nodes %d\ndoc id %d\n\n",n,d->docid);
     TEST_CHECK(n==3);
     PrintEntryList(d->list_of_words);
    
     DestroyDoc(d);
      
 }


// void test_destroy_hashTable(void){


//         hashTable *table=CreateHashTable();

        
//         DestroyHashTable(table);


// }



// void test_insert_hashTable(void){




//       hashTable *table=CreateHashTable();
      
//        Payload p=NULL;
//        ent *e=CreateEntry("niaou",p);

//        ent *e2=CreateEntry("niaou",p);
       
//        insertEntry(table,e,NOUPDATE);

//        insertEntry(table,e2,NOUPDATE);


//        DestroyEntry(&e); 
//        DestroyEntry(&e2);   
//        DestroyHashTable(table);



             
   



// }

// void test_exists_hashTable(void){
//        hashTable *table=CreateHashTable();
      
//        Payload p=NULL;
//        ent *e=CreateEntry("niaou",p);
//        ent *e2=CreateEntry("niaou",p);


//        insertEntry(table,e,NOUPDATE);
//        insertEntry(table,e2,NOUPDATE);
       

//        TEST_CHECK(Exists(table,e->w)!=NULL);  

       
    
       
    
//        DestroyEntry(&e);  
//        DestroyEntry(&e2);  

//        DestroyHashTable(table);


// }



// void  test_print_hashTable(void){

//        hashTable *table=CreateHashTable();
      
//        Payload p=NULL;
//        ent *e=CreateEntry("niaou",p);
//        ent *e2=CreateEntry("niaou2",p);
//        ent *e3=CreateEntry("niaou3",p);
//        ent *e4=CreateEntry("niaou4",p);
//        ent *e5=CreateEntry("niaou5",p);

//        insertEntry(table,e, NOUPDATE);
//        insertEntry(table,e2,NOUPDATE);
//        insertEntry(table,e3,NOUPDATE);
//        insertEntry(table,e4,NOUPDATE);
//        insertEntry(table,e5,NOUPDATE);


//        PrintHashTable(table);



//        DestroyEntry(&e);  
//        DestroyEntry(&e2);  
//        DestroyEntry(&e3);
//        DestroyEntry(&e4);
//        DestroyEntry(&e5);
       
//        DestroyHashTable(table);
       
       

// }




// void  test_getFirstEntryFromHash(void){

//        hashTable *table=CreateHashTable();
      
//        Payload p=NULL;
//        ent *e=CreateEntry("niaou",p);
//        ent *e2=CreateEntry("niaou2",p);
//        ent *e3=CreateEntry("niaou3",p);
//        ent *e4=CreateEntry("niaou4",p);
//        ent *e5=CreateEntry("niaou5",p);

//        insertEntry(table,e, NOUPDATE);
//        insertEntry(table,e2,NOUPDATE);
//        insertEntry(table,e3,NOUPDATE);
//        insertEntry(table,e4,NOUPDATE);
//        insertEntry(table,e5,NOUPDATE);


//        PrintHashTable(table);
//        entry nentry=getFirstEntryFromHash(table);

//        printf("%s\n",nentry->w);
       
//        DestroyEntry(&nentry);

//        DestroyEntry(&e);  
//        DestroyEntry(&e2);  
//        DestroyEntry(&e3);
//        DestroyEntry(&e4);
//        DestroyEntry(&e5);
       
//        DestroyHashTable(table);
       
       

// }





TEST_LIST = {
       { "test_create_doc", test_create_doc },
//        { "destroy_hashTable", test_destroy_hashTable },
//     { "insert_hashTable", test_insert_hashTable },
//       {"exists_hashTable", test_exists_hashTable},
//       {"print_hashTable", test_print_hashTable},
//       { "getFirstEntryFromHash", test_getFirstEntryFromHash },
//        { "getNextEntryFromHash", test_getNextEntryFromHash},
//       { "match_document_entry_list", test_match_document_HashTable},
//  	  { "match_document_entry_list2", test_match_document_HashTable2},
       { NULL, NULL } // τερματίζουμε τη λίστα με NULL
 };