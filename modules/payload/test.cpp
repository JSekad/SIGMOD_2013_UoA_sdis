#include "../../include/acutest.h"
#include "../../include/entry_list.h"
#include "../../include/hashTable.h"



void test_create_Payload(void){
    

     Payload p=CreatePayload(1,1,1);

    changePayloadThreshHold(&p,10);
    printf("THESHHHHHH %d",p->thresholdFount);
    DestroyPayload(p);

   
}


void test_UpdatePayload(void){
    

     Payload p=CreatePayload(1,1,1);


     Payload p2=CreatePayload(1,2,3);

     Payload p3=CreatePayload(1,1,1);


     Payload p4=CreatePayload(1,2,3);


     updatePayload(&p,p2->iDList->idnumber);
 
     updatePayload(&p,p3->iDList->idnumber);
     
     updatePayload(&p,p4->iDList->idnumber);
 

     TEST_CHECK(p->numOfNodes==4);
      
     PrintPayload(&p); 

 
     DestroyPayload(p); 
     DestroyPayload(p2);
   
}









TEST_LIST = {
     { "create_payload", test_create_Payload },
    { "tUpdatePayload", test_UpdatePayload },
 
	 { NULL, NULL } // τερματίζουμε τη λίστα με NULL
 };