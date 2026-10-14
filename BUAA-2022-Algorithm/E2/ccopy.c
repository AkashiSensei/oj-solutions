/*
 * Backtracking variant that prints up to M subsets of size floor(N/2)
 * from 1 through N, rejecting requests larger than the combination count.
 */

#include<stdio.h>

unsigned long long RANK[12];
unsigned long long CNN2[12];
int LIST[11], COUNT;
int M, LENGTH, N;

void output(int n, int loc, int depth){
    if(depth < n){
       for(int i = loc; i < N; i++){
            LIST[i] = 1;
            output(n, i + 1, depth + 1);
            LIST[i] = 0;
            if(COUNT == M){
                return;
            }
        } 
    } else {
        printf("%d ",n);
        for(int i = 0; i < 10; i++){
            if(LIST[i] == 1){
                printf("%d ",i + 1);
            }
        }
        printf("\n");
        COUNT++;
    }
}
int main() {
    RANK[0] = 1;
    for(int i = 1; i < 11; i++) {
        RANK[i] = RANK[i - 1] * i;
    }

    int addLeft = 0, halfL = 0, halfR = 0;
    for(int i = 1; i < 11; i++, addLeft = !addLeft) {
        if(addLeft) halfL++;
        else halfR++;
        CNN2[i] = RANK[i] / RANK[halfL] / RANK[halfR];
        //printf("%llu\n", CNN2[i]);
    }

    unsigned long long t;
    scanf("%llu", &t);
    for(unsigned long long i = 0; i < t; i++) {
        scanf("%d %d", &N, &M);
        if(M > CNN2[N]) {
            printf("-1\n");
            continue;
        }else{
            if(N == 1) {
                printf("1 1\n");
                continue;
            }
            COUNT = 0;
            LENGTH = N / 2;
            output(N / 2, 0, 0);
        }
    }
}
