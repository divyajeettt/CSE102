# include <stdio.h>

///////////////////////////////////////////////////////////////////////////////

int fibonacci(int n) {
    // Iterative Fibonacci

    int f1 = 0, f2 = 1, f3;

    if (n == 0 || n == 1)
        return n;
    else {
        for (int i=2; i <= n; i++) {
            f3 = f1 + f2;
            f1 = f2;
            f2 = f3;
        }
        return f3;
    }
}

///////////////////////////////////////////////////////////////////////////////

// int fibonacci(int n) {
//     // Recursive Fibonacci

//     if (n == 0 || n == 1)
//         return n;
//     else
//         return fibonacci(n-1) + fibonacci(n-2);
// }

///////////////////////////////////////////////////////////////////////////////

// int fibonacci(int n, int fn[1], int fn_1[1]) {
//     // Recursive Fibonacci, better

//     if (n == 0)
//         return 0;
//     else if (n == 1) {
//         fn[0] = 1;
//         fn_1[0] = 0;
//         return fn[0];
//     }
//     else {
//         fibonacci(n-1, fn, fn_1);
//         int temp = fn[0] + fn_1[0];
//         fn_1[0] = fn[0];
//         fn[0] = temp;
//         return fn[0];
//     }
// }

//////////////////////////////////////////////////////////////////////////////

int main() {
    int n = 2;
    int a1[1] = {1}, a2[1] = {1};

    printf("%d \n", fibonacci(n));
    // printf("%d \n", fibonacci(n, a1, a2));

    return 0;
}