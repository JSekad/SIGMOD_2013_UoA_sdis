#include <stdio.h>
#include "../include/api.h"
#include "../include/acutest.h"
#define TESTRECORDSNUMBER 10


void test_create_entry(void) {

    word w[TESTRECORDSNUMBER] = {"mell","felt00000000","hall","small","tall","sol","smell","play","sail","asasda"};
    



    entry testent;

    
    for (int i = 0; i < TESTRECORDSNUMBER;i++){
            
	        TEST_CHECK(create_entry(w[i],&testent) == Working);


	        TEST_CHECK(destroy_entry(&testent) == Working);

    }


      

    TEST_CHECK(create_entry(NULL,&testent) == Failed);  


    
 
    
     

 

}

void test_destroy_entry(void) {

    word w[TESTRECORDSNUMBER] = {"mell","felt","hall","small","tall","sol","smelaaaaaaaaaaaal","play","sail","play"};
    

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
     
     word w[TESTRECORDSNUMBER][31] = {"mell","felt","hall","small","tall","sol","smelaaaaaaaaaaaal","play","sail","play"};


     entry testent;
     entry_list l;

    TEST_CHECK(create_entry("mell",&testent) == Working);

    
     
    TEST_CHECK(create_entry_list(&l)== Working);
    
    
    

    TEST_CHECK(add_entry(&l,&testent)== Working);


    TEST_CHECK(destroy_entry_list(&l)== Working);


    TEST_CHECK(destroy_entry(&testent)== Working);



 }


 void test_destroy_entry_list(){


    word w[TESTRECORDSNUMBER] = {"mell","felt","hall","small","tall","sol","smelaaaaaaaaaaaal","play","sail","play"};


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



// Λίστα με όλα τα tests προς εκτέλεση


 TEST_LIST = {
	{ "create_entry", test_create_entry },
    { "destroy_entry", test_destroy_entry },
    { "create_entry_list", test_create_entry },
    {"destroy_entry_list", test_destroy_entry_list},
    { "add_entry", test_add_entry },
	{ NULL, NULL } // τερματίζουμε τη λίστα με NULL
 };