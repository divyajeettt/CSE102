# include <stdio.h>
# include <stdlib.h>

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

void merge(int *left, int n1, int *right, int n2, int *answer) {
    // Iterative 2-Way Merge Algorithm

    int i=0, j=0, k=0;

    for (; k < n1+n2 && i < n1 && j < n2; k++) {
        if (left[i] < right[j])
            answer[k] = left[i++];
        else
            answer[k] = right[j++];
    }

    while (i < n1)
        answer[k++] = left[i++];

    while (j < n2)
        answer[k++] = right[j++];
}

///////////////////////////////////////////////////////////////////////////////

int main() {
    int arr1[5] = {1, 2, 5, 7, 9};
    int arr2[5] = {0, 3, 4, 6, 8};
    int *array = (int *)malloc(10*sizeof(int));

    printf("arr1 = "); printArray(arr1, 5);
    printf("arr2 = "); printArray(arr2, 5);

    merge(arr1, 5, arr2, 5, array);

    printf("Merged Array = "); printArray(array, 10);

    return 0;
}