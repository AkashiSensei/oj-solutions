/*
 * Sort intervals by finishing time and greedily select non-overlapping
 * activities to maximize the number selected.
 */

#include<stdio.h>
#include<stdlib.h>


struct act{
    int start,end;
}LIST[1000005];

int cmp(const void *p1, const void *p2) {
    return ((struct act*)p1)->end - ((struct act*)p2)->end;
}

int main() {
    int n, result = 0, last_end = 0;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d %d", &LIST[i].start, &LIST[i].end);
    }
    qsort(LIST, n, sizeof(LIST[0]), cmp);

    for(int i = 0; i < n; i++) {
        if(last_end <= LIST[i].start) {
            last_end = LIST[i].end;
            result++;
        }
    }
    printf("%d", result);
    return 0;
}