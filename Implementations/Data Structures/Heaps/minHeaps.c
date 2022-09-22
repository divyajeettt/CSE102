# include <stdio.h>
# include <stdlib.h>

///////////////////////////////////////////////////////////////////////////////

int insert(int *heap, int *length, int size, int data);

///////////////////////////////////////////////////////////////////////////////

int *makeHeap(int size) {
    int *heap = (int *)malloc(size*sizeof(int));
    return heap;
}

////////////////////////////////////////////////////////////////////////////////

void swap(int *arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

///////////////////////////////////////////////////////////////////////////////

int *heapFromArray(int *array, int n) {
    // Top-Down Approach, O(nlogn)

    int *heap = makeHeap(n);
    int length = 0;
    for (int i=0; i < n; i++)
        insert(heap, &length, n, array[i]);
    
    return heap;
}

///////////////////////////////////////////////////////////////////////////////

void heapify(int *array, int i, int size) {
    int n = size - 1;
    while (i <= (n-1)/2) {
        int min = i;

        if (array[min] > array[2*i + 1])
            min = 2*i + 1;

        if (2*i + 2 <= n && array[min] > array[2*i + 2])
            min = 2*i + 2;
        
        if (min == i)
            break;
        
        swap(array, i, min);
        i = min;
    }
}

int *heapifyArray(int *array, int n) {
    // Bottom-Up Approach, O(n)

    int *heap = makeHeap(n);
    for (int i=0; i < n; i++)
        heap[i] = array[i];
    
    for (int i=n-1; i >= 0; i--)
        heapify(heap, i, n);
    
    return heap;
}

///////////////////////////////////////////////////////////////////////////////

void print(int *heap, int length) {
    for (int i=0; i < length; i++)
        printf("%d ", heap[i]);
    printf("\n");
}

///////////////////////////////////////////////////////////////////////////////

int currMin(int *heap, int length) {
    return ((length != 0) ? heap[0] : -1);
}

///////////////////////////////////////////////////////////////////////////////

int extractMin(int *heap, int *length) {
    int extracted = heap[0];
    swap(heap, 0, --(*length));
    heapify(heap, 0, *length);    // ensures i only goes uptill the deleted node's parent

    return extracted;
}

///////////////////////////////////////////////////////////////////////////////

int insert(int *heap, int *length, int size, int data) {
    // -1 represents OVERFLOW, 1 represents successful insertion

    if (*length == size)
        return -1;
    
    heap[(*length)++] = data;

    int i = (*length) - 1;
    while (heap[(i-1) / 2] > heap[i] && i >= 0) {
        swap(heap, i, (i-1) / 2);
        i = (i - 1) / 2;
    }

    return 1;
}

///////////////////////////////////////////////////////////////////////////////

void decreaseKey(int *heap, int length, int k, int delta) {
    // searches for value k in the heap and decreases it by delta

    int i = 0, found = 0;
    for (; i < length; i++) {
        if (heap[i] == k) {
            heap[i] -= delta;
            found++;
            break;
        }
    }
    if (!found)
        return;

    while (heap[(i-1) / 2] > heap[i] && i >= 0) {
        swap(heap, i, (i-1) / 2);
        i = (i - 1) / 2;
    }
}

///////////////////////////////////////////////////////////////////////////////

int *merge(int *heap1, int *heap2, int length1, int length2) {
    int *merged = makeHeap(length1 + length2);
    int size = length1 + length2;
    
    for (int i=0; i < length1; i++)
        merged[i] = heap1[i];
    
    for (int i=length1; i < length2+length1; i++)
        merged[i] = heap2[i-length1];
    
    return heapifyArray(merged, size);
}

///////////////////////////////////////////////////////////////////////////////

int main() {
    int size = 10;
    int *heap = makeHeap(size);
    int length = 0;

    insert(heap, &length, size, 10);
    insert(heap, &length, size, 7);
    insert(heap, &length, size, 4);
    insert(heap, &length, size, 3);
    insert(heap, &length, size, 9);
    insert(heap, &length, size, 6);
    insert(heap, &length, size, 5);
    insert(heap, &length, size, 8);
    insert(heap, &length, size, 1);
    insert(heap, &length, size, 2);
    
    print(heap, length);
    printf("currMin = %d \n", currMin(heap, length));
    
    int extracted = extractMin(heap, &length); 
    print(heap, length);
    printf("extracted = %d \n\n", extracted);

    decreaseKey(heap, length, 4, 3);
    decreaseKey(heap, length, 10, 9);
    printf("heap after decreasing = "); print(heap, length);

    int array[8] = {1, 4, 5, 2, 6, 0, 9, 10};
    int arraySize = 8;
    int *heapifiedArray = heapifyArray(array, arraySize);

    printf("heap made from array = ");
    print(heapifiedArray, arraySize);

    int *merged = merge(heap, heapifiedArray, length, arraySize);
    int lengthMerged = length + arraySize;
    printf("\nMerged Heaps = ");
    print(merged, lengthMerged);

    return 0;
}