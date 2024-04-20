#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct city *pCity;

struct city{
    char *name;
    int population;
    pCity next;
};

pCity citiesInput(int nCities){
    pCity cities = malloc(nCities*sizeof(struct city));

    for(int i=0; i<nCities; i++){
        char x[100];
        char *name;
        int population;
        
        scanf("%s", x);
        scanf("%d", &population);

        name = malloc((strlen(x)+1)*sizeof(char));

        strcpy(name, x);

        cities[i].name = name;
        cities[i].population = population;
        cities[i].next = NULL;
        printf("%s %d\n", cities[i].name, cities[i].population);
    }

    return cities;
}

void insertCity(pCity cities, char *name1, char *name2, int population){
    int i=0;
    while(strcmp(cities[i].name, name1)!=0){
        i++;
    }

    pCity node = cities[i].next;

    if(node==NULL){
    }

    while(node->next!=NULL){
        node = node->next;
    }

}

int main(){
    int nCities = 0;

    scanf("%d", &nCities);

    printf("ok %d\n", nCities);

    pCity cities;
    
    cities = citiesInput(nCities);
    
    return 0;
}
