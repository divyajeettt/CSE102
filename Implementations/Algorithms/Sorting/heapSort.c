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

void heapify(int *arr, int i, int n) {
    int end = n - 1;
    while (i <= (end-1)/2) {
        int max = i;

        if (arr[max] < arr[2*i + 1])
            max = 2*i + 1;
        if (2*i + 2 <= end && arr[max] < arr[2*i + 2])
            max = 2*i + 2;

        if (max == i)
            break;

        int temp = arr[max];
        arr[max] = arr[i];
        arr[i] = temp;

        i = max;
    }
}

void extractMax(int *arr, int n) {
    int temp = arr[0];
    arr[0] = arr[n - 1];
    arr[n - 1] = temp;

    heapify(arr, 0, n-2);
}

///////////////////////////////////////////////////////////////////////////////

void heapSort(int *arr, int n) {
    // implement the Heap Sort Algorithm

    // heapify the array
    for (int i=n-1; i >=0; i--) {
        heapify(arr, i, n);
    }
    // keep extracting the Maximum from the heap
    for (int i=n; i > 1; i--)
        extractMax(arr, i);
}

///////////////////////////////////////////////////////////////////////////////

int main() {
    int arr[10] = {1, 0, 4, 6, 5, 3, 2, 7, 8, 9};

    printf("Array before sorting: ");
    printArray(arr, 10);

    heapSort(arr, 10);

    printf("Array after sorting: ");
    printArray(arr, 10);

    return 0;
}