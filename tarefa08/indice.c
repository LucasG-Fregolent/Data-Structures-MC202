/*
Este arquivo conterá a implementação do índice.
Na versão atual, a estrutura de dados corresponde
somente a uma lista de períodos e não há nenhuma
estrutura pensada para realizar buscas rapidamente.

Você DEVE completar este arquivo, modificando-o livremente.
*/

#include "indice.h"
#include "utils.h"

#include <assert.h>
#include <stdlib.h>

/*
Defina todas as estruturas de dados
auxiliares que desejar. Em particular,
é obrigatório definir e utilizar uma
tabela de espalhamento.
*/

/*
Idéia: Criar uma tabela de espalhamento de palavras com indices de período do arquivo com encadeamento separado; 
assume-se que a probabilidade de a tabela degenerar-se é muito pequena (pode-se ainda implementar uma 
segunda funçao de hashing caso a lista ligada associada a uma dada chave venha a ser maior que um tamanho limite);

Função de hash: método de divisão trivial com peso de posição da string

Conflito: resolvido com lista ligada, i.e, elementos dos quais possuem uma mesma chave são colocados em uma lista ligada associada ao hash

Buscas: todos período de uma dado arquivo são salvos em um vetor (contrariamente à lista ligada implementada)
*/

/*----------------------------------------------INÍCIO-DO-CÓDIGO------------------------------------------------*/

// Necessary imports
#include <math.h>
#include <stdio.h>
#include <string.h>

// Constat definitions
#define hashSize 555557 // because its a cool number

// Linked list to store the words alongside with the index of the period it was read;
typedef struct node *pNode;

struct node{
    char *word;
    int index;
    pNode next;
};

// Linked List functions
pNode createList(char *word, int index){
    /*
    Receives a word and the period index, creates a linked list and then returns it

    --Parametrots:
    -word (char *): a word (string) read from the period;
    -index (int): the index of the so said period;

    --Returns:
    -node (pNode): the first element of the linked list associated with the key hashFunction(word) (see below
    for more information on hashFunction(char *word));
    */

    pNode newNode;
    char *newWord;

    newNode = malloc(sizeof(struct node));
    newWord = malloc((strlen(word)+1)*sizeof(char));

    strcpy(newWord, word);
    
    newNode->word = newWord;
    newNode->index = index;
    newNode->next = NULL;
    
    return newNode;
}

void destructList(pNode node){
    /*
    Recursive function to destruct the linked list;

    --Parameters:
    -node (pNode): the first node from the referred linked list;
    */
    if(node==NULL){
        free(node);
        return;
    }

    destructList(node->next);
    free(node->word);
    free(node);
}

void insertList(pNode node, char *word, int index){
    /*
    Recursive function to insert an element in the last position of the linked list;
    */

    if(node->index==index){ // Talvez dê erro kkk
        return;
    }

    if(node->next==NULL){
        pNode newNode;
        char *newWord;
        newNode = malloc(sizeof(struct node));
        newWord = malloc((strlen(word)+1)*sizeof(char));
        
        strcpy(newWord, word);

        newNode->word = newWord;
        newNode->index = index;
        newNode->next = NULL;
        node->next = newNode;

        return;
    }

    // Note that the function traverses all the nodes until it finds the last one to insert the newNode
    insertList(node->next, word, index);
}

// Hash table to store the words in a vector of type pNode;
typedef struct hash *pHash;

struct hash{
    pNode *vector; // List of linked lists
};

int hashFunction(char *word){
    /*
    A função de hash escolhida fora baseada no método de divisão; isso se deve ao fato de ser esta
    de implementação particularmente simples, rápida, fácil e, como nota-se pelo desempenho do 
    código, ela é capaz de espalhar as palavras com eficiencia suficientemente considerável (durante os testes realizados,
    notou-se um máximo de 5 colisões de palavras distintas somente!). Ainda assim, foi anteriormente implementada uma função 
    hash específica retirada do artigo http://www.cse.yorku.ca/~oz/hash.html, denominado djb2; este fez-se notavelmente 
    desnecessário, dado a impressionante quase inexistência de colisões no algorítmo mais simples implementado.
    */
    int key = 0;
    for(int i=0; i<strlen(word); i++){
        key += (256*key + word[i])%hashSize;
    }
    return key%hashSize;
}

