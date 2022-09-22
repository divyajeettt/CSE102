# include <stdio.h>

///////////////////////////////////////////////////////////////////////////////

int power(int x, int n) {
    // Iterative Power

    int total = 1;
    for (int i=1; i <= n; i++)
        total *= x;
    return total;
}

///////////////////////////////////////////////////////////////////////////////

// int power(int x, int n) {
//     // Recursive Power

//     if (n == 1)
//         return x;
//     else
//         return x * power(x, n-1);
// }

///////////////////////////////////////////////////////////////////////////////

// int power(int x, int n) {
//     // Recursive Power, better

//     if (n == 1)
//         return x;
//     else if (n%2 == 0) {
//         int half = power(x, n/2);
//         return half * half;
//     } else {
//         int half = power(x, (n-1)/2);
//         return x * half * half;
//     }
// }

///////////////////////////////////////////////////////////////////////////////

int main() {
    int x = 10, n = 5;
    printf("%d \n", power(x, n));

    return 0;
}