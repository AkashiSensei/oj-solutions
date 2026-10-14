/*
 * Add two sparse polynomials whose terms are ordered by exponent.
 * Merge equal exponents, discard zero sums, and print coefficients and exponents.
 */

#include<stdio.h>

#define MAX_LENGTH 100005

int A_LIST[MAX_LENGTH][2], B_LIST[MAX_LENGTH][2], C_LIST[MAX_LENGTH][2];

int main() {
    int n, m, group, aIndex, bIndex, cIndex;
    scanf("%d", &group);

    for(int i = 0; i < group; i++) {

        scanf("%d", &n);
        for(aIndex = 0; aIndex < n; aIndex++) {
            scanf("%d", &A_LIST[aIndex][0]);
        }

        for(aIndex = 0; aIndex < n; aIndex++) {
            scanf("%d", &A_LIST[aIndex][1]);
        }
        
        scanf("%d", &m);
        for(bIndex = 0; bIndex < m; bIndex++) {
            scanf("%d", &B_LIST[bIndex][0]);
        }

        for(bIndex = 0; bIndex < m; bIndex++) {
            scanf("%d", &B_LIST[bIndex][1]);
        }



        aIndex = 0;
        bIndex = 0;
        cIndex = 0;
        while (aIndex < n && bIndex < m) {
            if(A_LIST[aIndex][1] == B_LIST[bIndex][1]) {
                if(A_LIST[aIndex][0] + B_LIST[bIndex][0] == 0) {
                    aIndex++;
                    bIndex++;
                    continue;
                }
                C_LIST[cIndex][1] = A_LIST[aIndex][1];
                C_LIST[cIndex][0] = A_LIST[aIndex][0] + B_LIST[bIndex][0];
                cIndex++;
                aIndex++;
                bIndex++;
            } else if (A_LIST[aIndex][1] < B_LIST[bIndex][1]) {
                C_LIST[cIndex][1] = A_LIST[aIndex][1];
                C_LIST[cIndex][0] = A_LIST[aIndex][0];
                aIndex++;
                cIndex++;
            } else {
                C_LIST[cIndex][1] = B_LIST[bIndex][1];
                C_LIST[cIndex][0] = B_LIST[bIndex][0];
                bIndex++;
                cIndex++;
            }
        }
        if(aIndex < n) {
            for (; aIndex < n; aIndex++, cIndex++) {
                C_LIST[cIndex][1] = A_LIST[aIndex][1];
                C_LIST[cIndex][0] = A_LIST[aIndex][0];
            }
        }else if(bIndex < m) {
            for (; bIndex < m; bIndex++, cIndex++) {
                C_LIST[cIndex][1] = B_LIST[bIndex][1];
                C_LIST[cIndex][0] = B_LIST[bIndex][0];
            }
        }
        printf("%d\n", cIndex);
        for(int j = 0; j < cIndex; j++) {
            printf("%d ", C_LIST[j][0]);
        }
        printf("\n");
        for(int j = 0; j < cIndex; j++) {
            printf("%d ", C_LIST[j][1]);
        }
        printf("\n");
    }
}