pHash createHash(){
    /*
    Creates the hash table;
    */
    pHash table;
    table = malloc(sizeof(struct hash));
    pNode *vector;
    vector = malloc(hashSize*sizeof(struct node));
    
    for(int i=0; i<hashSize; i++){
        vector[i] = NULL;
    }

    table->vector = vector;
    return table;
}

void destructHash(pHash table){
    /*
    Destructs the hash, starting from the linked list associated with each index of the hash table;
    */
    for(int i=0; i<hashSize; i++){
        destructList(table->vector[i]);
    }

    free(table->vector);
    free(table);
}

void insertHash(pHash table, char *word, int index){
    /*
    Insert a new value into the hash table vector;
    Notice how simple the whole thing bacame with all the abstractions performed ;) beautiful!
    */
    
    int wordIndex = hashFunction(word);

    if(table->vector[wordIndex]==NULL){
        table->vector[wordIndex] = createList(word, index);
    }

    else{
        insertList(table->vector[wordIndex], word, index);
    }
}

struct indice {
    pHash table;
    p_no_str lista_periodos;
    char **periods;
    int numero_periodos;
};

p_indice criar_indice(char *nome_arquivo) {
    p_indice indice = malloc(sizeof(struct indice));
    assert(indice);
    int numero_periodos;
    indice->lista_periodos = ler_lista_periodos(nome_arquivo, &numero_periodos);
    indice->table = createHash();
    indice->numero_periodos = numero_periodos;
    char **vector;
    vector = malloc((indice->numero_periodos)*sizeof(char *));

    int periodo_index = 0;
    for(p_no_str no_periodo=indice->lista_periodos; no_periodo!=NULL; no_periodo=no_periodo->prox){
        vector[periodo_index] = malloc((MAX_BUFFER)*sizeof(char));
        strcpy(vector[periodo_index], no_periodo->str);
        char *periodo = no_periodo->str;

        p_no_str palavras_periodo = extrair_palavras(periodo);

        for(p_no_str p_word_periodo=palavras_periodo; p_word_periodo!=NULL; p_word_periodo=p_word_periodo->prox){
            insertHash(indice->table, p_word_periodo->str, periodo_index);
        }

        periodo_index++;
        
        liberar_lista_str(palavras_periodo);
    }

    indice->periods = vector;
    return indice;
}

void liberar_indice(p_indice indice) {
    liberar_lista_str(indice->lista_periodos);
    destructHash(indice->table);
    for(int i=0; i<indice->numero_periodos; i++){
        free(indice->periods[i]);
    }
    free(indice->periods);
    free(indice);
}

int consultar_indice(
    p_indice indice,
    char *consulta,
    void(callback)(char *periodo, int numero_ocorrencia)) //
{
    int numero_ocorrencia = 0;

    p_no_str palavras_consulta = extrair_palavras(consulta);

    // Search function goes here!
    char *word = palavras_consulta->str;

    int wordIndex = hashFunction(word);
    

    pNode node = indice->table->vector[wordIndex];

    while(node!=NULL){
        if(strcmp(node->word, word)==0){

            p_no_str lista = extrair_palavras(indice->periods[node->index]);

            if(corresponde(palavras_consulta, lista)){
                numero_ocorrencia++;
            
                callback(indice->periods[node->index], numero_ocorrencia);
            }

            liberar_lista_str(lista);
        }
        node = node->next;
    }

    liberar_lista_str(palavras_consulta);
    return numero_ocorrencia;
}
