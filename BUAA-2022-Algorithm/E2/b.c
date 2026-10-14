/*
 * Precompute a recurrence-defined sequence and auxiliary accumulated values
 * modulo 998244353, then answer queries by index.
 */

#include<stdio.h>

unsigned long long LIST[1000005];
unsigned long long ADD[1000005];

int main() {
    int n;
    scanf("%d", &n);
    LIST[1] = 1;
    LIST[2] = 2;
    LIST[3] = 9;
    LIST[4] = 21;
    LIST[5] = 48;

    ADD[0] = 1;
    ADD[1] = 1;

    for(int i = 6; i < 1000005; i++) {
        LIST[i] = (LIST[i - 1] + LIST[i - 2] + 6 * LIST[i - 3] + 4 * LIST[i - 4]) % 998244353;
        ADD[i - 4] = (ADD[i - 6] + LIST[i - 4]) % 998244353;
        LIST[i] = (LIST[i] + 2 * (ADD[i - 5] + ADD[i - 6])) % 998244353;
    }

    int index;
    for(int i = 0; i < n; i++) {
        scanf("%d", &index);
        printf("%llu\n", LIST[index]);
    }
}