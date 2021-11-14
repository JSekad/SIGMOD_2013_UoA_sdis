#ifndef MPLA
#define MPLA
#include "stdio.h"
#include "string.h"
#include "bktree.h"
#include "stdlib.h"
#include "distance.h"

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
    printf("\nin find");
    int a=editDistance(*word1,*word2);
    printf("\nedit distane is %d\n",a);
    return a;
}

void add_node(node** tree,char* word,entry* ent)
{
    printf("\n before find %s ",word);
    int a=strlen(word);
    printf("\n strlen of %s is %d\n",word,a);
    if((*tree) == NULL)
    {
        printf("\ncreate tree\n");
        *tree=create_node(word,ent);//if tree is empty creates root
        printf("\ncreate tree with word %s\n",(*tree)->word);
    }
    else
    {
        int b=find_distance(&((*tree)->word),&word);
        if((*tree)->next[b]!=NULL)
        {
            printf("\nanother word exists with same edit distance\n");
            add_node(&((*tree)->next[b]),word,ent);//checks if current node child is occupied and if it is traverses onto that childs subtree
        }
        else
        {
            printf("\nfound a spot for word\n");
            (*tree)->next[b]=create_node(word,ent);
        }
    }
    return;
}

entry_list* get_words(node** tree, char* word,int n)
{
    char* posmatch[30];
    entry_list *res=CreateEntryList();
    posmatch[1]=(*tree)->word;
    int dis=find_distance(posmatch[1],word);
    if(dis <= n)
    {
        InsertLastEntryList(res,(*tree)->ent);
    }
    else
    {
        return;
    }
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
            for (int j = 1; (((*tree)->next[j])==NULL); j++)
            {
                delete_tree(&((*tree)->next[j]));
            }
        }
    }
    printf("deleting %s\n",(*tree)->word);
    free((*tree)->word);
    (*tree)->ent=NULL;
    free(*tree);
    *tree=NULL;
}

#endif