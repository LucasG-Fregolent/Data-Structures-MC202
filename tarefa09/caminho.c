#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define PRETA 0
#define BRANCA 0xFFFFFF

// Queue implementation
typedef struct queue *pQueue;
typedef struct heads *pHeads;

struct queue{
    int value;
    int level;
    pQueue previous;
};

struct heads{
    pQueue first, last;
};

pHeads createHeads(){
    pHeads head; 

    head = malloc(sizeof(struct heads));
    head->first = NULL;
    head->last = NULL;
    
    return head;
}

void destructQueue(pHeads head, pQueue q){ // q = head->first
    if(q==NULL){
        free(head);
        return;
    }

    if(q->previous == NULL){
        free(q);
        free(head);
        return;
    }

    destructQueue(head, q->previous);
    free(q);
}

void insertQueue(pHeads head, int value, int level){
    pQueue q;

    q = malloc(sizeof(struct queue));
    q->value = value;
    q->level = level;
    q->previous = NULL;

    if(head->first==NULL){
        head->first = q;
        head->last = q;
    }
    else{
        head->last->previous = q;
        head->last = q;
    }
}

int *dequeue(pHeads head){
    int *info;
    info = malloc(2*sizeof(int));
    info[0] = info[1] = 0;

    if(head->first==NULL){
        return info;
    }

    pQueue q = head->first;
    info[0] = q->value;
    info[1] = q->level;

    head->first = head->first->previous;

    free(q);

    return info;
}

int isEmpty(pHeads head){
    if(head->first==NULL){
        return 1; // True
    }
    return 0; // False
}

void printQueue(pQueue q){
    if(q==NULL){
        return;
    }

    printf("%d - %d\n", q->value, q->level);
    printQueue(q->previous);
}
// Queue implementation - END

typedef struct{
    int rgb;
    int visited;
} pixel;

struct imagem {
    int w, h;
    pixel **pix;
    int *initial;
    int *final; // Not used, but it is an interesting information to have!
    int n_regions;
};

// função presume que não ocorrem erros e que
// máximo valor de um canal de cor é 255
struct imagem *ler_imagem() {
    struct imagem *img;
    int *initial, *final;
    char peek;
    int i, j, r, g, b;
    assert(img = malloc(sizeof(*img)));
    initial = malloc(2*sizeof(int)); // Starting position
    final = malloc(2*sizeof(int)); // Final goal position

    initial[0] = initial[1] = -1;
    final[0] = final[1] = -1;
    img->initial = initial;
    img->final = final;
    img->n_regions=0;

    scanf("P3 ");
    while ((peek = getchar()) == '#')
        scanf("%*[^\r\n]%*[\r\n]");
    ungetc(peek, stdin);
    assert(scanf("%d %d %*d", &img->w, &img->h) == 2);
    assert(img->pix = malloc(sizeof(*img->pix) * img->h));
    for (i = 0; i < img->h; i++) {
        assert(img->pix[i] = malloc(sizeof(**img->pix) * img->w));
        for (j = 0; j < img->w; j++) {
            assert(scanf("%d%d%d", &r, &g, &b) == 3);
            img->pix[i][j].visited = 0;
            if(r==255 && g==255 && b==255){
                img->pix[i][j].rgb = 0;
                if(initial[0]==-1 && initial[1]==-1){
                    initial[0] = i;
                    initial[1] = j;
                }
                else if(final[0]==-1 && final[1]==-1){
                    final[0] = i;
                    final[1] = j;
                }
            }
            else{
                img->pix[i][j].rgb = (16*r) + (8*g) + b;
            }
        }
    }
    return img;
}
void salvar_imagem(struct imagem *img, char *file) {
    int i, j;
    FILE *fp = fopen(file, "w");
    fprintf(fp, "P3\n%d %d %d\n", img->w, img->h, 255);
    for (i = 0; i < img->h; i++) {
        for (j = 0; j < img->w; j++) {
            int r, g, b;
            int pix = img->pix[i][j].rgb;
            r = pix >> 16 & 0xFF;
            g = pix >> 8 & 0xFF;
            b = pix & 0xFF;
            fprintf(fp, "%d %d %d\n", r, g, b);
        }
    }
    fclose(fp);
}
void liberar_imagem(struct imagem *img) {
    int i;
    for (i = 0; i < img->h; i++)
        free(img->pix[i]);
    free(img->pix);
    free(img->initial);
    free(img->final);
    free(img);
}


void printIMG(struct imagem *img){
    /*
    Function that prints the image in the same dimensions it is supposed to have
    */
    for(int i=0; i<img->h; i++){
        for(int j=0; j<img->w; j++){
            printf("%d ", img->pix[i][j].rgb);
        }
        printf("\n");
    }
    printf("initial: %d %d\n", img->initial[0], img->initial[1]);
    printf("final: %d %d\n", img->final[0], img->final[1]);
}


/*
Sequence of functions to verify the validity of the adjacent positions (in each cardinal direction) of a certain square;

--Parameters:
-img (struct imagem *): The matrix containing the image;
-n or m (int): n is the line and m is the column of the analised square;

--Returns:
-0 if the position is valid;
-1, otherwise;
*/
int verifyValidityNORTH(struct imagem *img, int n){
    if((n-1)>=0){
        return 0;
    }
    return 1;
}

int verifyValiditySOUTH(struct imagem *img, int n){
    if(n+1<img->h){
        return 0;
    }
    return 1;
}

int verifyValidityEAST(struct imagem *img, int m){
    if(m+1<img->w){
        return 0;
    }
    return 1;
}

int verifyValidityWEST(struct imagem *img, int m){
    if(m-1>=0){
        return 0;
    }
    return 1;
}
// Function to verify the validity of the cardinal directions - END

