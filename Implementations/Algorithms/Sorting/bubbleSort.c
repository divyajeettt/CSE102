# include <stdio.h>

///////////////////////////////////////////////////////////////////////////////

void printArray(int *arr, int n) {
    printf("[");
    for (int i=0; i < n; i++) {
        if (i+1 != n)
            printf("%d, ", arr[i]);
        else
            printf("%d] \n", arr[i]);
    }
}

///////////////////////////////////////////////////////////////////////////////

void bubbleSort(int *arr, int n) {
    // Implement the Bubble Sort Algorithm iteratively

    for (int i=0; i < n; i++) {
        for (int j=0; j < n-i-1; j++) {
            if (arr[j+1] < arr[j]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////

// void bubbleSort(int *arr, int n, int i) {
//     // Implement the Bubble Sort Algorithm recursively

//     if (i == n)
//         return;

//     for (int j=0; j < n-i-1; j++) {
//         if (arr[j+1] < arr[j]) {
//             int temp = arr[j];
//             arr[j] = arr[j+1];
//             arr[j+1] = temp;
//         }
//     }
//     bubbleSort(arr, n, i+1);
// }

///////////////////////////////////////////////////////////////////////////////

int main() {
    int arr[10] = {1, 0, 4, 6, 5, 3, 2, 7, 8, 9};

    printf("Array before sorting: ");
    printArray(arr, 10);

    bubbleSort(arr, 10);
    // bubbleSort(arr, 10, 0);

    printf("Array after sorting: ");
    printArray(arr, 10);

    return 0;
}