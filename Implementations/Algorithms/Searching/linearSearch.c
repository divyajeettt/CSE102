# include <stdio.h>

///////////////////////////////////////////////////////////////////////////////

int linearSearch(int *arr, int n, int element) {
    // Implement the Linear Search Algorithm iteratively
    // Returns index of element if found, and -1 otherwise

    for (int i=0; i < n; i++) {
        if (arr[i] == element)
            return i;
    }
    return -1;
}

///////////////////////////////////////////////////////////////////////////////

// int linearSearch(int *arr, int n, int element) {
//     // Implement the Linear Search Algorithm recursively
//     // Returns index of element if found, and -1 otherwise

//     if (n == 0)
//         return -1;
//     else if (arr[n-1] == element)
//         return n - 1;
//     else
//         return linearSearch(arr, n-1, element);
// }

///////////////////////////////////////////////////////////////////////////////

int main() {
    int arr[10] = {1, 0, 4, 6, 5, 3, 2, 7, 8, 9};
    int element = 6;

    printf("%d \n", linearSearch(arr, 10, element));

    return 0;
}