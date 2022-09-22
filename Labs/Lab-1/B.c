# include <stdio.h>


// void slice(int array[], int ans[], int i, int j) {
//     for (int x=i; x < j; x++)
//         ans[x-i] = array[x];
// }


int sum(int *array, int n) {
    int total = 0;

    for (int i=0; i < n; i++)
        total += array[i];

    return total;
}


int main() {
    int n, k, x;
    scanf("%d %d %d", &n, &k, &x);

    int A[n];
    for (int i=0; i < n; i++)
        scanf("%d", &A[i]);

    return 0;
}