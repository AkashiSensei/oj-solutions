/*
 * Find the minimum number of scalar multiplications needed to multiply
 * a chain of matrices using interval dynamic programming.
 */

#include<stdio.h>
long long MIN[325][325];
long long EDGE[325];

int main() {
    long long min, length, n;
    scanf("%lld", &n);

    for(int i = 0; i <= n; i++) {
        scanf("%lld", &EDGE[i]);
    }

    long long temp;
    for(length = 2; length <= n; length++) {
        for(int i = 1; i <= n - length + 1; i++) {
            int j = i + length - 1;
            MIN[i][j] = 9223372036854775806;
            for(int k = i; k <= j - 1; k++) {
                temp = MIN[i][k] + MIN[k+1][j] + EDGE[i - 1] * EDGE[k] * EDGE[j];
                if(temp < MIN[i][j]) {
                    MIN[i][j] = temp;
                }
            }
        }
    }

    printf("%lld", MIN[1][n]);
    return 0;
}