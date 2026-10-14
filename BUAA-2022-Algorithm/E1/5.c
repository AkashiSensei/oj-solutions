/*
 * Incomplete binomial-coefficient calculation with a 1e9 output limit.
 * The factorial-based case is implemented; the large-n branch is unfinished.
 */

#include<stdio.h>
#define DELTA 1e-5

#define MAX_RANK 20

double RANK[MAX_RANK + 1];

int main() {
    RANK[1] = 1;
    for(int i = 2; i < MAX_RANK + 1; i++) {
        RANK[i] = RANK[i - 1] * i;
    }
    int n, m, t;
    double ans;
    

    scanf("%d", &t);
    for(int group = 0; group < t; group++) {
        scanf("%d %d", &n, &m);
        m = (m < n - m)? m : n - m;
        if(m == 0) {
            printf("1\n");
            continue;
        }
        if(m > 16) {
            printf("-1\n");
            continue;
        }
        if(n <= 20) {
            ans = RANK[n] / RANK[m] / RANK[n-m];
            if(ans > 1e9) {
                printf("-1\n");
                continue;
            }
            printf("%d\n", (int)(ans + DELTA));
            continue;
        }
        if(m <= 20) {
            
        }
    }
}