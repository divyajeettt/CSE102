# include <stdio.h>

///////////////////////////////////////////////////////////////////////////////

int chessboard[8][8], visitedRook[8][8], visitedBishop[8][8], visitedKnight[8][8];

///////////////////////////////////////////////////////////////////////////////

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

    int copyX = rx+1;
    while (chessboard[copyX][ry]) {
        rookMoves(copyX, ry, countRook, ((dir==1) ? moves : moves-recursing), 1, 1);
        copyX++;
    }

    copyX = rx-1;
    while (chessboard[copyX][ry]) {
        rookMoves(copyX, ry, countRook, ((dir==1) ? moves : moves-recursing), 1, 1);
        copyX--;
    }

    int copyY = ry+1;
    while (chessboard[rx][copyY]) {
        rookMoves(rx, copyY, countRook, ((dir==2) ? moves : moves-recursing), 1, 2);
        copyY++;
    }
    
    copyY = ry-1;
    while (chessboard[rx][copyY]) {
        rookMoves(rx, copyY, countRook, ((dir==2) ? moves : moves-recursing), 1, 2);
        copyY--;
    }
}


///////////////////////////////////////////////////////////////////////////////


void bishopMoves(int bx, int by, int *countBishop, int moves, int recursing, int dir) {
    // printf("(%d, %d), moves=%d, isValid(bx, by)=%d, visitedBishop[bx][by]=%d \n", bx, by, moves, isValid(bx, by), visitedBishop[bx][by]); 
    
    if (moves == 0 || !isValid(bx, by) || visitedBishop[bx][by]) {
        return;
    }

    (*countBishop)++;
    visitedBishop[bx][by]++;

    int copyX = bx+1, copyY = by+1;
    while (chessboard[copyX][copyY]) {
        bishopMoves(copyX, copyY, countBishop, ((dir==1) ? moves : moves-recursing), 1, 1);
        copyX++; copyY++;
    }

    copyX = bx-1, copyY = by-1;
    while (chessboard[copyX][copyY]) {
        bishopMoves(copyX, copyY, countBishop, ((dir==1) ? moves : moves-recursing), 1, 1);
        copyX--; copyY--;
    }

    copyX = bx+1, copyY = by-1;
    while (chessboard[copyX][copyY]) {
        bishopMoves(copyX, copyY, countBishop, ((dir==2) ? moves : moves-recursing), 1, 2);
        copyX++; copyY--;
    }
    
    copyX = bx-1, copyY = by+1;
    while (chessboard[copyX][copyY]) {
        bishopMoves(copyX, copyY, countBishop, ((dir==2) ? moves : moves-recursing), 1, 2);
        copyX--; copyY++;
    }
}


///////////////////////////////////////////////////////////////////////////////


void knightMoves(int kx, int ky, int *countKnight, int moves) {
    int diff[9][2] = {
        {0, 0}, {+2, +1}, {+2, -1}, {-2, +1}, {-2, -1}, 
        {+1, +2}, {-1, +2}, {+1, -2}, {-1, -2}
    };

    int currBoxes[8][2];
    int sizeCurr = 1;
    currBoxes[0][0] = kx; currBoxes[0][1] = ky;

    while (sizeCurr != 0 && moves--) {
        int nextBoxes[16][2];
        int indexNext = 0;

        for (int i=0; i < sizeCurr; i++) {
            for (int j=0; j < 9; j++) {
                int x = currBoxes[i][0] + diff[j][0];
                int y = currBoxes[i][1] + diff[j][1];
                
                if (isValid(x, y) && chessboard[x][y] && !visitedKnight[x][y]) {
                    nextBoxes[indexNext][0] = x;
                    nextBoxes[indexNext++][1] = y;
                    (*countKnight)++;
                }
                visitedKnight[x][y]++;
            }
        }

        sizeCurr = indexNext;
        for (int i=0; i < indexNext; i++) { 
            currBoxes[i][0] = nextBoxes[i][0];
            currBoxes[i][1] = nextBoxes[i][1];
        }
    }
}


///////////////////////////////////////////////////////////////////////////////


int main() {
    int bx, by, kx, ky, rx, ry, M;
    int countRook, countBishop, countKnight;
    char row[8];

    for (int i=0; i < 8; i++) {
        scanf("%s", row);
        for (int j=0; j < 8; j++) {
            chessboard[i][j] = ((row[j] == '.') ? 1 : 0);
            visitedBishop[i][j] = visitedKnight[i][j] = visitedRook[i][j] = 0;
        }
    }

    // printBoard();

    scanf("%d %d", &bx, &by);
    scanf("%d %d", &kx, &ky);
    scanf("%d %d", &rx, &ry);
    scanf("%d", &M);

    bx--; by--; kx--; ky--; rx--; ry--;

    countRook = countBishop = countKnight = 0;

    if (chessboard[rx][ry])
        rookMoves(rx, ry, &countRook, M, 0, 0);
    
    if (chessboard[bx][by])
        bishopMoves(bx, by, &countBishop, M, 0, 0);

    if (chessboard[kx][ky])
        knightMoves(kx, ky, &countKnight, M);

    printf("%d %d %d", countBishop, countKnight, countRook);

    return 0;
}