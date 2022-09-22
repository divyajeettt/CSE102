# include <stdio.h>

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

    int i=0, j=0, k=start;

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

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int array[m][2];

    for (int i=0; i < m; i++)
        scanf("%d %d", &array[i][0], &array[i][1]);

    // printArray(array, m);
    mergeSort(array, 0, m-1);
    // printArray(array, m);

    int flag, counter=0;
    for (int num=1; num < n+1; num++) {
        flag = 0;
        for (int i=counter; i < m; i++) {
            if (array[i][0] > num)
                break;
            if (array[i][0] == num) {
                printf("%d ", array[i][1]);
                flag++; counter++;
            }
        }
        if (!flag)
            printf("-1");
        printf("\n");
    }

    return 0;
}