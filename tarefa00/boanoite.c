#include <stdio.h>
#define MAX 1000

int main(){
    int N;
    char nome[MAX];
    scanf("%d", &N);
    for (int i=0; i<N; i++){
        scanf("%s", nome);
        printf("Boa noite, %s.\n", nome);
    }
}
