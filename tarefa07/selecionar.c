#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX 20

/*
TENTATIVA 1 - com 1 heap: falha total e completa; é necessario saber quais sao os elementos medianos da lista (podendo ser no 
maximo 2), segue que implementar somente 1 heap nao oferece informações suficientes para conclusão do problema;

----------------------------------------------------------------------------------------------------------------------------------------

TENTATIVA 2 - com dois heaps (de uma ABB), um max e outro min, ambos para representar o mesmo conjunto de dados: pode oferecer uma resposta
correta uma vez que os elementos que permanecem na mesma posição em ambos os casos são os elementos médios, porém isso requeriria uma 
comparação dos elementos do vetor cuja comlexidade é O(n), não satisfazendo os imperativos do enunciado (e memória adicional 2*n);

----------------------------------------------------------------------------------------------------------------------------------------

TENTATIVA 3 - com dois heaps, um max e um min, porem os dados são colocados em somente 1 de acordo com a regra:
1. inicialmente, colocar o elemento recebido no heap que estiver vazio, ignorando quaisquer das regras abaixo explicitadas (começando
pelo maxHeap)
2. após, para cada novo elemento recebido como input, compara-lo com o elemento root (primeiro) do maxHeap, se menor, então
inserir-se-a o mesmo no maxHeap, do contrario, este sera inserido no minHeap;
3. se a diferença de tamanho entre o maxHeap e o minHeap for maior que 1, então remove-se a root do maior heap e em seguida insere-se este
no outro heap

Guiando-se por tal método, ter-se-a no fim doi possíveis casos:
caso 1: o tamanho do maxHeap e do minHeap é igual -> retorna o elemento root de ambos os heaps
caso 2: o tamanho do maxHeap e do minHeap é diferente -> retorna o elemento root do maior heap

complexidade: O(log(n))

----------------------------------------------------------------------------------------------------------------------------------------
*/

typedef struct {
    int weight;
    char *name;
} value;

typedef struct {
    value *values;
    int pos, size; // pos is the first free position in the tree
} pQueue;

pQueue *createHeap(int n){
    pQueue *heap;
    heap = malloc(sizeof(pQueue));
    heap->size = n;
    heap->pos = 0;
    heap->values = malloc((heap->size)*sizeof(value));
    return heap;
}

void destructHeap(pQueue *heap){
    for(int i=0; i<heap->pos; i++){
        free((heap->values[i]).name);
    }
    free(heap->values);
    free(heap);
}

void insertHeap(pQueue *heap, value newItem, char *typeHeap){
    heap->values[heap->pos] = newItem;
    int j = heap->pos;
    heap->pos = heap->pos+1;

    if(strcmp(typeHeap, "maxHeap")==0){
        while(j>0 && ((j%2!=0 && heap->values[(j-1)/2].weight<heap->values[j].weight) || (j%2==0 && heap->values[(j-2)/2].weight<heap->values[j].weight))){
            value aux;
            if(j%2!=0){
                aux = heap->values[(j-1)/2];
                heap->values[(j-1)/2] = heap->values[j];
                heap->values[j] = aux;
                j = (j-1)/2;
            }
            else if(j%2==0){
                aux = heap->values[(j-2)/2];
                heap->values[(j-2)/2]=heap->values[j];
                heap->values[j] = aux;
                j = (j-2)/2;
            }
        }
    }
    else if(strcmp(typeHeap, "minHeap")==0){
        while(j>0 && ((j%2!=0 && heap->values[(j-1)/2].weight>heap->values[j].weight) || (j%2==0 && heap->values[(j-2)/2].weight>heap->values[j].weight))){
            value aux;
            if(j%2!=0){
                aux = heap->values[(j-1)/2];
                heap->values[(j-1)/2] = heap->values[j];
                heap->values[j] = aux;
                j = (j-1)/2;
            }
            else if(j%2==0){
                aux = heap->values[(j-2)/2];
                heap->values[(j-2)/2]=heap->values[j];
                heap->values[j] = aux;
                j = (j-2)/2;
            }
        }
    }
}

