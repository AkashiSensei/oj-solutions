/*
 * Process stack push, pop, and top queries, reporting empty-stack operations.
 * Finally sort and print all remaining values in ascending order.
 */

#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
int LIST[maxn];

int main() {
    int t,n, code, input;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        stack<int> s;
        while(n--) {
            scanf("%d", &code);
            switch(code ) {
                case 1:
                    scanf("%d", &input);
                    s.push(input);
                    break;
                case 2:
                    if(s.empty()) {
                        printf("empty\n");
                        break;;
                    }
                    s.pop();
                    break;
                case 3:
                    if(s.empty()) {
                        printf("empty\n");
                        break;;
                    }
                    printf("%d\n", s.top());
                    break;
            }
        }
        int cnt = 0;
        while(!s.empty()) {
            LIST[cnt++] = s.top();
            s.pop();
        }
        sort(LIST, LIST + cnt);
        for(int i = 0; i < cnt; i++) {
            printf("%d ", LIST[i]);
        }
        printf("\n");
    }
}