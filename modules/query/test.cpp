#include "../../include/acutest.h"
#include "../../include/entry_list.h"
#include "../../include/query.h"

char doc_str[]="http dbpedia resource http dbpedia resource http dbpedia resource http dbpedia resource http dbpedia resource";


void test_init_querry(void){

  // query *q=(query *)malloc(sizeof(query));
   query *q;
   int res=initQuery(&q,1,2,3,doc_str);
   printf("/n/n/n/n/nn%d\n",res);
   printf("id NUM %d\nmatch type %d\ndistance %d\nnumofwords %d\n",q->idNumber,q->distance,q->matchTypeId,q->words->numOfNodes);
   TEST_CHECK(q->words->numOfNodes==15);

   PrintEntryList(q->words);


   destroyQuery(q);  
   
}


void test_init_result(void){

  // query *q=(query *)malloc(sizeof(query));
   result *r;
   initResult(&r,1,100);
   
   printf("num of words %d\nid %d\n\n",r->numOfWods,r->id);
   TEST_CHECK(r->numOfWods==100);

   


     destroyResult(r);  
   
}

// void test_UpdatePayload(void){
    

//      Payload p=CreatePayload(1,1,1);


//      Payload p2=CreatePayload(1,2,3);

//      Payload p3=CreatePayload(1,1,1);


//      Payload p4=CreatePayload(1,2,3);


//      updatePayload(&p,p2->iDList->idnumber);
 
//      updatePayload(&p,p3->iDList->idnumber);
     
//      updatePayload(&p,p4->iDList->idnumber);
 

//      TEST_CHECK(p->numOfNodes==4);
      
//      PrintPayload(&p); 

 
//      DestroyPayload(p); 
//      DestroyPayload(p2);
   
// }






// void test_create_Payload(void){
    

//       hashTable *table=CreateHashTable();
    
//        Payload p=CreatePayload(-1,-1,-1);
//        ent *e=CreateEntry("niaou",p);
//        ent *e2=CreateEntry("niaou2",p);
//        ent *e3=CreateEntry("niaou3",p);
//        ent *e4=CreateEntry("niaou4",p);
//        ent *e5=CreateEntry("niaou5",p);

//        insertEntry(table,e, UPDATE);
//        insertEntry(table,e2,UPDATE);
//        insertEntry(table,e3,UPDATE);
//        insertEntry(table,e4,UPDATE);
//       insertEntry(table,e5,UPDATE);


//        Entry_list *l = CreateEntryList();
        
//        InsertLastEntryList(l,e);  
//        InsertLastEntryList(l,e2);
//        InsertLastEntryList(l,e3);
//        InsertLastEntryList(l,e4); 
       
//        ent *e10=CreateEntry("niaou10",p);
//        ent *e11=CreateEntry("niaou11",p);
//        ent *e12=CreateEntry("niaou12",p);

//        InsertLastEntryList(l,e10);  
//        InsertLastEntryList(l,e11);
//        InsertLastEntryList(l,e12);
        
       
       
       
       
//       Entry_list *resl=MatchDocumentHashTable(table,l); 
      




//      TEST_CHECK(resl->numOfNodes==4);


//      PrintEntryList(resl);








        
//       DestroyEntryList(&l);
//       DestroyEntryList(&resl);
      



//        DestroyEntry(&e);  
//        DestroyEntry(&e2);  
//        DestroyEntry(&e3);
//        DestroyEntry(&e4);
//        DestroyEntry(&e5);
//        DestroyEntry(&e10);
//        DestroyEntry(&e11);
//        DestroyEntry(&e12);
       
      
      
//   //     DestroyHashTable(table);
       
       


   
// }


TEST_LIST = {
     { "init_querry", test_init_querry },
    { "test_init_result", test_init_result },
  //  { "insert_hashTable", test_insert_hashTable },
  //   {"exists_hashTable", test_exists_hashTable},
   //  {"print_hashTable", test_print_hashTable},
   ///  { "getFirstEntryFromHash", test_getFirstEntryFromHash },
   //   { "getNextEntryFromHash", test_getNextEntryFromHash},
   //  { "match_document_entry_list", test_match_document_HashTable},
	 { NULL, NULL } // τερματίζουμε τη λίστα με NULL
 };