#include "string.h"
#include "entry.h"
#include "entry_list.h"
#define LEN 30

typedef struct treenode
{
    char* word;
    node* next[LEN];
}node;

node* create_tree(char*);

int find_distance(char*,char*);

void add_node(node*,char*);

entry_list* get_words(node*,char *,int);

void delete_tree(node *);