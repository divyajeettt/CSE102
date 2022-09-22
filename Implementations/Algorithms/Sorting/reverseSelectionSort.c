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

void reverseSelectionSort(int *arr, int n) {
    // Implement the Reverse Selection Sort Algorithm iteratively

    int maxIndex, max, temp;

    for (int i=n-1; i > -1; i--) {
        // search for max([:i]) and swap it with arr[i]

        max = arr[i];
        maxIndex = i;

        for (int j=0; j < i; j++) {
            if (arr[j] > max) {
                max = arr[j];
                maxIndex = j;
            }
        }

        if (maxIndex != i) {
            temp = arr[i];
            arr[i] = arr[maxIndex];
            arr[maxIndex] = temp;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////

// void reverseSelectionSort(int *arr, int start) {
//     // Implement the Reverse Selection Sort Algorithm recursively

//     if (start == 0)
//         return;

//     int maxIndex, max, temp;

//     max = arr[start];
//     maxIndex = start;

//     for (int j=0; j < start; j++) {
//         if (arr[j] > max) {
//             max = arr[j];
//             maxIndex = j;
//         }
//     }

//     if (maxIndex != start) {
//         temp = arr[start];
//         arr[start] = arr[maxIndex];
//         arr[maxIndex] = temp;
//     }

//     reverseSelectionSort(arr, start-1);
// }

///////////////////////////////////////////////////////////////////////////////

int main() {
    int arr[10] = {1, 0, 4, 6, 5, 3, 2, 7, 8, 9};

    printf("Array before sorting: ");
    printArray(arr, 10);

    reverseSelectionSort(arr, 10);
    // reverseSelectionSort(arr, 9);

    printf("Array after sorting: ");
    printArray(arr, 10);

    return 0;
}