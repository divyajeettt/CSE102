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

int partition(int *arr, int start, int end) {
    int temp;
    int pivot = arr[end];  // Always assume pivot as the last element
    int i = start - 1;     // Correct position of the pivot so far

    for (int j=start; j <= end-1; j++) {
        if (arr[j] < pivot) {
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    temp = arr[i+1];
    arr[i+1] = arr[end];
    arr[end] = temp;

    return (i + 1);
}

void quickSort(int *arr, int start, int end) {
    // Implement the Quick Sort Algorithm

    if (start >= end)
        return;
    else {
        // arr[partitionIndex] is now at the right place
        int partitionIndex = partition(arr, start, end);
        quickSort(arr, start, partitionIndex-1);
        quickSort(arr, partitionIndex+1, end);
    }
}

///////////////////////////////////////////////////////////////////////////////

int main() {
    int arr[10] = {1, 0, 4, 6, 5, 3, 2, 7, 8, 9};

    printf("Array before sorting: ");
    printArray(arr, 10);

    quickSort(arr, 0, 9);

    printf("Array after sorting: ");
    printArray(arr, 10);

    return 0;
}