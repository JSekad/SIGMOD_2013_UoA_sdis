#include "../../include/doc.h"
doc* initializedoc(int id,char* wordsofdoc)
{
    int counter=0;
    //printf("initializedoc %s\n",wordsofdoc);
    hashTable* ht=CreateHashTable();
    char* token;
    char  del[]=" ";

    doc* docu=(doc*)malloc(sizeof(doc));
    docu->docid=id;

    docu->list_of_words=CreateEntryList();
    token=strtok(wordsofdoc,del);
    while (token != NULL)
    {
        counter++;
        ent* Entry = CreateEntry(token,NULL);

        if(insertEntry(ht,Entry,NOUPDATE))
        {
            InsertLastEntryList(docu->list_of_words,Entry);
            DestroyEntry(&Entry);
            token=strtok(NULL,del);
        }
        else
        {
            DestroyEntry(&Entry);
            token=strtok(NULL,del);
        }
    }
    free(token);
    docu->numofwords=counter;
    DestroyHashTable(ht);

    docu->qIdResults=(vector*)malloc(sizeof(vector));  
    vector_init(docu->qIdResults,STARTING_VERTORS_CAPACITY);
    return docu;
}



void DestroyDoc(doc *d){

    for(int i=0;i<d->qIdResults->total;i++){
        free((unsigned int *)d->qIdResults->items[i]);
    }
    vectorFree(d->qIdResults);

    DestroyEntryList(&(d->list_of_words));
    
    free(d);


}