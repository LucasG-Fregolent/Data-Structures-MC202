#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define hashSize 555557

int hashFunction(char *word){
    int key = 0;
    for(int i=0; i<strlen(word); i++){
        key += (256*key + word[i])%hashSize;
    }
    return key%hashSize;
}

int main(){
    printf("%d\n", hashFunction("certo"));
    return 0;
}
