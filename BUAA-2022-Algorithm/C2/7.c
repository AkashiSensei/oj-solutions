/*
 * Incomplete grid-processing draft: read text rows into a map.
 * The cell-processing loop and the original problem logic are unfinished.
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char MAP[205][205];
int LIST[50000];

int main() {
    int t, count;
    scanf("%d", &t);
    for(int i = 1; i <= t; i++) {
        count = 0;
        memset(MAP, 0, sizeof(MAP));
        gets(MAP[i]);
        for(int j = 1; j <= n; j++) {
            for(int k = 1; k <= n; k++) {
                if(MAP[j][k] == 0) {
                    
                }
            }
        }
    }
}