/*
 * Compare characters from opposite ends until the first mismatch,
 * print the matched prefix lengths, and then the full length when different.
 */

#include <bits/stdc++.h>
using namespace std;

char s[1000006];

int main() {
    int t;
    string str;
    cin >> t;
    while(t--) {
        cin >> s;
        bool flag = 0;
        int len = strlen(s);
        int i;
        for(i = 0; i < len; i++) {
            if(s[i] == s[len - i -1]) {
                printf("%d ", i + 1);
            }else {
                flag = 0;
                break;
            }

        }
        if(i != len) {
            printf("%d\n", len);
        }else printf("\n");
    }
    return 0;
}