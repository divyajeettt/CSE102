# include <stdio.h>


///////////////////////////////////////////////////////////////////////////////


// void printArray(int arr[][2], int n) {
//     printf("[");
//     for (int i=0; i < n; i++) {
//         if (i+1 != n)
//             printf("[%d, %d], ", arr[i][0], arr[i][1]);
//         else
//             printf("[%d, %d]] \n", arr[i][0], arr[i][1]);
//     }
// }


///////////////////////////////////////////////////////////////////////////////


void merge(int array[][2], int start, int mid, int end) {
    int n1 = mid - start + 1;
    int n2 = end - mid;

    int left[n1][2], right[n2][2];

    for (int p=0; p < n1; p++) {
        left[p][0] = array[start + p][0];
        left[p][1] = array[start + p][1];
    }
    
    for (int q=0; q < n2; q++) {
        right[q][0] = array[mid + q + 1][0];
        right[q][1] = array[mid + q + 1][1];
    }

    int i = 0, j = 0, k = start;
    for (; i<n1 && j<n2; k++) {
        if (left[i][0] <= right[j][0]) {
            array[k][0] = left[i][0];
            array[k][1] = left[i++][1];
        } else {
            array[k][0] = right[j][0];
            array[k][1] = right[j++][1];
        }
    }

    while (i < n1) {
        array[k][0] = left[i][0];
        array[k++][1] = left[i++][1];
    }
    
    while (j < n2) {
        array[k][0] = right[j][0];
        array[k++][1] = right[j++][1];
    }
}


void mergeSort(int array[][2], int start, int end) {
    if (start >= end)
        return;
    
    int mid = (start + end) / 2;

    mergeSort(array, start, mid);
    mergeSort(array, mid+1, end);
    merge(array, start, mid, end);
}


///////////////////////////////////////////////////////////////////////////////


int main() {
    int t, n, count, totalSub, num, index, x;
    scanf("%d", &t);

    for (int i=0; i < t; i++) {
        scanf("%d", &n);

        int indices[n][2];
        
        for (int j=0; j < n; j++) {
            scanf("%d", &indices[j][0]);
            indices[j][1] = j+1;
        }

        // printf("Before Sorting: "); printArray(indices, n);

        mergeSort(indices, 0, n-1);
        totalSub = count = 0;

        // print("After Sorting: "); printArray(indices, n);

        for (int j=0; j < n; j++) {
            num = indices[j][0] - totalSub;
            index = indices[j][1];

            // printf("count=%d, totalSub=%d \n", count, totalSub);
            if (num < 0)
                continue;

            // printf("num=%d, index=%d, totalSub=%d \n", num, index, totalSub);

            x = (num/index) + 1;
            count += x;
            totalSub += x * index;

            // printf("new totalSub=%d, count=%d \n", totalSub, count);
        }

        printf("%d \n", count);
    }

    return 0;
}