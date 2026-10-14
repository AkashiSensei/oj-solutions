/*
 * Given N names and N-1 matching entries, find and print the unmatched name.
 * Mark individual occurrences so repeated names can be matched separately.
 */

#include <bits/stdc++.h>
using namespace std;

char NAME[10004][26];
char IS_MATCH[10004];

int main() {
    int n;
    cin >> n;
    fgets(NAME[0], 26, stdin);
    for(int i = 0; i < n; i++) {
        fgets(NAME[i], 26, stdin);
    }
    char input[26];
    for(int i = 0; i < n - 1; i++) {
        fgets(input, 26, stdin);
        for(int j = 0; j < n; j++) {
            if(IS_MATCH[j] == 0 && strcmp(NAME[j], input) == 0) {
                IS_MATCH[j] = 1;
                break;
            }
        }
    }
    for(int i = 0 ; i < n; i++) {
        if(IS_MATCH[i] == 0) {
            puts(NAME[i]);
            return 0;
        }
    }
}