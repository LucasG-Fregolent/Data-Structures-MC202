#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 11
#define INFINITY (2e31)-1

typedef struct bTree *pbTree; // pbTree stands for "pointer to binary tree"
typedef struct head *pHead;

struct bTree{
    char *data;
    pbTree left, right;
};

struct head{
    pbTree root;
};

// General algorithms
int isAlphabet(char letter){
    // Return true (0) if a given char is an alphabet letter
    char *alphabet = "abcdefghijklmnopqrstuvwxyz";
    for(int i=0; i<strlen(alphabet); i++){
        if(alphabet[i]==letter){
            return 0;
        }
    }
    return 1;
}
// General algorithm = END

// TREE ALGORITHMS
pHead createTree(){
    pHead tree;
    tree = malloc(sizeof(struct head));
    tree->root = NULL;
    return tree;
}

void burnTree(pbTree tree){
    /*
    Function to destroy the tree
    */
    if(tree->left==NULL && tree->right==NULL){
        free(tree->data);
        free(tree);
        return;
    }

    burnTree(tree->left);
    burnTree(tree->right);

    free(tree->data);
    free(tree);
}

void printTree(pbTree tree){
    printf("%s ", tree->data);
    if(tree->left==NULL && tree->right==NULL){
        return;
    }
    
    if(tree->left!=NULL){
        printTree(tree->left);
    }

    if(tree->right!=NULL){
        printTree(tree->right);
    }
}

pbTree plantTree(pbTree tree){
    /*
    Recursive function to create the binary tree from the input
    */
    char buffer[MAX];
    scanf(" %s", buffer);
    

    if(buffer[0]=='('){
        pbTree newNode;
        newNode = malloc(sizeof(struct bTree));
        char *newText;

        newText = malloc(5*sizeof(char));

        strcpy(newText, ".");
        
        newNode->data = newText;
        newNode->left = plantTree(newNode);
        newNode->right = plantTree(newNode);
        return newNode;

    }
    else if((buffer[0]>='0' && buffer[0]<='9') || (isAlphabet(buffer[0])==0)){
        pbTree newNode;
        newNode = malloc(sizeof(struct bTree));
        char *number;

        number = malloc(MAX*sizeof(char));
        
        strcpy(number, buffer);
        
        newNode->data = number;
        newNode->left= newNode->right = NULL;
        return newNode;
    }
    else{ // bufer[0] is an operation (i.e. +, -, * or /)
        char *operation;
        operation = malloc(MAX*sizeof(char));
        strcpy(operation, buffer);
        free(tree->data);
        tree->data = operation;
        return plantTree(tree);
    }
}

char *trimTree(pbTree tree){
    char *c;
    
    if(tree->left==NULL && tree->right==NULL){

        c = malloc((strlen(tree->data)+1)*sizeof(char));
        strcpy(c, tree->data);
        return c;
    }

    if(tree->data[0]=='+' || tree->data[0]=='-' || tree->data[0]=='*'){
        char *a, *b;
        
        a = trimTree(tree->left);
        b = trimTree(tree->right);


        if((a[0]=='(' || isAlphabet(a[0])==0) || (b[0]=='(' || isAlphabet(b[0])==0)){
            // printf("size: %d\n", (2*(strlen(a)+strlen(b)+5)));
            c = malloc((2*(strlen(a)+strlen(b)+5))*sizeof(char));
            strcpy(c, "( ");
            strcat(c, a);
            
            if(tree->data[0]=='+'){
                strcat(c, " + ");
            }
            else if(tree->data[0]=='-'){
                strcat(c, " - ");
            }
            else if(tree->data[0]=='*'){
                strcat(c, " * ");
            }

            strcat(c, b);
            strcat(c, " )");
            
        }
        else{
            int a_int, b_int;
            c = malloc((strlen(a)+strlen(b)+1)*sizeof(char));

            a_int = atoi(a);
            b_int = atoi(b);
            int x;

            if(tree->data[0]=='+'){
                x = (a_int+b_int);
                if(x<0){
                    x = (256+x)%256;
                }
                else{
                    x = x%256;
                }
                // printf("executing %s %s %s = %d\n", a, tree->data, b, x);
            }
            else if(tree->data[0]=='-'){
                x = (a_int-b_int);
                if(x<0){
                    x = (256+x)%256;
                }
                else{
                    x = x%256;
                }
                // printf("executing %s %s %s = %d\n", a, tree->data, b, x);
            }
            else if(tree->data[0]=='*'){
                x = (a_int*b_int);
                if(x<0){
                    x = (256+x)%256;
                }
                else{
                    x = x%256;
                }
                // printf("executing %s %s %s = %d\n", a, tree->data, b, x);
            }
            
            sprintf(c, "%d", abs(x));
        }
        
        free(a);
        free(b);
        // printf("c: %s\n", c);
    }

    return c;
}
// TREE ALGORITHMS - END

int main(){
    char *optimized;
    
    pHead tree = createTree();
    
    tree->root = plantTree(tree->root);

    optimized = trimTree(tree->root);

    printf("%s\n", optimized);
    
    free(optimized);

    burnTree(tree->root);

    return 0;
}