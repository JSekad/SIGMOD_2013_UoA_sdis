#include "entry_list.h"
#define LEN 30
typedef struct treenode node;
typedef node* inDex;

struct treenode
{
    char* word;
    ent* ent;
    node* next[LEN];
};

node* create_node(char*,entry*);

int find_distance(char**,char**);

void add_node(node**,char*,entry*);

void get_words_sub(Entry_list**,node**,char*,int);

void get_words(node** tree, char* word,int n,Entry_list** resel);

void delete_tree(node **);
 