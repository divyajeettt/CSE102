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
    // Implement the Lomuto Partition Algorithm

    int temp;
    int pivot = arr[end];  // Always assume pivot as the last element
    int i = start - 1;     // Keeps track of elements larger than the pivot

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

///////////////////////////////////////////////////////////////////////////////

// int partition(int *array, int low, int high) {
//     // Implement the Hoare Partition Algorithm

//     int temp;
//     int pivot = array[low];  // Always assume first element to be the pivot

//     // i, j are left, right index pointers
//     int i = low;  // i checks for elements greater than pivot
//     int j = high; // j checks for elements less than the pivot

//     while (i < j) {
//         while (array[i] < pivot)
//             i++;
//         while (array[j] > pivot)
//             j--;

//         temp = array[i];
//         array[i] = array[j];
//         array[j] = temp;
//     }

//     temp = array[low];
//     array[low] = array[j-1];
//     array[j-1] = temp;

//     return (j - 1);
// }

///////////////////////////////////////////////////////////////////////////////

int main() {
    int arr[10] = {1, 6, 0, 2, 4, 3, 7, 9, 8, 5};

    printf("Array before partitioning: ");
    printArray(arr, 10);

    partition(arr, 0, 9);

    printf("Array after partitioning: ");
    printArray(arr, 10);

    return 0;
}