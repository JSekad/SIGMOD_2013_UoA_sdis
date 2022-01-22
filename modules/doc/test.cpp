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