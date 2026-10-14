/*
 * Enumerate up to M subsets of size floor(N/2) from the integers 1 through N.
 * Print -1 if the requested number exceeds the available combinations.
 */

#include<stdio.h>

unsigned long long RANK[12];
unsigned long long CNN2[12];
int LIST[6], COUNT;
int M, LENGTH, N;

int output(int, int);

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
            output(N / 2, 1);
        }
    }
} 
int output(int last, int start) {
    if(last == 1) {
        for(int i = start; i <= N && COUNT < M; i++) {
            printf("%d ", LENGTH);
            LIST[LENGTH - 1] = i;
            for(int j = 0; j < LENGTH; j++) {
                printf("%d ", LIST[j]);
            }
            printf("\n");
            COUNT++;
        }
    }
    else {
        for(int i = start; i <= N - last; i++) {
            LIST[LENGTH - last] = i;
            output(last - 1, i + 1);
        }
    }
}