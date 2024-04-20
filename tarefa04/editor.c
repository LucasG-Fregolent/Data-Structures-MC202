#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define COMAND_SIZE 10
#define MAX 150

typedef struct node *pNode;
typedef struct heads *pHeads;

struct node{
    char *text;
    int bold;
    pNode next;
    pNode previous;
};

struct heads{
    pNode first, last;
};

pHeads createList(){ 
    pHeads head;
    head = malloc(sizeof(struct heads));
    head->first = NULL;
    head->last = NULL;
    return head;
} // ok

void printList(pNode node, int bold){
    if(node == NULL){
        return;
    }
    if(bold != node->bold){
        if(bold != -1){
            printf("\n");
        }
        if(node->bold == 0){
            printf("NORMAL '%s'", node->text);
        }
        else{
            printf("NEGRITO '%s'", node->text);
        }
    }
    printList(node->next, node->bold);
} // ok

pNode findNode(pHeads head, int n, int *j, int mode){
    int i = 0;
    pNode actual = head->first;
    char *actualText = actual->text;
    while(i<n){
        if(actualText[(*j)] == '\0'){
            actual = actual->next;
            actualText = actual->text;
            (*j) = 0;
            continue;
        }
        i++;
        (*j)++;
    }
    
    if((*j)==strlen(actualText) && mode!=0){
        actual = actual->next;
        (*j) = 0;
    }
    else if((*j)==strlen(actualText) && mode==0 && actual->next!=NULL){
        actual = actual->next;
        (*j) = 0;
    }

    return actual;
} // ok

void destructList(pHeads head, pNode node){
    if(node== NULL){
        free(head);
        return;
    }
    destructList(head, node->next);
    free(node->text);
    free(node);
} // ok

void divideText(char *text, int n, char *textB, char *textF){
    int i = 0;
    while(i<n){
        textB[i] = text[i];
        i++;
    }
    textB[i] = '\0';

    int j=0;
    while(i<strlen(text)){
        textF[j] = text[i];
        i++;
        j++;
    }
    textF[j] = '\0';
} // ok

void concatNodes(pHeads head, pNode node){
    if(node->next == NULL){
        return;
    }

    if(node->next->bold == node->bold){
        pNode aux = node->next;
        char *newText;
        newText = malloc((strlen(node->text)+strlen(node->next->text)+1)*sizeof(char)); // 1 unidade de segurança!

        strcpy(newText, node->text);

        strcat(newText, node->next->text);
        
        free(node->text);
        node->text = newText;

        node->next = node->next->next;

        if(node->next != NULL){
            node->next->previous = node;
        }
        else{
            head->last = node;
        }

        free(aux->text);
        free(aux);
    }

    return concatNodes(head, node->next);
}

void insertNode(pHeads head, char *newText, int n){
    pNode newNode;
    char *text;
    newNode = malloc(sizeof(struct node));
    if(head->first == NULL){ // o elemento a ser adicionado será o primeiro
        text = malloc((strlen(newText)+1)*sizeof(char)); // 1 unidade de segurança!
        strcpy(text, newText);
        newNode->text = text;
        newNode->bold = 0;
        newNode->next = NULL;
        newNode->previous = NULL;
        head->first = newNode;
        head->last = newNode;
        return;
    } // ok!

    int j = 0;
    char *textB, *textF;
    pNode actual = findNode(head, n, &j, 0); // ok!
    
    char *actualText = actual->text;

    text = malloc((strlen(actualText)+strlen(newText)+1)*sizeof(char)); // 1 unidade de segurança!
    textB = malloc((j+1)*sizeof(char)); // 1 unidade de segurança!
    textF = malloc((strlen(actualText)-j+1)*sizeof(char)); // 1 unidade de segurança!

    divideText(actualText, j, textB, textF); // ok

    strcpy(text, textB);

    strcat(text, newText);

    strcat(text, textF);

    free(textF);
    free(textB);

    newNode->text = text;
    newNode->bold = actual->bold;

    newNode->previous = actual->previous;
    if(newNode->previous != NULL){
        actual->previous->next = newNode;
    }
    else{
        head->first = newNode;
    }

    newNode->next = actual->next;
    if(newNode->next != NULL){
        actual->next->previous = newNode;
    }
    else{
        head->last = newNode;
    }

    free(actual->text);
    free(actual);
} // ok!

void selectSeq(pHeads head, int n, int m){
    int j = 0;
    char *text1, *text2, *text3, *aux;
    pNode node1, node2, node3;
    
    node1 = malloc(sizeof(struct node));
    node2 = malloc(sizeof(struct node));
    node3 = malloc(sizeof(struct node));

    node1->bold = 0;
    node2->bold = 1;
    node3->bold = 0;

    pNode actual = findNode(head, n, &j, 1);

    if(actual->bold == 1){
        n += strlen(actual->text)-j;
        j = 0;
        actual = actual->next;
    }
    
    // printf("texto do actual: %s\n", actual->text);

    aux = malloc((strlen(actual->text)+1)*sizeof(char)); // 1 unidade de segurança!
    text1 = malloc((j+1)*sizeof(char)); // 1 unidade de segurança!
    text1[0] = '\0';
    text2 = malloc((m-n+1)*sizeof(char)); // 1 unidade de segurança!
    text2[0] = '\0';
    text3 = malloc((strlen(actual->text)-j-(m-n)+1)*sizeof(char)); // 1 unidade de segurança!
    text3[0] = '\0';

    divideText(actual->text, j, text1, aux);

    divideText(aux, (m-n), text2, text3);

    // printf("text1: %s\n", text1);
    // printf("text2: %s\n", text2);

    free(aux);

    node2->text = text2;

    if(strcmp(text1, "")==0){
        free(text1);
        free(node1);
        node2->previous = actual->previous;
        
        if(actual->previous != NULL){
            actual->previous->next = node2;
        }
        else{
            head->first = node2;
        }
    }
    else{
        node1->text = text1;
        node1->next = node2;
        node2->previous = node1;
        node1->previous = actual->previous;

        if(actual->previous != NULL){
            actual->previous->next = node1;
        }
        else{
            head->first = node1;
        }
    }

    if(strcmp(text3, "")==0){
        free(text3);
        free(node3);

        node2->next = actual->next;
        if(actual->next != NULL){
            actual->next->previous = node2;
        }
        else{
            head->last = node2;
        }
    }
    else{
        node3->text = text3;
        node3->previous = node2;
        node2->next = node3;
        node3->next = actual->next;

        if(actual->next != NULL){
            actual->next->previous = node3;
        }
        else{
            head->last = node3;
        }
    }

    free(actual->text);
    free(actual);

    concatNodes(head, head->first);
    // printList(head->first, -1);
    // printf("\n");
} // ok

int main(){
    int x = 0;
    pHeads head = createList();
    while(x==0){
        char comando[COMAND_SIZE];
        scanf("%s", comando);
        if(strcmp(comando, "INSERIR")==0){
            int n;
            char text[MAX];
            scanf("%d", &n);
            scanf(" '%[^']'", text);
            insertNode(head, text, n);
        }
        else if(strcmp(comando, "DESTACAR")==0){
            int n, m;
            scanf("%d%d", &n, &m);
            selectSeq(head, n, m);
        }
        else if(strcmp(comando, "MOSTRAR")==0){
            x = 1;
            printList(head->first, -1);
            destructList(head, head->first);
            continue;
        }
    }
    return 0;
}
