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

void doubleSelectionSort(int *arr, int n) {
    // Implement the Double Selection Sort Algorithm iteratively

    int minIndex, maxIndex, min, max, temp, i1, i2;

    for (int i=0; i < n/2; i++) {
        i1 = i;
        i2 = n - i - 1;

        min = arr[i1]; max = arr[i2];
        minIndex = i1; maxIndex = i2;

        for (int j=i1; j < i2; j++) {
            if (arr[j] < min) {
                min = arr[j];
                minIndex = j;
            }
            else if (arr[j] > max) {
                max = arr[j];
                maxIndex = j;
            }
        }

        if (minIndex != i1) {
            temp = arr[i1];
            arr[i1] = arr[minIndex];
            arr[minIndex] = temp;
        }
        if (maxIndex != i2) {
            temp = arr[i2];
            arr[i2] = arr[maxIndex];
            arr[maxIndex] = temp;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////

// void doubleSelectionSort(int *arr, int n, int start) {
//     // Implement the Double Selection Sort Algorithm recursively

//     if (n == start)
//         return;

//     int minIndex, maxIndex, min, max, temp, i1, i2;

//     i1 = start;
//     i2 = n - start - 1;

//     min = arr[i1]; max = arr[i2];
//     minIndex = i1; maxIndex = i2;

//     for (int j=i1; j < i2; j++) {
//         if (arr[j] < min) {
//             min = arr[j];
//             minIndex = j;
//         }
//         else if (arr[j] > max) {
//             max = arr[j];
//             maxIndex = j;
//         }
//     }

//     if (minIndex != i1) {
//         temp = arr[i1];
//         arr[i1] = arr[minIndex];
//         arr[minIndex] = temp;
//     }
//     if (maxIndex != i2) {
//         temp = arr[i2];
//         arr[i2] = arr[maxIndex];
//         arr[maxIndex] = temp;
//     }

//     doubleSelectionSort(arr, n-1, start+1);
// }

///////////////////////////////////////////////////////////////////////////////

int main() {
    int arr[10] = {1, 0, 4, 6, 5, 3, 2, 7, 8, 9};

    printf("Array before sorting: ");
    printArray(arr, 10);

    doubleSelectionSort(arr, 10);
    // doubleSelectionSort(arr, 10, 0);

    printf("Array after sorting: ");
    printArray(arr, 10);

    return 0;
}