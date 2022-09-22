# include <stdio.h>


// int max(int A[], int n) {
//     int maxEle = A[0];
//     for (int i=1; i < n; i++) {
//         if (A[i] > maxEle)
//             maxEle = A[i];
//     }
//     return maxEle;
// }


int minTime(int *A, int k, int n) {
    if (n == 1)
        return (k * A[0]);
}


int main() {
    int n, k;
    scanf("%d", &n);    // # of machines
    scanf("%d", &k);    // # of chocolates

    int A[n];
    for (int i=0; i < n; i++)
        scanf("%d", &A[i]);

    // need to make k chocolates
    // n machines in the factory
    // i-th machine takes A[i] sec to make a chocolate

    return 0;
}