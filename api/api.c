#include "../include/api.h"


enum error_code create_entry(const word w, entry * e){
    ent ** temp = e;
    *temp=CreateEntry(w,NULL);
    if (*temp != NULL) {
        return Working;
    }else{
        return Failed;
    }

}

enum error_code destroy_entry(entry *e){
    ent **temp=e;
    DestroyEntry(temp);
    if (*temp==NULL){
        return Working;
    }else{
        return Failed;
    }
};

enum error_code create_entry_list(entry_list* el){
    Entry_list **temp=el;
    *temp=CreateEntryList();
    if (*el != NULL) {
        return Working;
    }else{
        return Failed;
    }
};

enum error_code add_entry(entry_list* el, const entry* e) {
    Entry_list **tempEntEl = el;
    InsertLastEntryList(*tempEntEl, *e);
    if (!strcmp((*tempEntEl)->last->w,(*e)->w)) {
        return Working;
    }else{
        return Failed;
    }
}

unsigned int get_number_entries(const entry_list* el){
    return (*el)->numOfNodes;
};


entry* get_first(const entry_list* el){
    return getFirstEntryOfList(*el);
};

entry* get_next(const entry_list* el){
    return getNextEntryOfList(*el);
};

enum error_code destroy_entry_list(entry_list* el){
    Entry_list **temp=el;
    DestroyEntryList(temp);
    if(*temp==NULL) {
        return Working;
    }else{
        return Failed;
    }
};

enum error_code build_entry_index(const entry_list* el,  MatchType type, inDex * ix){
    entry * testIterator;
    node *tempTree=NULL;
    testIterator=getFirstEntryOfList(*el);
    if (testIterator == NULL)
        return Failed;
    while(testIterator!=NULL) {
        add_node(&tempTree,(*testIterator)->w,testIterator);
        printf("%s\n", (*testIterator)->w);
        testIterator = getNextEntryOfList(*el);
    }
    *ix=tempTree;
    return Working;
};

enum error_code lookup_entry_index(const word* w, inDex* ix, int threshold, entry_list* result){
    Entry_list **tempEntEl = result;
    get_words_sub(tempEntEl,ix,*w,threshold);
    PrintEntryList(*result);
    return Working;
};

enum error_code destroy_entry_index(inDex * ix){
    delete_tree(ix);
    if (*ix == NULL) {
        return Working;
    }else{
        return Failed;
    }
};