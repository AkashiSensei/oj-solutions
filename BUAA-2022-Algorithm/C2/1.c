/*
 * Find the minimum Chebyshev distance between any two input points
 * by checking every pair: distance = max(abs(dx), abs(dy)).
 */

#include<stdio.h>
#include<math.h>
#define MAXSIZE 1005

int X_LIST[MAXSIZE], Y_LIST[MAXSIZE];

int main() {
    int t, n, min, dx, dy, dis;
    scanf("%d", &t);
    for(int i = 0; i < t; i++) {
        scanf("%d", &n);
        for(int j = 0; j < n; j++) {
            scanf("%d %d", &X_LIST[j], &Y_LIST[j]);
        }

        min = 1000000;
        for(int j = 0; j < n - 1; j++) {
            for(int k = j + 1; k < n; k++) {
                dx = (X_LIST[j] > X_LIST[k])? X_LIST[j] - X_LIST[k] : X_LIST[k] - X_LIST[j];
                dy = (Y_LIST[j] > Y_LIST[k])? Y_LIST[j] - Y_LIST[k] : Y_LIST[k] - Y_LIST[j];
                dis = (dy > dx)?dy : dx;
                min = (min > dis)? dis : min;
            }
        }
        printf("%d\n", min);
    }
}