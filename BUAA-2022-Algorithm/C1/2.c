/*
 * Evaluate two polynomials at each pair of query points using Horner's method.
 * Print the product of their values modulo 10007.
 */

#include<stdio.h>

int A[30005], B[30005];

int main() {
    int xLen, yLen,n;
    scanf("%d", &xLen);
    for(int i = 0; i <= xLen; i++) {
        scanf("%d", &A[i]);
    }
    scanf("%d", &yLen);
    for(int i = 0; i <= yLen; i++) {
        scanf("%d", &B[i]);
    }

    unsigned long long resultX, resultY;
    unsigned long long x, y;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        resultX = 0;
        resultY = 0;
        scanf("%llu %llu", &x, &y);
        for(int j = xLen; j > 0; j--) {
            resultX = (resultX + A[j]);
            resultX = (resultX * x) % 10007;
        }
        resultX = (resultX + A[0]) % 10007;

        for(int j = yLen; j > 0; j--) {
            resultY = (resultY + B[j]);
            resultY = (resultY * y) % 10007;
        }
        resultY = (resultY + B[0]) % 10007;

        printf("%d\n", (resultX * resultY) % 10007);
    }
}