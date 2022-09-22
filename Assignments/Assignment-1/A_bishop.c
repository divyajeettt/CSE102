# include <stdio.h>

///////////////////////////////////////////////////////////////////////////////

int chessboard[8][8], visitedBishop[8][8];

int isValid(int x, int y) {
    return ((0 <= x && x < 8) && (0 <= y && y < 8));
}

///////////////////////////////////////////////////////////////////////////////


void bishopMoves(int bx, int by, int *countBishop, int moves, int recursing, int dir) {
    // printf("(%d, %d), moves=%d, isValid(bx, by)=%d, visitedBishop[bx][by]=%d \n", bx, by, moves, isValid(bx, by), visitedBishop[bx][by]); 
    
    if (moves == 0 || !isValid(bx, by) || visitedBishop[bx][by]) {
        return;
    }

    (*countBishop)++;
    visitedBishop[bx][by]++;

    int copyX = bx, copyY = by;
    while (chessboard[copyX][copyY]) {
        bishopMoves(copyX, copyY, countBishop, ((dir==1) ? moves : moves-recursing), 1, 1);
        copyX++; copyY++;
    }

    copyX = bx, copyY = by;
    while (chessboard[copyX][copyY]) {
        bishopMoves(copyX, copyY, countBishop, ((dir==1) ? moves : moves-recursing), 1, 1);
        copyX--; copyY--;
    }

    copyX = bx, copyY = by;
    while (chessboard[copyX][copyY]) {
        bishopMoves(copyX, copyY, countBishop, ((dir==2) ? moves : moves-recursing), 1, 2);
        copyX++; copyY--;
    }
    
    copyX = bx, copyY = by;
    while (chessboard[copyX][copyY]) {
        bishopMoves(copyX, copyY, countBishop, ((dir==2) ? moves : moves-recursing), 1, 2);
        copyX--; copyY++;
    }
}


///////////////////////////////////////////////////////////////////////////////


int main() {
    int bx, by, M;
    int countBishop;
    char row[8];

    for (int i=0; i < 8; i++) {
        scanf("%s", row);
        for (int j=0; j < 8; j++) {
            chessboard[i][j] = ((row[j] == '.') ? 1 : 0);
            visitedBishop[i][j] = 0;
        }
    }

    scanf("%d %d", &bx, &by);
    scanf("%d", &M);

    bx--; by--;

    countBishop = 0;

    bishopMoves(bx, by, &countBishop, M, 0, 0);

    printf("%d", countBishop);

    return 0;
}