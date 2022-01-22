#include "../../include/bktree.h"

node* create_node(char* word,entry* ent)//if tree is empty creates the root of the tree and initializes its components
{
    node* tree=NULL ;
    tree = (node*)malloc(sizeof(node));
    int a=strlen(word);
    tree->word=(char*)malloc(sizeof(char) * (++a));
    strcpy(tree->word,word);
    for(int i=0;i<=LEN;i++)
    {
        tree->next[i]=NULL;
    }
    tree->entp = CreateEntry((*ent)->w,(*ent)->payload);
    return tree;
}

int find_distance(char** word1,char** word2,distanceAlgo distAlgo)//finds the edit distance between two words
{
    int a;
    if (distAlgo==EDIT_DIST){
        a=editDistance(*word1,*word2);
        return a;
    }else if(distAlgo==HAMMING_DIST){
//  printf("Im inside Distance----------------%s/-------%s/--------------------\n",*word1,*word2);
        a= hammingDistance(*word1,*word2);
        return a;
    }
    return 0;
}

void add_node(node** tree,char* word,entry* ent,distanceAlgo distAlgo)
{
//    int a=strlen(word);
    if((*tree) == NULL)
    {
        *tree=create_node(word,ent);//if tree is empty creates root
    }
    else
    {
//        printf("Im inside Distance----------------%s/-------%s/--------------------\n",&((*tree)->word),&word);
        int b=find_distance(&((*tree)->word),&word,distAlgo);
        if(b==0 && (*tree)->entp->payload->distance == (*ent)->payload->distance)
        {
            updatePayload(&((*tree)->entp->payload),(*ent)->payload->iDList->idnumber);
            return;
        }
        if((*tree)->next[b]!=NULL)
        {
            add_node(&((*tree)->next[b]),word,ent,distAlgo);//checks if current node child is occupied and if it is traverses onto that childs subtree
        }
        else
        {
            (*tree)->next[b]=create_node(word,ent);
        }
    }
    return;
}

void get_words_sub(Entry_list** res,node** tree,char* word,int n,distanceAlgo distAlgo)//uses recursion to traverse the tree and find matches for given word
{   
  //  printf("Im inside Distance----------------%s/-------%s/--------------------\n",((*tree)->word),word);
    int dis=find_distance(&((*tree)->word),&word,distAlgo);
    int a=dis-n;
    if(a<0)
    {
        a=0;
    }
    int b=dis+n;
    if(dis<=n &&(*tree)->entp->payload->distance==n)
    {
        InsertLastEntryList(*res,(*tree)->entp);
        //changePayloadThreshHold(&((*res)->last->payload),n);
    }
   // else
    {
        //changePayloadThreshHold(&((*tree)->entp->payload),n);
        //(*tree)->entp->payload->thresholdFount=n;
        //InsertLastEntryList(*res,(*tree)->entp);
        //changePayloadThreshHold(&((*res)->last->payload),n);
        for (int i = a;(i<=b) ; i++)
        {
            if(((*tree)->next[i])!=NULL) {
                get_words_sub(res, (&(*tree)->next[i]), word, n,distAlgo);
            }
        }
    }
}
void get_words(node** tree, char* word,int n,Entry_list** resel,distanceAlgo distAlgo)//outside function of get_word_sub stores the entry_list result
{   *resel=CreateEntryList();
    get_words_sub(resel,tree,word,n,distAlgo);
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
            for (int j = 0; ((*tree)->next[j])==NULL; j++)
            {
                delete_tree(&((*tree)->next[j]));
            }
        }
    }
    free((*tree)->word);
    DestroyEntry(&(*tree)->entp);
    free(*tree);
    *tree=NULL;
}

void delete_tree2(node *tree)
{
    if((tree) == NULL)
    {
        return;
    }
    for(int i=1;i<31;i++)
    {
        if (((tree)->next[i])!=NULL)
        {
            delete_tree2(tree->next[i]);
        }
        else
        {
            for (int j = 1; (tree->next[j])==NULL; j++)
            {
                delete_tree2(tree->next[j]);
            }
        }
    }
    free(tree->word);
    DestroyEntry(&(tree->entp));
    free(tree);
    tree=NULL;
}

void print_tree_test(node *tree)
{
    if(tree==NULL)
    {
        return;
    }
    printf("%s,",tree->word);
    PrintPayload(&(tree->entp->payload));
    for(int i=1;i<31;i++)
    {
        if((tree->next[i])!=NULL)
        {
            print_tree_test((tree->next[i]));
        }
        else
        {
            for(int j=1;(tree->next[j])==NULL;j++)
            {
                print_tree_test((tree->next[j]));
            }
        }
    }

}
