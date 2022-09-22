# include <stdio.h>

///////////////////////////////////////////////////////////////////////////////

int chessboard[8][8], visitedKnight[8][8];

int isValid(int x, int y) {
    return ((0 <= x && x < 8) && (0 <= y && y < 8));
}

///////////////////////////////////////////////////////////////////////////////


void knightMoves(int kx, int ky, int *countKnight, int moves) {
    if (!chessboard[kx][ky])
        return;

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
    int kx, ky, M;
    int countKnight;
    char row[8];

    for (int i=0; i < 8; i++) {
        scanf("%s", row);
        for (int j=0; j < 8; j++) {
            chessboard[i][j] = ((row[j] == '.') ? 1 : 0);
            visitedKnight[i][j] = 0;
        }
    }

    scanf("%d %d", &kx, &ky);
    scanf("%d", &M);

    kx--; ky--;

    countKnight = 0;

    knightMoves(kx, ky, &countKnight, M);

    printf("%d", countKnight);

    return 0;
}