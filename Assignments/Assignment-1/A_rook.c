# include <stdio.h>

///////////////////////////////////////////////////////////////////////////////

int chessboard[8][8], visitedRook[8][8];

int isValid(int x, int y) {
    return ((0 <= x && x < 8) && (0 <= y && y < 8));
}

///////////////////////////////////////////////////////////////////////////////


void rookMoves(int rx, int ry, int *countRook, int moves, int recursing, int dir) {
    // printf("(%d, %d), moves=%d, isValid(rx, ry)=%d, visitedRook[rx][ry]=%d \n", rx, ry, moves, isValid(rx, ry), visitedRook[rx][ry]); 
    
    if (moves == 0 || !isValid(rx, ry) || visitedRook[rx][ry]) {
        return;
    }

    (*countRook)++;
    visitedRook[rx][ry]++;

    int copyX = rx;
    while (chessboard[copyX][ry]) {
        rookMoves(copyX, ry, countRook, ((dir==1) ? moves : moves-recursing), 1, 1);
        copyX++;
    }

    copyX = rx;
    while (chessboard[copyX][ry]) {
        rookMoves(copyX, ry, countRook, ((dir==1) ? moves : moves-recursing), 1, 1);
        copyX--;
    }

    int copyY = ry;
    while (chessboard[rx][copyY]) {
        rookMoves(rx, copyY, countRook, ((dir==2) ? moves : moves-recursing), 1, 2);
        copyY++;
    }
    
    copyY = ry;
    while (chessboard[rx][copyY]) {
        rookMoves(rx, copyY, countRook, ((dir==2) ? moves : moves-recursing), 1, 2);
        copyY--;
    }
}


///////////////////////////////////////////////////////////////////////////////


int main() {
    int rx, ry, M;
    int countRook;
    char row[8];

    for (int i=0; i < 8; i++) {
        scanf("%s", row);
        for (int j=0; j < 8; j++) {
            chessboard[i][j] = ((row[j] == '.') ? 1 : 0);
            visitedRook[i][j] = 0;
        }
    }

    scanf("%d %d", &rx, &ry);
    scanf("%d", &M);

    rx--; ry--;

    countRook = 0;

    rookMoves(rx, ry, &countRook, M, 0, 0);

    printf("%d", countRook);

    return 0;
}