/*
 * Compute a triangle's area from three integer-coordinate points
 * using a cross product, and print the result with a .0 or .5 suffix.
 */

#include<stdio.h>

int main() {
    long long x0, x1, x2, y0, y1, y2;
    int t;
    scanf("%d", &t);
    while(t--) {
        scanf("%lld%lld%lld%lld%lld%lld", &x0, &y0, &x1, &y1, &x2, &y2);
        long long result = (x1 - x0) * (y2 - y0) - (x2 - x0) * (y1 - y0);
        if(result < 0) {
            result = -result;
        }

        long long iint = result >> 1;
        if(result % 2) {
            printf("%lld.5\n", iint);
        }else {
            printf("%lld.0\n", iint);
        }
    }
}