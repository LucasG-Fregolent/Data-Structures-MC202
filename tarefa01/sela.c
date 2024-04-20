#include <stdio.h>
#define MAX 100

int coluna(int mapa[MAX][MAX], int resposta[3], int N, int M){
    int minion;
    int a, b;
    int boolean1 = 0, boolean2 = 0;
    for(int i=0; i<N; i++){
        minion = mapa[i][0];
        a = i;
        b = 0;
        boolean2 = 0;
        for(int j=1; j<M; j++){
            if(mapa[i][j]==minion){
                boolean1 = 1;
            }
            else if(mapa[i][j]<minion){
                boolean1 = 0;
                minion=mapa[i][j];
                a = i;
                b = j;
            }
        }
        if(boolean1==1){
            continue;
        }
        for(int l=0; l<N; l++){
            if((mapa[l][b]==minion && l!=a) || (mapa[l][b]>minion)){
                boolean2 = 1;
                continue;
            }
        }
        if(boolean2==1){
            continue;
        }
        resposta[0]=a;
        resposta[1]=b;
        resposta[2]=minion;
        break;
    }
    if(boolean2==1){
        return 1;
    }
    return 0;
}

int main(){
    int N, M;
    int mapa[MAX][MAX];
    int resposta[3];
    scanf("%d %d", &N, &M);
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            scanf("%d", &mapa[i][j]);
        }
    }
    if(coluna(mapa, resposta, N, M)==1){
        printf("nao existe ponto de sela");
        return 0;
    }
    printf("(%d, %d) eh ponto de sela com valor %d\n", resposta[0], resposta[1], resposta[2]);
    return 0;
}
