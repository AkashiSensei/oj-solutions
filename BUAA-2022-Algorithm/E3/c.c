/*
 * Use interval dynamic programming to choose an optimal binary search tree
 * for ordered keys with given access weights, minimizing weighted search cost.
 */

#include<stdio.h>

unsigned long long E[502][502];
unsigned long long W[502][502];

int main() {
    int n;
    sleep(10);
    scanf("%d", &n);

    for(int i = 1; i <= n; i++) {
        scanf("%d", &W[i][i]);
    }

    int i, j, k, length;
    unsigned long long t;
    for(length = 1; length <= n; length++) {
        for(i = 1; i <= n - length + 1; i++) {
            j = i + length - 1;
            E[i][j] = 18446744073709551615;
            W[i][j] = W[i][j - 1] + W[j][j];
            for(k = i; k <= j; k++) {
                t = E[i][k - 1] + E[k + 1][j] + W[i][j];
                if(t < E[i][j]) {
                    E[i][j] = t;
                }
            }
        }
    }

    printf("%llu", E[1][n]);
}