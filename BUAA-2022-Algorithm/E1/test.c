/*
 * Interactive arithmetic experiment: repeatedly compute C(n, m)
 * from precomputed floating-point factorials and print the result.
 */

#include<stdio.h>
#define DELTA 1e-3

#define MAX_RANK 50

double RANK[MAX_RANK + 1];

int main() {
    RANK[1] = 1;
    for(int i = 2; i < MAX_RANK + 1; i++) {
        RANK[i] = RANK[i - 1] * i;
    }
    int n, m;
    double ans;
    while(1) {
        scanf("%d %d", &n, &m);
        ans = RANK[n] / RANK[m] / RANK[n - m];
        printf("%lf\n", ans);
    }
}