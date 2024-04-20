#include <stdio.h>
#include <stdlib.h>

/*
General idea: place queens recursively with backtraking
if the number of queens to be placed > max number of non-treatening queens in the board, them verify with a
certain amount of pawns
*/

// Creation of the chess board
typedef struct {
    int i;
    int j;
} pos;

char** createChess(int n){
    char **chess = malloc(n*sizeof(char *));
    for(int i=0; i<n; i++) chess[i] = malloc(n*sizeof(char));
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            chess[i][j] = '.';
        }
    }
    return chess;
}

void printChess(char **chess, int n, int p){
    printf("%d\n", p);
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            printf("%c ", chess[i][j]); 
        }
        printf("\n");
    }
}
// Creation of the chess board - END

// Recursive algorithms
int verifyPos(char **chess, int n, pos p){
    /*
    Boolean function that return true (0) if a given positions is not being attacked
    by another queen already placed in the board
    */

    for(int i=0; i<n; i++){
        char row = chess[p.i][i];
        if(row == 'r'){
            return 1;
        }
        char col = chess[i][p.j];
        if(col == 'r'){
            return 1;
        }
        if((p.i+i<n) && (p.j+i)<n){
            char mainDiagonalF = chess[p.i+i][p.j+i];
            if(mainDiagonalF == 'r'){
                return 1;
            }
        }
        if((p.i-i>=0) && (p.j-i>=0)){
            char mainDiagonalB = chess[p.i-i][p.j-i];
            if(mainDiagonalB == 'r'){
                return 1;
            }
        }
        if((p.i+i<n) && (p.j-i>=0)){
            char secDiagonalB = chess[p.i+i][p.j-i];
            if(secDiagonalB == 'r'){
                return 1;
            }
        }
        if((p.i-i>=0) && (p.j+i<n)){
            char secDiagonalF = chess[p.i-i][p.j+i];
            if(secDiagonalF == 'r'){
                return 1;
            }
        }
    }
    return 0;
}

void placeQueen(char **chess, pos p){
    chess[p.i][p.j] = 'r';
}

void unplaceQueen(char **chess, pos p){
    chess[p.i][p.j] = '.';
}

void placePawn(char **chess, pos p){
    chess[p.i][p.j] = 'p';
}

void unplacePawn(char **chess, pos p){
    /*
    Although both functions unplaceQueen and unplacePawn does exactly the same, it was
    prefered to keep the distinction so as make the code more self-explanatory
    */
    chess[p.i][p.j] = '.';
}


void initPositions(pos positions[], int m){
    /*
    Function that initiates all of the queens positions to (0, 0)
    */
    pos firstPos;
    firstPos.i = firstPos.j = 0;
    for(int i=0; i<m; i++){
        positions[i] = firstPos;
    }
}

int finalPos(pos position, int n){
    /*
    boolean functin that verifies if the last placed position is the last one
    0 is True, 1 if False
    */
    pos final;
    final.i = n-1;
    final.j = n-1;
    if(position.j==final.j && position.i==final.i){
        return 0;
    }
    return 1;
}

pos nextPos(int n, pos p){
    /*
    Given a positions p, returns the next position
    */
    int i = p.i;
    int j = p.j;
    if(finalPos(p, n)==0){
        pos newPos;
        newPos.i = newPos.j = -1;
        return newPos;
    }
    if(i<n-1){
        p.i = i+1;
    }
    else if((i==n-1) && (j<n-1)){
        p.i = 0;
        p.j = j+1;
    }
    return p;
}

void placeQueens(char **chess, int n, int m, pos *positions, int positionsIndex){
    if(positionsIndex == m){
        return;
    }

    pos newPos = positions[positionsIndex]; // Each new queen`s position begins from the last placed queen

    positionsIndex++;
    
    while(verifyPos(chess, n, newPos)!=0){
        // Executes while the actual position is invalid
        // printf("newPos: %d %d / %d\n", newPos.i, newPos.j, verifyPos(chess, n, newPos));
        if((finalPos(newPos, n)==0 && (positionsIndex<m-1 || verifyPos(chess, n, newPos)==1)) || (newPos.i==-1)){
            positionsIndex--;
            newPos = positions[positionsIndex];
            unplaceQueen(chess, positions[positionsIndex]);
        }
        newPos = nextPos(n, newPos);
    }

    positions[positionsIndex] = newPos;

    placeQueen(chess, newPos);

    printChess(chess, n, 0);

    return placeQueens(chess, n, m, positions, positionsIndex);
}
// Recursive algorithms - END

int main(){
    int m, n;
    int p = 0;
    pos *positions;
    int positionsIndex = 0;
    char **chess;

    scanf("%d%d", &m, &n);
    
    positions = malloc((m+1)*sizeof(pos)); // 1 unidade de segurança!

    initPositions(positions, m);
    chess = createChess(n);

    placeQueens(chess, n, m, positions, positionsIndex);

    printChess(chess, n, p);

    free(positions);

    for(int i=0; i<n; i++){
        free(chess[i]);
    }
    free(chess);

    return 0;
}
