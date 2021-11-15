#include <stdio.h>
#include "../include/api.h"

#define TESTRECORDSNUMBER 7

int main() {

    //Creating entries and lisofentries

    char words[TESTRECORDSNUMBER][31] = {"hell","help","fall","felt","fell","small","melt"};


    entry_list  testel = NULL;
//
    if (Working == create_entry_list(&testel)) {
        printf("Initialize list\n");
    }


    entry testent;

    for (int i=0; i<TESTRECORDSNUMBER; i++) {
        if (Working == create_entry(words[i], &testent)) {
            printf("Create entry \"%s\" is working \n", (testent)->w);
            if (Working == add_entry(&testel,&testent)) {
                printf("Create entry \"%s\" is working \n", (testent)->w);
            }
        }
        if (Working == destroy_entry(&testent)) {
            if ((testent)==NULL){
                printf("Delete Working fine\n");
            }
        }
    }

    printf("Number of Entries %d\n", get_number_entries(&testel));


    entry * testIterator;

    testIterator=get_first(&testel);
    while(testIterator!=NULL) {
        printf("%s\n", (*testIterator)->w);
        testIterator = get_next(&testel);
    }

    node * tempTree = NULL;
    build_entry_index(&testel,MT_EDIT_DIST,&tempTree);



    //UNTIL HERE THERE IS A LIST OF ENTRIES

    if (Working == destroy_entry_list(&testel)) {
        printf("Delete Working fine\n");
    }


    word w= "henn";

    entry_list  testResultList = NULL;

    if (Working == lookup_entry_index(&w,&tempTree,2,&testResultList)){
        printf("Results have come\n");
    }

    PrintEntryList(testResultList);


    if (Working == destroy_entry_index(&tempTree)){
        printf("Delete tree Working fine\n");
    }

    if (Working == destroy_entry_list(&testResultList)) {
        printf("Delete Working fine\n");
    }

    printf("\nall done well\n"
           "---------------------\n"
           "---------------------\n\n");



    return 0;

}