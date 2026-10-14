/*
 * Solve rod cutting with dynamic programming: maximize the total selling price
 * by splitting a rod into pieces with the given prices.
 */

#include<stdio.h>
long long PRICE[10005];
long long LIST[10005];


int main() {
    long long length, max, n;
    scanf("%lld", &n);
    PRICE[0] = 0;
    for(int i = 1; i <= n; i++) {
        scanf("%lld", &PRICE[i]);
    }

    LIST[1] = PRICE[1];
    for(length = 1; length <= n; length++) {
        max = 0;
        for(int first = 1; first <= length; first++) {
            if(PRICE[first] + LIST[length - first] > max) {
                max = PRICE[first] + LIST[length - first];
            }
        }
        LIST[length] = max;
    }

    printf("%lld", LIST[n]);
}