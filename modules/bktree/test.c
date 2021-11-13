#include "../../include/bktree.h"
#include "../../include/distance.h"
#include <stdio.h>

int main(){



  printf("%d\n",editDistance("henn","smell"));

  node *tree = create_tree("smell");


  add_node(tree,"henn");

  add_node(tree,"hell");
   
  



  

  delete_tree(tree);



  
  
  return 0;
  
}