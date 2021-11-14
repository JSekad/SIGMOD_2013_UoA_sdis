#include <stdio.h>
#include "../../include/bktree.h"

int main(void)
{
    ent* ent=NULL;
    char* arr[]={"hell","help","fall","felt","fell","small","melt"};
    node* tree1=NULL;
    node** tree=&tree1;
    for(int i=0;i<=6;i++)
    {
        add_node(tree,arr[i],&ent);
    }
    printf("in test testing if tree is correct %s \n",(*tree)->next[2]->next[3]->word);
    delete_tree(tree);
    for (int i = 0; i < 10; i++)
    {
        if((*tree)!=NULL)
    {
        printf("tree still here %s\n" , (*tree)->next[i]->word);
    }
    }
    
    if((*tree)!=NULL)
    {
        printf("tree still here %s\n" , (*tree)->word);
    }  
    return 0;
}