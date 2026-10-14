/*
 * Activity-selection attempt: sort intervals by finishing time and greedily
 * count how many non-overlapping activities can be selected.
 */

#include<stdio.h>
#include<stdlib.h>


int LIST[15][2];

int cmp(const void *p1, const void *p2) {
    return (*((int **)p1))[1] - (*((int **)p2))[1];
}

int main() {
    int n, result = 0, last_end = 0;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d %d", &LIST[i][0], &LIST[i][1]);
    }
    qsort(LIST, n, sizeof(LIST[0]), cmp);

    for(int i = 0; i < n; i++) {
        if(last_end <= LIST[i][0]) {
            last_end = LIST[i][1];
            result++;
        }
    }
    printf("%d", result);
}