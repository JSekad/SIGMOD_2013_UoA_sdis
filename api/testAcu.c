#include <stdio.h>
#include "../include/api.h"
#include "../include/acutest.h"
#define TESTRECORDSNUMBER 7


void test_create_entry(void) {

    word w[TESTRECORDSNUMBER] ={"hell","help","fall","felt","fell","small","melt"};

    entry testent;

    for (int i = 0; i < TESTRECORDSNUMBER;i++){
            
	        TEST_CHECK(create_entry(w[i],&testent) == Working);
	        TEST_CHECK(destroy_entry(&testent) == Working);
    }

    TEST_CHECK(create_entry(NULL,&testent) == Failed);

}

void test_destroy_entry(void) {

    word w[TESTRECORDSNUMBER] = {"hell","help","fall","felt","fell","small","melt"};
    entry testent;

 for (int i = 0; i < TESTRECORDSNUMBER;i++){
 	TEST_CHECK(create_entry(w[i],&testent) == Working);
	TEST_CHECK(destroy_entry(&testent) == Working);
 }


}



 void test_create_entry_list(void){
     
     entry_list l;

     for (int i = 0; i < TESTRECORDSNUMBER;i++){
         TEST_CHECK(create_entry_list(&l)== Working);
         TEST_CHECK(destroy_entry_list(&l)== Working);
     }

 }


  

 void test_add_entry(void){
     
     word w[TESTRECORDSNUMBER][31] = {"hell","help","fall","felt","fell","small","melt"};
     entry testent;
     entry_list l;

    TEST_CHECK(create_entry("mell",&testent) == Working);
    TEST_CHECK(create_entry_list(&l)== Working);
    TEST_CHECK(add_entry(&l,&testent)== Working);
    TEST_CHECK(destroy_entry_list(&l)== Working);
    TEST_CHECK(destroy_entry(&testent)== Working);

 }


 void test_destroy_entry_list(){


    word w[TESTRECORDSNUMBER] = {"hell","help","fall","felt","fell","small","melt"};
    entry testent;
    entry_list l;
    TEST_CHECK(create_entry_list(&l)== Working);
 

    for (int i = 0; i < TESTRECORDSNUMBER;i++){
        TEST_CHECK(create_entry(w[i],&testent)== Working);
        TEST_CHECK(add_entry(&l, &testent) == Working);
        TEST_CHECK(destroy_entry(&testent) == Working);
    
    }
    TEST_CHECK(destroy_entry_list(&l)== Working);
 
 }






 void  test_build_entry_index(){

      //Creating entries and lisofentries

    char words[TESTRECORDSNUMBER][31] = {"hell","help","fall","felt","fell","small","melt"};


    entry_list  testel = NULL;
//
    TEST_CHECK(Working == create_entry_list(&testel)); 
    

    entry testent;

    for (int i=0; i<TESTRECORDSNUMBER; i++) {
        TEST_CHECK(Working == create_entry(words[i], &testent));
        TEST_CHECK((Working == add_entry(&testel,&testent)));
        
        TEST_CHECK(Working == destroy_entry(&testent));
        TEST_CHECK(testent==NULL);
                
        
    }

   // printf("Number of Entries %d\n", get_number_entries(&testel));


    entry * testIterator;

    testIterator=get_first(&testel);
    while(testIterator!=NULL) {
        testIterator = get_next(&testel);
    }

    node * tempTree = NULL;
    TEST_CHECK(build_entry_index(&testel,MT_EDIT_DIST,&tempTree)== Working);

    //UNTIL HERE THERE IS A LIST OF ENTRIES

    TEST_CHECK(Working == destroy_entry_list(&testel));
    TEST_CHECK(Working == destroy_entry_index(&tempTree));

 }


void  test_look_up_entry_index(){

    //Creating entries and lisofentries

    char words[TESTRECORDSNUMBER][31] = {"hell","help","fall","felt","fell","small","melt"};


    entry_list  testel = NULL;
//
    TEST_CHECK(Working == create_entry_list(&testel));


    entry testent;

    for (int i=0; i<TESTRECORDSNUMBER; i++) {
        TEST_CHECK(Working == create_entry(words[i], &testent));
        TEST_CHECK((Working == add_entry(&testel,&testent)));

        TEST_CHECK(Working == destroy_entry(&testent));
        TEST_CHECK(testent==NULL);

    }

    // printf("Number of Entries %d\n", get_number_entries(&testel));


    entry * testIterator;

    testIterator=get_first(&testel);
    while(testIterator!=NULL) {
        testIterator = get_next(&testel);
    }

    node * tempTree = NULL;
    TEST_CHECK(build_entry_index(&testel,MT_EDIT_DIST,&tempTree)== Working);


    TEST_CHECK (Working == destroy_entry_list(&testel));

    word w= "henn";

    entry_list  testResultList = NULL;

    TEST_CHECK (Working == lookup_entry_index(&w,&tempTree,2,&testResultList));



    TEST_CHECK (Working == destroy_entry_index(&tempTree));

    TEST_CHECK (Working == destroy_entry_list(&testResultList));

}

// Λίστα με όλα τα tests προς εκτέλεση


 TEST_LIST = {
	{ "create_entry", test_create_entry },
    { "destroy_entry", test_destroy_entry },
    { "create_entry_list", test_create_entry },
    {"destroy_entry_list", test_destroy_entry_list},
    { "add_entry", test_add_entry },
    { "build_entry_index", test_build_entry_index },
    { "look_up_entry_index", test_look_up_entry_index},
	{ NULL, NULL } // τερματίζουμε τη λίστα με NULL
 };