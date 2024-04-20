#include <stdio.h>
#include <stdlib.h>

typedef struct node *pNode;
typedef struct heads *pHeads;

struct heads{
    pNode first;
    pNode last;
};

struct node{
    int value;
    pNode next;
    pNode previous;
};

typedef struct {
    int label;
    int data;
} map;

pHeads createStack(){
    pHeads head;
    head = malloc(sizeof(struct heads));
    head->first = NULL;
    head->last = NULL;
    return head;
}

void destructStack(pHeads head, pNode node){
    if(node == NULL){
        free(head);
        return;
    }
    destructStack(head, node->next);
    free(node);
}

void insertNode(pHeads head, int k){
    pNode newNode;
    newNode = malloc(sizeof(struct node));
    newNode->value = k;
    newNode->next = NULL;

    if(head->first == NULL){
        head->first = newNode;
        newNode->previous = NULL;
    }
    else{
        head->last->next = newNode;
        newNode->previous = head->last;
    }

    head->last = newNode;
}

void removeNode(pHeads head){ // Removes the last node from a stack
    pNode node = head->last;
    if(node->previous != NULL){
        node->previous->next = NULL;
    }
    else{
        head->first = NULL;
    }
    head->last = node->previous;
    free(node);
}

void printStack(pNode node){
    if(node == NULL){
        printf("\n");
        return;
    }
    if(node->next==NULL){
        printf("%d", node->value);
    }
    else{
        printf("%d -->", node->value);
    }
    printStack(node->next);
}

void printMap(map *levels, int n){
    for(int i=0; i<n; i++){
        if(levels[i].label==-1){
            continue;
        }
        printf("%d contem %d bonecas\n", levels[i].label, levels[i].data);
    }
}

void insertionSort(map *levels, int n){
    for(int i = 1; i<n; i++){
        int j = i;
        while((j-1)>=0 && levels[j].label<=levels[j-1].label){
            map aux = levels[j];
            levels[j] = levels[j-1];
            levels[j-1] = aux;
            j = j-1;
        }
    }
}

void iniciateMap(map *levels, int n){
    for(int i=0; i<n; i++){
        levels[i].label = -1;
    }
}

int searchMap(map *levels, int n, int label){
    for(int i=0; i<n; i++){
        if(levels[i].label == label){
            return i;
        }
    }
    return -1;
}

int verifyCorrectness(pHeads head){
    /*
    O(n) algorithm that verifies if a given sequence is correct or not.
    */

    pHeads stack = createStack();
    pNode actual = head->first;
    int counter = 0;
    int sizeSum = 0;
    int limit;

    if(actual->value<0){ // If first value is negative, then the sequence is wrong!
        destructStack(stack, stack->first);
        return -1;
    }

    while(actual != NULL){
        if(stack->last!=NULL && stack->last->value == -actual->value){
            removeNode(stack);
            counter--;
        }
        else{
            insertNode(stack, actual->value);
            if(actual->value>0){
                
                if(counter==0){
                    limit = actual->value;
                    sizeSum = 0;
                }
                else if(counter==1){
                    sizeSum+=actual->value;
                }

                counter++;
            }
            else{
                counter--;
            }
        }

        if(counter<0 || sizeSum>limit){
            destructStack(stack, stack->first);
            return -1;
        }

        actual = actual->next;
    }

    if(stack->first != NULL){
        destructStack(stack, stack->first);
        return -1;
    }

    destructStack(stack, stack->first);
    return 0;
}

int sublevels(pHeads head, pNode node){
    /*
    O(n) iterative method that searches for immidiate sublevels of a given starting (positive) node!
    *** Executed only when verifyCorrectness(head) return 0!
    */
    pHeads stack = createStack();
    int level = 0;
    int n = 0;

    insertNode(stack, node->value);
    node = node->next;
    
    while(stack->first!=NULL){
        if(stack->last==NULL || stack->last->value!=-node->value){
            level++;
            insertNode(stack, node->value);
        }
        else if(stack->last->value == -node->value){
            removeNode(stack);
            level--;
            if(level == 0){
                n++;
            }
        }
        node = node->next;
    }

    destructStack(stack, stack->first);
    return n;
}


int main(){
    int n;
    int k;
    int i = 0;
    pHeads head;
    map *levels;
    
    head = createStack();

    scanf("%d", &n);
    levels = malloc(n*sizeof(map));
    iniciateMap(levels, n);

    while(scanf("%d", &k) != EOF){
        insertNode(head, k);
    }


    if(verifyCorrectness(head) == 0){
        pNode actual = head->first;
        while(actual!=NULL){
            if(actual->value>0){
                int k = searchMap(levels, n, actual->value); // Verify is actual->value is already in the map
                if(k!=-1){ // if so:
                    int x = sublevels(head, actual); 
                    if(x>levels[k].data){ // Verify which one has the bigger number of direct sublevels
                        levels[k].data = x;
                    }
                }
                else{
                    levels[i].label = actual->value;
                    levels[i].data = sublevels(head, actual);
                    i++;
                }
            }
            actual = actual->next;
        }
        insertionSort(levels, i);
        printMap(levels, i);
    }
    else{
        printf("sequencia invalida");
        return 0;
    }

    free(levels);
    destructStack(head, head->first);
    return 0;
}
