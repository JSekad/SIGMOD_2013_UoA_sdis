#ifndef BKTREE
#define BKTREE
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "distance.h"

#include "entry_list.h"
#define LEN 30
typedef struct treenode node;
typedef node* inDex;

struct treenode
{
    char* word;
    ent* entp;
    node* next[LEN];
};


node* create_node(char*,entry*);

int find_distance(char** word1,char** word2,distanceAlgo distAlgo);

void add_node(node** tree,char* word,entry* ent,distanceAlgo distAlgo);

void get_words_sub(Entry_list**,node**,char*,int,distanceAlgo distAlgo);

void get_words(node** tree, char* word,int n,Entry_list** resel,distanceAlgo distAlgo);

void delete_tree(node **);
void delete_tree2(node *);

void print_tree_test(node *);

#endif
 