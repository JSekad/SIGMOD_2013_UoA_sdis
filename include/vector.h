#ifndef VECTOR
#define VECTOR

#define STARTING_VERTORS_CAPACITY 4000

#define UNDEFINE  -1
#define SUCCESS 0

#include "stdio.h"
#include "string.h"
#include "stdlib.h"

typedef struct sVectorList
{
    void **items;
    int capacity;
    int total;
} vector;

void vector_init(vector *v,int capacity);

int vectorTotal(vector *);

int vectorResize(vector *, int);

int vectorPushBack(vector *, void *);

int vectorSet(vector *, int, void *);

void* vectorGet(vector *, int);

int vectorFree(vector *);


#endif