value removeRootHeap(pQueue *heap, char *typeHeap){
    value aux = heap->values[0];
    heap->values[0] = heap->values[(heap->pos)-1];

    heap->pos = heap->pos-1;
    
    int j = 0;

    if(strcmp(typeHeap, "maxHeap")==0){
        while((2*j+1<heap->pos && heap->values[j].weight<heap->values[2*j+1].weight) || (2*j+2<heap->pos && heap->values[j].weight<heap->values[2*j+2].weight)){
            value least = heap->values[j];

            if(2*j+2<heap->pos){
            
                if(heap->values[2*j+1].weight>heap->values[2*j+2].weight){
                    heap->values[j] = heap->values[2*j+1];
                    heap->values[2*j+1] = least;
                    j = 2*j+1;
                }
                else{
                    heap->values[j] = heap->values[2*j+2];
                    heap->values[2*j+2] = least;
                    j = 2*j+2;
                }

            }
            else{
                heap->values[j] = heap->values[2*j+1];
                heap->values[2*j+1] = least;
                j = 2*j+1;
            }
        }
    }
    else if(strcmp(typeHeap, "minHeap")==0){
        while((2*j+1<heap->pos && heap->values[j].weight>heap->values[2*j+1].weight) || (2*j+2<heap->pos && heap->values[j].weight>heap->values[2*j+2].weight)){
            value biggest = heap->values[j];
            
            if(2*j+2<heap->pos){

                if(heap->values[2*j+1].weight<heap->values[2*j+2].weight){  
                    heap->values[j] = heap->values[2*j+1];
                    heap->values[2*j+1] = biggest;
                    j = 2*j+1;
                }
                else{
                    heap->values[j] = heap->values[2*j+2];
                    heap->values[2*j+2] = biggest;
                    j = 2*j+2;
                }
                
            }
            else{
                    heap->values[j] = heap->values[2*j+1];
                    heap->values[2*j+1] = biggest;
                    j = 2*j+1;
            }
        }
    }
    return aux;
}

int main(){
    int n;
    pQueue *maxHeap, *minHeap;
    scanf("%d", &n);
    
    maxHeap = createHeap(n);
    minHeap = createHeap(n);

    for(int i=0; i<n; i++){
        char *nameValue;
        char buffer[MAX+1];
        int weightValue;

        scanf("%s %d", buffer, &weightValue);

        nameValue = malloc((MAX+1)*sizeof(char));

        strcpy(nameValue, buffer);

        value newValue;
        newValue.name = nameValue;
        newValue.weight = weightValue;

        if(maxHeap->pos!=0 && newValue.weight>maxHeap->values[0].weight){
            /*
            Executes when maxHeap already at least one element and the new element to be inserted is
            bigger than the root
            */
            insertHeap(minHeap, newValue, "minHeap");
        }
        else{
            /*
            Else if maxHeap is empty or if the element to be inserted is lesser than the
            maxHeap root
            */
            insertHeap(maxHeap, newValue, "maxHeap");
        }

        if(maxHeap->pos>minHeap->pos && maxHeap->pos-minHeap->pos==2){
            /*
            Executes if the difference between the length of maxHeap and minHeap is equal 2
            */
            value x = removeRootHeap(maxHeap, "maxHeap");
            insertHeap(minHeap, x, "minHeap");
        }
        else if(maxHeap->pos<minHeap->pos && minHeap->pos-maxHeap->pos==2){
            value x = removeRootHeap(minHeap, "minHeap");
            insertHeap(maxHeap, x, "maxHeap");
        }

        if(minHeap->pos==0){
            printf("%s: %d\n", maxHeap->values[0].name, maxHeap->values->weight);
        }
        else if(maxHeap->pos==minHeap->pos){

            if(maxHeap->values[0].weight>minHeap->values[0].weight){
                printf("%s: %d\n", minHeap->values[0].name, minHeap->values->weight);
                printf("%s: %d\n", maxHeap->values[0].name, maxHeap->values->weight);
            }
            else{
                printf("%s: %d\n", maxHeap->values[0].name, maxHeap->values->weight);
                printf("%s: %d\n", minHeap->values[0].name, minHeap->values->weight);
            }
            
        }
        else{
            if(maxHeap->pos>minHeap->pos){
                printf("%s: %d\n", maxHeap->values[0].name, maxHeap->values->weight);
            }
            else{
                printf("%s: %d\n", minHeap->values[0].name, minHeap->values->weight);
            }
        }

    }

    destructHeap(maxHeap);
    destructHeap(minHeap);
    return 0;
}