void dfsTraverse(struct imagem *img, int n, int m, int i){
    img->pix[n][m].visited = 1;
    if(verifyValidityNORTH(img, n)==0 && img->pix[n-1][m].visited==0 && img->pix[n-1][m].rgb==img->pix[n][m].rgb){
        dfsTraverse(img, n-1, m, i);
    }
    if(verifyValiditySOUTH(img, n)==0 && img->pix[n+1][m].visited==0 && img->pix[n+1][m].rgb==img->pix[n][m].rgb){
        dfsTraverse(img, n+1, m, i);
    }
    if(verifyValidityEAST(img, m)==0 && img->pix[n][m+1].visited==0 && img->pix[n][m+1].rgb==img->pix[n][m].rgb){
        dfsTraverse(img, n, m+1, i);
    }
    if(verifyValidityWEST(img, m)==0 && img->pix[n][m-1].visited==0 && img->pix[n][m-1].rgb==img->pix[n][m].rgb){
        dfsTraverse(img, n, m-1, i);
    }

    img->pix[n][m].rgb = i;
    return;
}

// void paintWhite(struct imagem *img){
//     img->pix[img->initial[0]][img->initial[1]].rgb = -2;
//     img->pix[img->final[0]][img->final[1]].rgb = -1;
// }

int ** createAdjList(struct imagem *img){
    int **adjList = malloc(img->n_regions*sizeof(int *));
    for(int i=0; i<img->n_regions; i++) adjList[i]=malloc((img->n_regions+1)*sizeof(int));

    for(int i=0; i<img->n_regions; i++){
        adjList[i][0] = -5; // NULL number that indicated the end of the vector;
    }

    return adjList;
}

void destroyAdjList(struct imagem *img, int **adjList){
    for(int i=0; i<img->n_regions; i++){
        free(adjList[i]);
    }
    free(adjList);
}

void addNeighbor(int **adjList, int x, int neighbor, int i){
    if(adjList[x][i]==-5){
        adjList[x][i] = neighbor;
        adjList[x][i+1] = -5;
        return;
    }

    if(adjList[x][i]==neighbor){
        return;
    }

    i++;
    return addNeighbor(adjList, x, neighbor, i);
}

void parseMap(struct imagem *img, int **adjList){
    for(int i=0; i<img->h; i++){
        for(int j=0; j<img->w; j++){
            int x = img->pix[i][j].rgb;
            if(verifyValidityNORTH(img, i)==0){
                if(img->pix[i][j].rgb!=img->pix[i-1][j].rgb){
                    addNeighbor(adjList, x, img->pix[i-1][j].rgb, 0);
                }
            }
            if(verifyValiditySOUTH(img, i)==0){
                if(img->pix[i][j].rgb!=img->pix[i+1][j].rgb){
                    addNeighbor(adjList, x, img->pix[i+1][j].rgb, 0);
                }
            }
            if(verifyValidityEAST(img, j)==0){
                if(img->pix[i][j].rgb!=img->pix[i][j+1].rgb){
                    addNeighbor(adjList, x, img->pix[i][j+1].rgb, 0);
                }
            }
            if(verifyValidityWEST(img, j)==0){
                if(img->pix[i][j].rgb!=img->pix[i][j-1].rgb){
                    addNeighbor(adjList, x, img->pix[i][j-1].rgb, 0);
                }
            }
        }
    }
}

void printAdjList(struct imagem *img, int **adjList){
    for(int i=0; i<img->n_regions; i++){
        printf("%d: ", i);
        for(int j=0; adjList[i][j]!=-5; j++){
            printf("%d ", adjList[i][j]);
        }
        printf("\n");
    }
}

void paintIMG(struct imagem *img){
    int x = 2;
    int first = 0;
    for(int i=0; i<img->h; i++){
        for(int j=0; j<img->w; j++){
            if(img->pix[i][j].visited==0){
                if(img->pix[i][j].rgb!=0){
                    dfsTraverse(img, i, j, x);
                    x++;
                }
                else if(img->pix[i][j].rgb==0){
                    int k = 0;
                    if(first==1){
                        k = 1;
                    }
                    dfsTraverse(img, i, j, k);
                    first = 1;
                }
            }
        }
    }
    img->n_regions = x; // Because there are 2 white regions, different from each other
}

int bfs(struct imagem *img, int **adjList){
    pHeads head = createHeads();
    int *visited;
    visited = malloc(img->n_regions*sizeof(int));
    for(int i=0; i<img->n_regions; i++){
        visited[i] = -1; // Indicates a not visited position
    }
    
    int initial = 0;
    int final = 1;
    int level = 0;
    
    int actual = initial;
    while(actual != final){
        level++;
        visited[actual] = 0;
        for(int i=0; adjList[actual][i]!=-5; i++){
            int x = adjList[actual][i];
            if(visited[x]==-1){
                insertQueue(head, x, level);
                visited[x] = 0;
            }
        }
        int *list = dequeue(head);
        
        actual = list[0];
        level = list[1];

        free(list);

        if(actual == final){
            continue;

        }
    }

    destructQueue(head, head->first);
    free(visited);
    return level-1; 
    /*
    Notice it countes it surpass the correct answer in 1 unity; That is because it considers the initial
    position to be a region in itself;
    */
}

// exemplo de como usar as funções:
// lê uma imagem e cria um novo
// arquivo com metade da imagem pintada
int main(int argc, char *argv[]) {
    int **adjList;

    struct imagem *img = ler_imagem();
    salvar_imagem(img, "pintada.ppm");

    
    paintIMG(img);
    
    adjList = createAdjList(img);

    parseMap(img, adjList);

    printf("Maria deve memorizar %d regioes.\n", bfs(img, adjList));
    destroyAdjList(img, adjList);
    
    liberar_imagem(img);

    return 0;
}
