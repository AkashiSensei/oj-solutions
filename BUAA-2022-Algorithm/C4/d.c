/*
 * Solve fractional knapsack by taking items in decreasing value-to-weight ratio,
 * allowing a fraction of the final item when capacity runs out.
 */

#include<stdio.h>
#include<stdlib.h>

struct item
{
    int value, weight;
    double rate;
} LIST[100005];

int cmp(const void *p1, const void *p2) {
    if (((struct item *)p2)->rate - ((struct item *)p1)->rate > 0) {
        return 1;
    }else if(((struct item *)p2)->rate - ((struct item *)p1)->rate < 0){
        return -1;
    }
    else{
        return 0;
    }
}

int main() {
    int n, i;
    double package, value = 0;
    scanf("%d %lf", &n, &package);
    for(int i = 0; i < n; i++) {
        scanf("%d %d", &LIST[i].value, &LIST[i].weight);
        LIST[i].rate = (double)LIST[i].value / LIST[i].weight;
    }

    qsort(LIST, n, sizeof(LIST[0]), cmp);

    for(i = 0; i < n; i++) {
        if(package >= LIST[i].weight) {
            package -= LIST[i].weight;
            value += LIST[i].value;
        }
        else{
            value += (package / LIST[i].weight) * LIST[i].value;
            break;
        }
    }

    printf("%.3lf", value);
    return 0;
}