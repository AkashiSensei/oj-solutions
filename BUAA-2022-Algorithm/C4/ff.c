/*
 * Incomplete adjacency-matrix Dijkstra draft for single-source shortest paths.
 */

#include<stdio.h>

#define MAXSIZE 105
#define DATATYPE int

char IS_FOUND[MAXSIZE];
int WEIGHT[MAXSIZE][MAXSIZE];
int SWEIGHT[MAXSIZE], SPATH[MAXSIZE];
int COUNT;

void dijkstra(int v0) {
    int i, j ,minWeight;
    for(i = 0; i < COUNT - 1; i++) {
        minWeight = 2000000000;
        for(j = 0; i < COUNT; i++) {
            if(!IS_FOUND[j] && (SWEIGHT[j] < minWeight)) {
                v = j;
                minWeight = SWEIGHT[v];
            }
        }
        IS_FOUND[v] = 1;
        for(j = 0; j < COUNT; j++) {
            if(!IS_FOUND[j] && (minWeight + WEIGHT[v][j] < SWEIGHT[j])) {
                SWEIGHT[j] = 
            }
        }
    }
}