/*
 * String-processing draft: inspect the trailing run of the first character,
 * print the corresponding lengths, and also print the full length when different.
 */

#include<string>
#include<iostream>
#include<stdio.h>

using namespace std;

void judge_and_output(string str) {
    int n = str.length();
    int i = 0, j;
    while (str[0] == str[n - i - 1])i++;
    for(j = 0; j < i; j++) {
        printf("%d ", j + 1);
    }
    if(i != n) {
        printf("%d\n", n);
    }else printf("\n");
}

int main() {
    int t;
    string str;
    cin >> t;
    while(t--) {
        cin >> str;
        judge_and_output(str);
    }
    return 0;
}