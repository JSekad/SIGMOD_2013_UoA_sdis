#include "../../include/acutest.h"
#include "../../include/entry_list.h"
#include "../../include/query.h"

char doc_str[]="http dbpedia resource http dbpedia resource http dbpedia resource http dbpedia resource http dbpedia resource";


void test_init_querry(void){

 
   query *q;
   int res=initQuery(&q,1,2,3,doc_str);
   printf("/n/n/n/n/nn%d\n",res);
   printf("id NUM %d\nmatch type %d\ndistance %d\nnumofwords %d\n",q->idNumber,q->distance,q->matchTypeId,q->words->numOfNodes);
   TEST_CHECK(q->words->numOfNodes==15);

   PrintEntryList(q->words);


   destroyQuery(q);  
   
}


void test_init_result(void){

   result *r;
   initResult(&r,1,100);
   
   printf("num of words %d\nid %d\n\n",r->numOfWods,r->id);
   TEST_CHECK(r->numOfWods==100);

   


     destroyResult(r);  
   
}











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