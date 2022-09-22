# include <stdio.h>
typedef long long ll;

///////////////////////////////////////////////////////////////////////////////

// void printArray(int arr[], int n) {
//     printf("[");
//     for (int i=0; i < n; i++) {
//         if (i+1 != n)
//             printf("%d, ", arr[i]);
//         else
//             printf("%d] \n", arr[i]);
//     }
// }

///////////////////////////////////////////////////////////////////////////////

void merge(int arr[], int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int left[n1], right[n2];

    for (int p=0; p < n1; p++)
        left[p] = arr[low + p];
    
    for (int q=0; q < n2; q++)
        right[q] = arr[mid + q + 1];

    int i = 0, j = 0, k = low;

    for (; i<n1 && j<n2; k++) {
        if (left[i] <= right[j])
            arr[k] = left[i++];
        else
            arr[k] = right[j++];
    }

    while (i < n1)
        arr[k++] = left[i++];

    while (j < n2)
        arr[k++] = right[j++];
}

void mergeSort(int array[], int start, int end) {
    if (start >= end)
        return;
    
    int mid = (start + end) / 2;
    mergeSort(array, start, mid);
    mergeSort(array, mid+1, end);
    merge(array, start, mid, end);
}

///////////////////////////////////////////////////////////////////////////////

ll damage(int timeArray[], int n, ll k) {
    // damage that could be dealt to X
    ll X = 0, diff;
    for (int i=0; i < n-1; i++) {
        diff = timeArray[i+1] - timeArray[i];
        if (diff > k)
            X += k;
        else
            X += diff;
        // printf("diff=%d, sum=%d \n", diff, X);
    }
    return (X + k);
}

///////////////////////////////////////////////////////////////////////////////

ll binarySearchK(ll start, ll end, int array[], int n, ll h) {
    ll mid = (start + end) / 2;
    ll damageX = damage(array, n, mid);

    if (start > end)
        return start;
    else if (damageX < h)
        return binarySearchK(mid+1, end, array, n, h);
    else
        return binarySearchK(start, mid-1, array, n, h);
}

// int linearSearchK(int array[], int n, int h) {
//     for (int i=1; i <= h; i++) {
//         if (damage(array, n, i) >= h)
//             return i;
//     }
// }

///////////////////////////////////////////////////////////////////////////////

int main() {
    int q;
    scanf("%d", &q);

    for (int i=0; i < q; i++) {
        int n; ll h;
        scanf("%d %lld", &n, &h);
        
        int arr[n];
        for (int j=0; j < n; j++) 
            scanf("%d", &arr[j]);

        // printArray(arr, n);
        mergeSort(arr, 0, n-1);
        // printArray(arr, n);

        printf("%lld \n", binarySearchK(1, h, arr, n, h));        
        // printf("%d \n\n", linearSearchK(arr, n, h));
    }

    return 0;
}