#include "../../include/vector.h"

void vector_init(vector *v,int capacity)
{
    v->capacity = capacity;
    v->total = 0;
    v->items = (void**)malloc(sizeof(void *) * v->capacity);
}

int vectorResize(vector *v, int capacity)
{
    int  status = UNDEFINE;
    if(v)
    {
        void **items =(void**) realloc(v->items, sizeof(void *) * capacity);
        if (items)
        {
            v->items = items;
            v->capacity = capacity;
            status = SUCCESS;
        }
    }
    return status;
}

int vectorPushBack(vector *v, void *item)
{
    int  status = UNDEFINE;
    if(v)
    {
        if (v->capacity == v->total)
        {
            status = vectorResize(v, v->capacity * 2);
            if(status != UNDEFINE)
            {
                v->items[v->total++] = item;
            }
        }
        else
        {
            v->items[v->total++] = item;
            status = SUCCESS;
        }
    }
    return status;
}

int vectorSet(vector *v, int index, void *item)
{
    int  status = UNDEFINE;
    if(v)
    {
        if ((index >= 0) && (index < v->total))
        {
            v->items[index] = item;
            status = SUCCESS;
        }
    }
    return status;
}

void *vectorGet(vector *v, int index)
{   bool gotIn = false ;
    void *readData = NULL;
    if(v)
    {
        //  printf("vectorGet v!=NULL with index %d\n",index);
        //  printf("vectorGet v!=NULL with v->total %d\n",v->total);
        if ((index >= 0) && (index < v->total))
        {
            // printf("vectorGet v!=NULL index>=0 index < v->total %d\n",v->total);
            readData = v->items[index];
            gotIn=true;
        }
       if (gotIn) {
            //    printf("vectorGet v!=NULL 2  got in \n"); 
           }else{
            //    printf("vectorGet v!=NULL 2 DID NOT got in \n");
               }

    }
    return readData;
}

int vectorFree(vector *v)
{
    int  status = UNDEFINE;
    if(v)
    {
        free(v->items);
        v->items = NULL;
        status = SUCCESS;
    }
    return status;
}

int vectorTotal(vector *v)
{
    int totalCount = UNDEFINE;
    if(v)
    {
        totalCount = v->total;
    }
    return totalCount;
}