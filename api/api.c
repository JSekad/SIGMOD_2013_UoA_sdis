#include "../include/api.h"


enum error_code create_entry(const word w, entry * e){

    ent ** temp = e;
    printf("create_entry\n");
    *temp=CreateEntry(w,NULL);
    printf("%s\n",(*e)->w);
    return Working;

}
//TODO The bellow

enum error_code destroy_entry(ent *e){
    return Working;
};

enum error_code create_entry_list(entry_list* el);

 unsigned int get_number_entries(const entry_list* el);

enum error_code add_entry(entry_list* el, const ent* e);

 ent* get_first(const entry_list* el);

 ent* get_next(const entry_list* el);

enum error_code destroy_entry_list(entry_list* el);

enum error_code build_entry_index(const entry_list* el,  MatchType type, index* ix);

enum error_code lookup_entry_index(const word* w, index* ix, int threshold, entry_list* result);

enum error_code destroy_entry_index(index* ix);