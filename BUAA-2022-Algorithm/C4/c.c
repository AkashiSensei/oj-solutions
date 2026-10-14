/*
 * Solve the 0/1 knapsack problem with dynamic programming:
 * maximize total value within the weight capacity, using each item at most once.
 */

#include<stdio.h>
#include<stdlib.h>

struct item
{
    long long int value, weight;
} LIST[100005];
long long int F[100005];

long long int max(long long int a, long long int b) {
    return a > b ? a : b;
}

int main() {
    int n, package;
    scanf("%d %d", &n, &package);
    for(int i = 0; i < n; i++) {
        scanf("%lld %lld", &LIST[i].value, &LIST[i].weight);
    }

    for(int i = 0; i < n; i++) {
        for(int j = package; j >= 1; j--) {
            if(j >= LIST[i].weight) {
                F[j] = max(F[j], F[j - LIST[i].weight] + LIST[i].value);
            }
        }
    }
    printf("%lld", F[package]);
    return 0;
}