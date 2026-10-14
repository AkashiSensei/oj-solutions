/*
 * Use dynamic programming to find a maximum-sum selection of array elements
 * subject to never selecting two adjacent positions.
 */

#include<stdio.h>
#include<string.h>

int NUM[1000005];
long long MAX[1000005];

int main() {
    int t, n;
    scanf("%d", &t);

    long long temp;
    for(int i = 0; i < t; i++) {
        scanf("%d", &n);
        for(int j = 1; j <= n; j++) {
            scanf("%d", &NUM[j]);
        }

        MAX[0] = 0;
        MAX[1] = NUM[1];

        for(int k = 2; k <= n; k++) {
            temp = MAX[k - 2] + NUM[k];

            if(temp > MAX[k - 1]) {
                MAX[k] = temp;
            }else if(MAX[k - 2] > MAX[k - 1]) {
                MAX[k] = MAX[k - 2];
            }else {
                MAX[k] = MAX[k - 1];
            }
        }

        printf("%lld\n", MAX[n]);
    }
}