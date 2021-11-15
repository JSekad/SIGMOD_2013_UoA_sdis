#ifndef MPLA
#define MPLA
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "../../include/bktree.h"
#include "../../include/distance.h"

node* create_node(char* word,entry* ent)//if tree is empty creates the root of the tree and initializes its components
{
    node* tree=NULL ;
    tree = (node*)malloc(sizeof(node));
    int a=strlen(word);
    tree->word=malloc(sizeof(char) * (++a));
    strcpy(tree->word,word);
    for(int i=0;i<LEN;i++)
    {
        tree->next[i]=NULL;
    }
    tree->ent=ent;
    return tree;
}

int find_distance(char** word1,char** word2)//finds the edit distance between two words
{
    int a=editDistance(*word1,*word2);
    return a;
}

void add_node(node** tree,char* word,entry* ent)
{
    int a=strlen(word);
    if((*tree) == NULL)
    {
        *tree=create_node(word,ent);//if tree is empty creates root
    }
    else
    {
        int b=find_distance(&((*tree)->word),&word);
        if((*tree)->next[b]!=NULL)
        {
            add_node(&((*tree)->next[b]),word,ent);//checks if current node child is occupied and if it is traverses onto that childs subtree
        }
        else
        {
            (*tree)->next[b]=create_node(word,ent);
        }
    }
    return;
}

void get_words_sub(Entry_list** res,node** tree,char* word,int n)//uses recursion to traverse the tree and find matches for given word
{
    int dis=find_distance(&((*tree)->word),&word);
    int a=dis-n;
    if(a<0)
    {
        a=0;
    }
    int b=dis+n;
    if(dis>n)
    {
        return;
    }
    else
    {
        InsertLastEntryList(*res,(*(*tree)->ent));
        for (int i = 0;(i>a) && (i<b) && (((*tree)->next[i])!=NULL) ; i++)
        {
            get_words_sub(res,(&(*tree)->next[i]),word,n);
        }
        
    }
}

entry_list* get_words(node** tree, char* word,int n)//outside function of get_word_sub stores the entry_list result
{   entry_list* res;
    *res=CreateEntryList();
    get_words_sub(res,tree,word,n);
    return res;
}

void delete_tree(node **tree)
{
    if((*tree) == NULL)
    {
        return;
    }
    for(int i=1;i<31;i++)
    {
        if (((*tree)->next[i])!=NULL)
        {
            delete_tree(&((*tree)->next[i]));
        }
        else
        {
            for (int j = 1; ((*tree)->next[j])==NULL; j++)
            {
                delete_tree(&((*tree)->next[j]));
            }
        }
    }
    free((*tree)->word);
    (*tree)->ent=NULL;
    free(*tree);
    *tree=NULL;
}

#endif