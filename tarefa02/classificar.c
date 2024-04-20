#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 31

typedef struct {
    char nome[MAX];
    char sobrenome[MAX];
} paciente;

void ordenar_nomes(paciente *pacientes, int N){
    for(int i=1; i<N; i++){
        int j = i;
        while((j-1>=0) && (strcmp(pacientes[j].nome, pacientes[j-1].nome)<0)){
            char auxNomes[MAX];
            strcpy(auxNomes, pacientes[j].nome);
            strcpy(pacientes[j].nome, pacientes[j-1].nome);
            strcpy(pacientes[j-1].nome, auxNomes);

            char auxSobrenomes[MAX];
            strcpy(auxSobrenomes, pacientes[j].sobrenome);
            strcpy(pacientes[j].sobrenome, pacientes[j-1].sobrenome);
            strcpy(pacientes[j-1].sobrenome, auxSobrenomes);

            j--;
        }
    }
}

void ordenar_sobrenomes(paciente *pacientes, int N){
    for(int i=1; i<N; i++){
        int j = i;
        while((j-1>=0) && (strcmp(pacientes[j].sobrenome, pacientes[j-1].sobrenome)<0)){
            char auxSobrenomes[MAX];
            strcpy(auxSobrenomes, pacientes[j].sobrenome);
            strcpy(pacientes[j].sobrenome, pacientes[j-1].sobrenome);
            strcpy(pacientes[j-1].sobrenome, auxSobrenomes);

            char auxNomes[MAX];
            strcpy(auxNomes, pacientes[j].nome);
            strcpy(pacientes[j].nome, pacientes[j-1].nome);
            strcpy(pacientes[j-1].nome, auxNomes);

            j--;
        }
    }
}

int achar_homonimos(paciente *pacientes, paciente *homonimos, int N){
    int k=0, i=0;
    while(i<N){
        int j = i+1;
        if(strcmp(pacientes[i].nome, pacientes[j].nome)==0){
            strcpy(homonimos[k].nome, pacientes[i].nome);
            strcpy(homonimos[k].sobrenome, pacientes[i].sobrenome);
            k++;
            while((j<N) && (strcmp(pacientes[i].nome, pacientes[j].nome)==0)){
                strcpy(homonimos[k].nome, pacientes[j].nome);
                strcpy(homonimos[k].sobrenome, pacientes[j].sobrenome);
                k++;
                j++;
            }
        }
        i=j;
    }
    return k;
}

int achar_parentes(paciente *pacientes, paciente *parentes, int N){
    int k=0, i=0;
    while(i<N){
        int j = i+1;
        if(strcmp(pacientes[i].sobrenome, pacientes[j].sobrenome)==0){
            strcpy(parentes[k].nome, pacientes[i].nome);
            strcpy(parentes[k].sobrenome, pacientes[i].sobrenome);
            k++;
            while((j<N) && (strcmp(pacientes[i].sobrenome, pacientes[j].sobrenome)==0)){
                strcpy(parentes[k].nome, pacientes[j].nome);
                strcpy(parentes[k].sobrenome, pacientes[j].sobrenome);
                k++;
                j++;
            }
        }
        i=j;
    }
    return k;
}

int main(){
    int N, k=0;
    int indice_pacientes = 0;
    char opcionar[MAX];
    paciente *pacientes;
    paciente *homonimos;
    paciente *parentes;

    //Leitura - Número de termos e opção
    scanf("%d", &N);
    scanf("%s", opcionar);

    //Alocação dinâmica e leitura de pacientes
    pacientes = (paciente*)malloc(N*sizeof(paciente));
    homonimos = (paciente*)malloc(N*sizeof(paciente));
    parentes = (paciente*)malloc(N*sizeof(paciente));
    for(int i=0; i<N; i++){
        //Declaração de variáveis
        paciente p;
        char a[3*MAX];
        int barra = 0;
        int k=0;

        //Leitura e separação do nome_sobrenome
        scanf("%s", a);
        for(int j=0; a[j]!='\0'; j++){
            if(a[j]=='_'){
                k = 0;
                barra = 1;
                continue;
            }
            else if(barra==1){
                p.sobrenome[k] = a[j];
                p.sobrenome[k+1] = '\0';
                k++;
                continue;
            }
            p.nome[k] = a[j];
            p.nome[k+1] = '\0';
            k++;
        }
        pacientes[indice_pacientes] = p;
        indice_pacientes++;
    }

    if(strcmp(opcionar,"homonimos")==0){
        ordenar_sobrenomes(pacientes, N);
        ordenar_nomes(pacientes, N);
        k = achar_homonimos(pacientes, homonimos, N);
        for(int i=0; i<k; i++){
            printf("%s_%s\n", homonimos[i].nome, homonimos[i].sobrenome);
        }
    }
    else{
        ordenar_nomes(pacientes, N);
        ordenar_sobrenomes(pacientes, N);
        k = achar_parentes(pacientes, parentes, N);
        for(int i=0; i<k; i++){
            printf("%s_%s\n", parentes[i].nome, parentes[i].sobrenome);
        }
    }

    free(pacientes);
    free(homonimos);
    free(parentes);
    return 0;
}
