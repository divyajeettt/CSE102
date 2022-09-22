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

void selectionSort(int *arr, int n) {
    // Implement the Selection Sort Algorithm iteratively

    int minIndex, min, temp;

    for (int i=0; i < n/2; i++) {
        // search for min(arr[i:]) and swap it with arr[i]

        min = arr[i];
        minIndex = i;

        for (int j=i+1; j < n; j++) {
            if (arr[j] < min) {
                min = arr[j];
                minIndex = j;
            }
        }

        if (minIndex != i) {
            temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////

// void selectionSort(int *arr, int n, int start) {
//     // Implement the Selection Sort Algorithm recursively

//     if (n == start)
//         return;

//     int minIndex, min, temp;

//     min = arr[start];
//     minIndex = start;

//     for (int j=start+1; j < n; j++) {
//         if (arr[j] < min) {
//             min = arr[j];
//             minIndex = j;
//         }
//     }

//     if (minIndex != start) {
//         temp = arr[start];
//         arr[start] = arr[minIndex];
//         arr[minIndex] = temp;
//     }

//     selectionSort(arr, n-1, start+1);
// }

///////////////////////////////////////////////////////////////////////////////

int main() {
    int arr[10] = {1, 0, 4, 6, 5, 3, 2, 7, 8, 9};

    printf("Array before sorting: ");
    printArray(arr, 10);

    selectionSort(arr, 10);
    // selectionSort(arr, 10, 0);

    printf("Array after sorting: ");
    printArray(arr, 10);

    return 0;
}