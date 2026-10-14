/*
 * Read k*n integers, sort them in ascending order, and print the result.
 */

#include<stdio.h>
#include<stdlib.h>

int LIST[100005];

int cmp(const void *, const void *);

int main() {
    int t, k, n, count;
    scanf("%d", &t);
    for(int group = 0; group < t; group++) {
        scanf("%d %d", &k, &n);
        count = k * n;
        for(int index = 0; index < count; index++) {
            scanf("%d", &LIST[index]);
        }
        qsort(LIST, count, sizeof(int), cmp);
        for(int index = 0; index < count; index++) {
            printf("%d ", LIST[index]);
        }
        printf("\n");
    }
}

int cmp(const void *p1, const void *p2) {
    return *(int *)p1 - *(int *)p2;
}