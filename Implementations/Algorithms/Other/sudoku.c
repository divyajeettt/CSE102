# include <stdio.h>
# include <stdlib.h>

///////////////////////////////////////////////////////////////////////////////

void printBoard(int **board) {
    for (int i=0; i < 9; i++) {
        for (int j=0; j < 9; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

///////////////////////////////////////////////////////////////////////////////

int *findEmpty(int **board) {
    for (int i=0; i < 9; i++) {
        for (int j=0; j < 9; j++) {
            if (board[i][j] == 0) {
                int *empty = (int *)malloc(2*sizeof(int));
                empty[0] = i; empty[1] = j;
                return empty;
            }
        }
    }
    return NULL;
}

///////////////////////////////////////////////////////////////////////////////

int valid(int **board, int num, int x, int y) {
    for (int i=0; i < 9; i++) {
        if ((board[x][i] == num) && (y != i))
            return 0;
        if ((board[i][y] == num) && (x != i))
            return 0;
    }

    int bx = (x / 3) * 3;
    int by = (y / 3) * 3;

    for (int i=bx; i < bx+3; i++) {
        for (int j=by; j < by+3; j++) {
            if ((board[i][j] == num) && (i != x || j != y))
                return 0;
        }
    }
    return 1;
}

///////////////////////////////////////////////////////////////////////////////

int solve(int **board) {
    int *indices = findEmpty(board);

    if (indices == NULL)
        return 1;

    int x = indices[0], y = indices[1];

    for (int num=1; num <= 9; num++) {
        if (valid(board, num, x, y)) {
            board[x][y] = num;
            if (solve(board))
                return 1;
            else
                board[x][y] = 0;
        }
    }

    return 0;
}

///////////////////////////////////////////////////////////////////////////////

int main() {
    int **board = (int **)malloc(9*sizeof(int *));
    for (int i=0; i < 9; i++)
        board[i] = (int *)malloc(9*sizeof(int));

    for (int i=0; i < 9; i++) {
        for (int j=0; j < 9; j++) {
            scanf("%d", &board[i][j]);
        }
    }

    printf("\n");
    printBoard(board);
    printf("\n");

    if (solve(board))
        printBoard(board);
    else
        printf("NO SOLUTION");
}