#ifndef QUERY
#define QUERY

#include "entry_list.h"
#include <stdio.h>
#include <string.h>
typedef struct Query{
    int idNumber;
    int matchTypeId;
    int distance;
    int numOfWords;
    Entry_list* words;
    int flag; // If still exists 1 exists 0 deleted
} query;

typedef struct Result{
    int id;
    int numOfWods;
    int* words;
}result;

int initResult(result **r,int id,int numofwords);
int destroyResult(result * r);




int initQuery(query**,int idNumber,int matchTypeId,int distance,char* concatWords);
void PrintQuery(query* );

int destroyQuery(query*);




#endif