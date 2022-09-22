# include <stdio.h>

///////////////////////////////////////////////////////////////////////////////

void move(int n, char *A, char *B, char *C) {
    if (n == 0)
        return;
    else {
        move(n-1, A, C, B);
        printf("Move ring from %s to %s \n", A, C);
        move(n-1, B, A, C);
    }
}

///////////////////////////////////////////////////////////////////////////////

int main() {
    int n = 3;
    move(n, "Tower A", "Tower B", "Tower C");
    return 0;
}