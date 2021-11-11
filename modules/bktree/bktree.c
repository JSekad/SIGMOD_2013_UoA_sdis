#ifndef MPLA
#define MPLA
#include "stdio.h"
#include "bktree.h"
#include "distance.h"

node* create_tree(char* word)//if tree is empty creates the root of the tree and initializes its components
{
    node* tree = malloc(sizeof(node));
    int a=strlen(word);
    tree->word=malloc(sizeof(char) * (++a));
    strcpy(tree->word,word);
    for(int i=0;i<LEN;i++)
    {
        tree->next[i]=NULL;
    }
    return tree;
}

int find_distance(char* word1,char* word2)//finds the edit distance between two words
{
    return editDistance(word1,word2);
}

void add_node(node* tree,char* word)
{
    int a=strlen(word);
    if(tree == NULL)
    {
        create_tree(word);//if tree is empty creates root
    }
    else
    {
        if(tree->next[find_distance(tree->word,word)]!=NULL)
        {
            add_node(tree->next[find_distance(tree->word,word)],word);//checks if current node child is occupied and if it is traverses onto that childs subtree
        }
        else
        {
            tree->next[find_distance(tree->word,word)]=malloc(sizeof(node));//if current child is unoccupied  creates that node and initializes its components
            tree->next[find_distance(tree->word,word)]->word=malloc(sizeof(char) * (++a));
            strcpy(tree->next[find_distance(tree->word,word)]->word,word);
            for(int i=0;i<LEN;i++)
            {
            tree->next[i]=NULL;
            }
        }
    }
    return;
}

entry_list* get_words(node* tree, char* word,int n)
{
    char* posmatch[30];
    entry_list *res=CreateEntryList();
    posmatch[1]=tree->word;
    int dis=find_distance(posmatch[1],word);
    if(dis <= n)
    {
        
    }
    else
    {
        return;
    }
}

void delete_tree(node *tree)
{
    node* temp= tree;
    for(int i=0;i<LEN || temp->next[i]==NULL;i++)
    {
        delete_tree(temp->next[i]);
        free(temp->next[i]);
    }
    free(tree);
}

#endif