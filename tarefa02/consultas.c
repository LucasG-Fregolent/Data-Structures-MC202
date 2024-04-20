#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
#define max 100
#define CID 100

// Definição das structs de doença e medico
typedef struct {
    int crm;
    char nome[MAX];
} medico;

typedef struct {
    char cid[CID];
    char nome[MAX];
} doenca;

typedef struct {
    char nome[MAX];
    char cid[CID];
    int crm;
    int remover;
} registro;

void ordenar_nomes(registro *registros, int N){
    for(int i=1; i<N; i++){
        int j = i;
        while((j-1>=0) && (strcmp(registros[j].nome, registros[j-1].nome)<0)){
            char aux[MAX]="";
            strcpy(aux, registros[j].nome);
            strcpy(registros[j].nome, registros[j-1].nome);
            strcpy(registros[j-1].nome, aux);

            char auxCID[CID]="";
            strcpy(auxCID, registros[j].cid);
            strcpy(registros[j].cid, registros[j-1].cid);
            strcpy(registros[j-1].cid, auxCID);

            int auxCRM;
            auxCRM = registros[j].crm;
            registros[j].crm = registros[j-1].crm;
            registros[j-1].crm = auxCRM;

            int auxremv;
            auxremv = registros[j].remover;
            registros[j].remover = registros[j-1].remover;
            registros[j-1].remover = auxremv;
            j--;
        }
    }
}

int acharDoencas(doenca *doencas, int n, char cid[]){
    for(int i=0; i<n; i++){
        if(strcmp(doencas[i].cid, cid)==0){
            return i;
        }
    }
    return -1;
}

int acharMedico(medico *medicos, int n, int crm){
    for(int i=0; i<n; i++){
        if(medicos[i].crm == crm){
            return i;
        }
    }
    return -1;
}

int main(){
    FILE *open1 = fopen("dados/doencas.txt", "r");
    FILE *open2 = fopen("dados/medicos.txt", "r");
    medico *medicos;
    doenca *doencas;
    registro *registros;
    int vagas = 0;
    int k = 0;
    char abrir_fechar[50];


    // Abrir ambos os arquivo de medicos e doenças
    // Abrir medicos
    int n_medicos;
    if(open2==NULL){
        printf("não foi possível abrir o arquivo de medicos");
        return -1;
    }

    fscanf(open2, "%d", &n_medicos);
    medicos = malloc(n_medicos*sizeof(medico));

    for(int i=0; i<n_medicos; i++){
        fscanf(open2, "%d%s", &medicos[i].crm, medicos[i].nome);
    }

    // Abrir doencas
    int n_doencas;
    if(open1==NULL){
        printf("não foi possível abrir o arquivo de doencas");
        return -1;
    }

    fscanf(open1, "%d", &n_doencas);
    doencas = malloc(n_doencas*sizeof(doenca));
    
    for(int i=0; i<n_doencas; i++){
        fscanf(open1, "%s", doencas[i].cid);
        int k = 0;
        char atual='\0';
        while(atual!='\n'){
            fscanf(open1, "%c", &atual);
            if(atual != '\n'){
                doencas[i].nome[k] = atual;
                k++;
            }
        }
        doencas[i].nome[k] = '\0';
    }

    // Escaneamento do input
    scanf("%s %d", abrir_fechar, &vagas);
    registros = malloc((2*vagas)*sizeof(registro));

    while(1){
        char operacao[max];
        scanf("%s", operacao);
        if(strcmp(operacao, "registrar")==0){
            scanf("%s", registros[k].nome); 
            scanf("%s", registros[k].cid);
            scanf("%d", &registros[k].crm);
            registros[k].remover = 0;
            k++;
        }
        else if(strcmp(operacao, "remover")==0){
            char nome[MAX] = "";
            scanf("%s", nome);
            for(int i=0; i<k; i++){
                if(strcmp(registros[i].nome, nome)==0){
                    registros[i].remover = 1;
                    break;
                }
            }
        }
        else if(strcmp(operacao, "alterar")==0){
            char cid_novo[CID] = "";
            char nome_alterar[MAX] = "";
            scanf("%s", nome_alterar);
            scanf("%s", cid_novo);
            for(int i=0; i<k; i++){
                if(strcmp(registros[i].nome, nome_alterar)==0){
                    strcpy(registros[i].cid, cid_novo);
                }
            }
        }
        else if(strcmp(operacao, "fechar")==0){
            ordenar_nomes(registros, k);
            for(int i=0; i<k; i++){
                if(registros[i].remover==0){
                    int crm;
                    crm = registros[i].crm;
                    char cid[CID] = "";
                    strcpy(cid, registros[i].cid);
                    int i_medicos;
                    i_medicos = acharMedico(medicos, n_medicos, crm);
                    int i_doencas;
                    i_doencas = acharDoencas(doencas, n_doencas, cid);
                    char registro_nome[MAX] = "";
                    strcpy(registro_nome, registros[i].nome);
                    char medicos_nome[MAX] = "";
                    strcpy(medicos_nome, medicos[i_medicos].nome);
                    char doencas_nome[MAX] = "";
                    strcpy(doencas_nome, doencas[i_doencas].nome);
                    printf("%s atendido por %s: %s\n", registro_nome, medicos_nome, doencas_nome);
                }
            }
            break;
        }
    }

    free(registros);
    free(medicos);
    free(doencas);
    fclose(open1);
    fclose(open2);
    return 0;
}
