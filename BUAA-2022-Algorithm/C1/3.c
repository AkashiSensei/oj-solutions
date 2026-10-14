/*
 * For each array position, compute the product of all other elements
 * modulo 1000000006 using prefix and suffix products.
 */

#include<stdio.h>
#include<string.h>

unsigned int LIST[100005][3];

int main() {
    int t;
    scanf("%d", &t);
    
    for(int i = 0; i < t; i++) {
        int n;
        unsigned long long temp;
        scanf("%d", &n);
        memset(LIST, 0, sizeof(LIST));

        scanf("%u", &LIST[0][0]);
        LIST[0][1] = 1;
        LIST[n - 1][2] = 1;
        for(int j = 1; j < n; j++) {
            scanf("%u", &LIST[j][0]);
            LIST[j][1] = (((unsigned long long)LIST[j-1][0] * (unsigned long long)LIST[j-1][1]) % 1000000006);
            //printf("%u", ((unsigned long long)LIST[j-1][0] * (unsigned long long)LIST[j-1][1]) % 1000000006);
        }
        for(int j = n - 2; j >= 0; j--) {
            LIST[j][2] = (((unsigned long long)LIST[j+1][0] * (unsigned long long)LIST[j+1][2]) % 1000000006);
        }

        for(int j = 0; j < n; j++) {
            printf("%llu ", ((unsigned long long)LIST[j][1] * (unsigned long long)LIST[j][2]) % 1000000006);
        }
        printf("\n");
        
    }
}