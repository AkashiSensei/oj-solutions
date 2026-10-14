/*
 * Find the length of the longest palindromic substring
 * by expanding around every odd-length and even-length center.
 */

#include<cstdio>
#include<string.h>
#include<stdio.h>
#include<iostream>
#include<algorithm>
using namespace std;

char STR[1000];

int change(char *str, int i, int j) {
	// (1)i == st, j == st;
	// (2) i == st, j == st + 1;
	int len = strlen(str);
	while(str[i] == str[j] && i >= 0 && j < len) {
		i --;
		j ++;
	}
	return j - i -1;
} 
int main()
{
    int len, t;
    scanf("%d", &t);
    while(t--) {
        scanf("%s", STR);
        len = strlen(STR);
        if(len == 0 ) {
            printf("0\n");
            return 0;
        }
        int maxLen = 1;
        for(int st = 0; st < len - 1; st ++) {
            int len1 = change(STR, st, st + 1);
            int len2 = change(STR, st, st);
            maxLen = max(maxLen, max(len1, len2));
        }
        
        printf("%d\n",maxLen);
    }
	
 } 
