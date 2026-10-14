/*
 * Answer queries for a recurrence-defined sequence modulo 998244353.
 * This version precomputes only indices 1 through 9.
 */

#include<stdio.h>

unsigned long long LIST[100];

int main() {
    int n;
    scanf("%d", &n);
    LIST[1] = 1;
    LIST[2] = 2;
    LIST[3] = 7;
    LIST[4] = 15;
    for(int i = 5; i < 10; i++) {
        LIST[i] = (LIST[i - 1] + LIST[i - 2] + 4 * LIST[i - 3] + 2 * LIST[i - 4]) % 998244353;
    }

    int index;
    for(int i = 0; i < n; i++) {
        scanf("%d", &index);
        printf("%llu\n", LIST[index]);
    }
}