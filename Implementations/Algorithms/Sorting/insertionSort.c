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

void insertionSort(int *arr, int n) {
    // Implement the Insertion Sort Algorithm

    int j, key;
    for (int i=1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

///////////////////////////////////////////////////////////////////////////////

int main() {
    int arr[10] = {1, 0, 4, 6, 5, 3, 2, 7, 8, 9};

    printf("Array before sorting: ");
    printArray(arr, 10);

    insertionSort(arr, 10);

    printf("Array after sorting: ");
    printArray(arr, 10);

    return 0;
}