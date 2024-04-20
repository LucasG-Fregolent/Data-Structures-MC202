#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "otimizar.h"
#define MAX 11

/*
To create a tree from the input:
if input[p] == '(', then create a new node in the tree with the operator '.' (undefined)
else if input[p] == 'n' (9<=n<=0), then create two nodes conected to the last node with operator '.'
else break
*/

int main(){
    char *optimized;
    
    pHead tree = createTree();
    
    tree->root = plantTree(tree->root);

    optimized = trimTree(tree->root);

    printf("%s\n", optimized);
    
    // free(optimized);

    // burnTree(tree->root);

    return 0;
}
