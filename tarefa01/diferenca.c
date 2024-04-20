#include <stdio.h>
#define MAX 50

void bubble_sort(int diferenca[MAX], int k){
    for(int i=1; i<k; i++){
        int j = i;
        while(((j-1)>=0) && (diferenca[j-1]>diferenca[j])){
            int aux = diferenca[j];
            diferenca[j] = diferenca[j-1];
            diferenca[j-1]=aux;
            j--;
        }
    }
}

void diferenca(int lista1[MAX], int lista2[MAX], int N1, int N2){
    int diferenca[MAX], repetidos[MAX];
    int k=0, r=0;

    //Lista1-lista2
    for(int i=0; i<N1; i++){
        int x = lista1[i];
        int logic = 0;
        for(int j=0; j<N2; j++){
            int y = lista2[j];
            if(x==y){
                logic = 1;
                repetidos[r] = x;
                r++;
                break;
            }
        }
        if(logic==0){
            diferenca[k]=x;
            k++;
        }
    }

    //Lista2-repetidos
    for(int i=0; i<N2; i++){
        int x = lista2[i];
        int logic = 0;
        for(int j=0; j<r; j++){
            int y = repetidos[j];
            if(x==y){
                logic = 1;
                break;
            }
        }
        if(logic==0){
            diferenca[k]=x;
            k++;
        }
    }

    //Bubble sort
    bubble_sort(diferenca, k);

    //Print dos valores da diferença simétrica
    for(int i=0; i<k; i++){
        printf("%d ", diferenca[i]);
    }
}

int main(){
    int N1, N2;
    int lista1[MAX], lista2[MAX];
    scanf("%d %d", &N1, &N2);
    for(int i=0; i<(N1); i++){
        scanf("%d", &lista1[i]);
    }
    for(int i=0; i<(N2); i++){        
        scanf("%d", &lista2[i]);
    }
    diferenca(lista1, lista2, N1, N2);
    return 0;
}
