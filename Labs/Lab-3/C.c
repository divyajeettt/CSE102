# include <stdio.h>

///////////////////////////////////////////////////////////////////////////////

// void printArray(int arr[], int start, int end) {
//     printf("[");
//     for (int i=start; i < end; i++) {
//         if (i+1 != end)
//             printf("%d, ", arr[i]);
//         else
//             printf("%d] \n", arr[i]);
//     }
// }

///////////////////////////////////////////////////////////////////////////////

int min(int x, int y) {
    return ((x > y) ? y : x);
}

///////////////////////////////////////////////////////////////////////////////

int kBeautiful(int arr[], int start, int end, int k) {
    // returns the # of ops to make arr[start:end] k-beautiful
    int count = 0;
    for (int i=start; i < end; i++) {
        if (arr[i] != k)
            count++;
    }
    return count;
}

///////////////////////////////////////////////////////////////////////////////

int kSmooth(int arr[], int start, int end, int k) {
    // returns the # of ops to make arr[start:end] k-smooth

    if (end-start == 1)
        return (arr[start] != k);

    int mid = (start + end - 1) / 2;
    
    // printArray(arr, start, mid+1); printArray(arr, mid+1, end);

    // arr[start:mid] is k-beautiful && arr[mid+1:end] is (k+1)-smooth
    // arr[start:mid] is (k+1)-smooth && arr[mid+1:end] is k-beautiful

    return min(
        kBeautiful(arr, start, mid+1, k) + kSmooth(arr, mid+1, end, k+1), 
        kBeautiful(arr, mid+1, end, k) + kSmooth(arr, start, mid+1, k+1)
    );
}

///////////////////////////////////////////////////////////////////////////////

int main() {
    int N, k;
    scanf("%d %d", &N, &k);

    int A[N]; 
    for (int i=0; i < N; i++)
        scanf("%d", &A[i]);

    printf("%d", kSmooth(A, 0, N, k));

    return 0;
}