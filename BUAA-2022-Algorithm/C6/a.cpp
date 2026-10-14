/*
 * Print all zero-based pattern-match positions in a text by repeatedly
 * running KMP and advancing one position past each match start.
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_SIZE 1000005

char S[MAX_SIZE];
char T[MAX_SIZE];
int NEXT[MAX_SIZE];

void get_next(char *t, int * next, int len){//数组传入时，由于自己表示的就是地址，所以既是形参也是实参
    int i = 0,j = -1;
    next[0] = -1;
    while(i < len){
        if(-1 == j || t[i] == t[j]){
            i++;
            j++;
            next[i] = j;
        } else {
            j = next[j];
        }
    }
    for(j = 1; j < len; j++){
        if(t[next[j]] == t[j]){
            next[j] = next[next[j]];
        }
    }
}
int KMP(char *s, char *t, int slen, int tlen){
    int i = 0,j = 0;    
    while(i < slen && j < tlen){
        if(-1 == j || s[i] == t[j]){
            i++;
            j++;
        } else {
            j = NEXT[j];
        }   
    }
    if(j == tlen)
        return i - tlen;
    else 
        return -1;
}

int main() {
    scanf("%s %s", S, T);
    int slen = strlen(S);
    int tlen = strlen(T);
    get_next(T, NEXT, tlen);
    int ans = 0, loc = 0;
    while(~(ans = KMP(S + loc, T, slen - loc, tlen))) {
        loc += ans + 1;
        printf("%d ", loc - 1);
    }
}