# include <stdio.h>

///////////////////////////////////////////////////////////////////////////////

int binarySearch(int *arr, int left, int right, int element) {
    // Implement the Binary Search Algorithm iteratively
    // Returns index of element if found, and -1 otherwise

    int mid;

    while (left <= right) {
        mid = (left + right) / 2;
        if (arr[mid] == element)
            return mid;
        else if (element < arr[mid])
            right = mid - 1;
        else
            left = mid + 1;
    }
    return -1;
}

///////////////////////////////////////////////////////////////////////////////

// int binarySearch(int *arr, int left, int right, int element) {
//     // Implement the Binary Search Algorithm recursively
//     // Returns index of element if found, and -1 otherwise

//     if (left > right)
//         return -1;

//     int mid = (left + right) / 2;

//     if (arr[mid] == element)
//         return mid;
//     else if (element < arr[mid])
//         return binarySearch(arr, left, mid-1, element);
//     else
//         return binarySearch(arr, mid+1, right, element);
// }

///////////////////////////////////////////////////////////////////////////////

int main() {
    int arr[10] = {2, 4, 6, 7, 9, 10, 11, 15, 19, 20};
    int element = 6;

    printf("%d \n", binarySearch(arr, 0, 9, element));

    return 0;
}