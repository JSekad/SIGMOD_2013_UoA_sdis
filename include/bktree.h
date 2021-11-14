#include "entry_list.h"
#define LEN 30
typedef struct treenode node;
typedef node* inDex;

struct treenode
{
    char* word;
    entry* ent;
    node* next[LEN];
};

node* create_node(char*,entry*);

int find_distance(char**,char**);

void add_node(node**,char*,entry*);

entry_list* get_words(node**,char *,int);

void delete_tree(node **);
 