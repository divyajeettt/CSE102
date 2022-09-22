# include <stdio.h>

///////////////////////////////////////////////////////////////////////////////

int factorial(int n) {
    // Iterative Factorial

    int total = 1;
    for (int i=1; i <= n; i++)
        total *= i;
    return total;
}

///////////////////////////////////////////////////////////////////////////////

// int factorial(int n) {
//     // Recursive Factorial

//     if (n <= 1)
//         return 1;
//     else
//         return n * factorial(n-1);
// }

///////////////////////////////////////////////////////////////////////////////

int main() {
    int n = 5;
    printf("%d \n", factorial(n));

    return 0;
}