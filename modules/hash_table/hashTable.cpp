#include "../../include/hashTable.h"

hashTable *CreateHashTable()  {
    hashTable *hash=(hashTable*)malloc(sizeof(hashTable));
    hash->sizeOfHash=SIZEOFHASH;
    hash->current=0;
    hash->sizeofInput=0;
    for (int i=0 ; i<hash->sizeOfHash ; i++){

        hash->entrylist[i]= NULL;

    }

    return hash;
}

void DestroyHashTable(hashTable *hash) {

    for (int i=0 ; i<hash->sizeOfHash ; i++){

        if (hash->entrylist[i])
            DestroyEntryList(&hash->entrylist[i]);
    }
    free(hash);

}



int HashFuction(hashTable *hash,char* key){
    // printf("HashFuction size of hash %d\n",hash->sizeOfHash);
    int h=0, a=33;
    for (; *key!='\0'; key++)
        h=(a*h + *key) % hash->sizeOfHash;

    return h;
}



int insertEntry(hashTable *hash,ent *e,HasInsertionType type){


    hash->sizeofInput++;
    //  printf("%s",e->w);
    int pos=0;
    pos=HashFuction(hash,e->w);

    // printf("%d\n\n\n",pos);

    if (hash->entrylist[pos]==NULL){


//              printf("is null\n");

        hash->entrylist[pos]=CreateEntryList();
        InsertLastEntryList(hash->entrylist[pos],e);
        return 1;

    }
    else{
        ent *e2=searchEntryList(hash->entrylist[pos],e->w);
        //printf("e2 in insertEntry %s\n\n\n\n",e2->w);
        if (e2==NULL){
            InsertLastEntryList(hash->entrylist[pos],e);
            return 1;
        }
        else{
            if (type==UPDATE){
                updatePayload(&(e2->payload),e->payload->iDList->idnumber);
                return 1;
            }
            if (type==NOUPDATE){
               hash->sizeofInput--;

                return 0;
            }
        }

    }

     return 0;


}


entry*   Exists(hashTable *hash,word w){

    int pos=HashFuction(hash,w);


    if(hash->entrylist[pos]!=NULL){
        //PrintEntryList(hash->entrylist[pos]);
        entry* e=getFirstEntryOfList(hash->entrylist[pos]);
        while ((strcmp((*e)->w, w)!=0)){
            e=getNextEntryOfList(hash->entrylist[pos]);
            if (e==NULL) return NULL;
        }
        return e;
    }

    return NULL;

}




void PrintHashTable(hashTable *hash){
    for (int i=0;i<hash->sizeOfHash ; i++){

        if(hash->entrylist[i]!=NULL){
            printf("in hash array index %d\n",i);
            PrintEntryList(hash->entrylist[i]);
        }
    }
}


entry  getFirstEntryFromHash(hashTable *hash){


    for (int i=0;i<hash->sizeOfHash;i++){
        if(hash->entrylist[i]!=NULL){
            hash->current=i;
            entry *e=getFirstEntryOfList(hash->entrylist[i]);
            entry e2=CreateEntry((*e)->w,(*e)->payload);
            return e2;
        }

    }

    return NULL;


}


entry  getNextEntryFromHash(hashTable *hash){


    for (int i=hash->current ; i<hash->sizeOfHash ; i++){

        if(hash->entrylist[i]!=NULL){
            hash->current=i;
            if ((hash->entrylist[i])->current==NULL){
                entry *e=getFirstEntryOfList(hash->entrylist[i]);
                entry e2=CreateEntry((*e)->w,(*e)->payload);
                return e2;
            }
            else{

                entry *e=getNextEntryOfList(hash->entrylist[i]);
                if (e!=NULL){
                    entry e2=CreateEntry((*e)->w,(*e)->payload);
                    return e2;
                }

            }


        }

    }

    return NULL;

}






Entry_list * MatchDocumentHashTable(hashTable *h,Entry_list *l){

    Entry_list *reslist=CreateEntryList();
    entry *e=getFirstEntryOfList(l);
    while  (e!=NULL){
       entry *cure=Exists(h,(*e)->w); 
       if (cure!=NULL){

           InsertLastEntryList(reslist,*cure);
           changePayloadThreshHold(&(reslist->last->payload),0);
       }
       e=getNextEntryOfList(l);       
    }
    return reslist;
}





//      void HashTable::deleteByid(int id){


//         int pos = HashFuction(id);



//         hasharray[pos].eraseNode(id);


//      }


//      void HashTable::lookUP(int id){

//         if (!ifExists(id)){
//           cout<<"- Student "<<id<<"does not exist"<<endl;
//           return;
//         }


//         int pos=HashFuction(id);


//         Listnode *node=hasharray[pos].returnNodeById(id);
//         node->getItem()->printInfo();
//      }




//      Student* HashTable::getStudent(int id){

//         int pos=HashFuction(id);



//        Listnode *n = hasharray[pos].returnNodeById(id);

//         return n->getItem();


//      }
