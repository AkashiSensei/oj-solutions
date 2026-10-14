/*
 * Compute the least common multiple of a sequence using successive gcd calls.
 * Print -1 when the computed value exceeds 1e9.
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;


LL LIST[1005];
int main() {
    int g, n;
    LL gcd, lcm;
    ios::sync_with_stdio(false);
    cin >> g;
    while(g--) {
        cin >> n;
        for(int i = 0; i < n; i++) {
            cin >> LIST[i];
        }
        gcd = lcm = LIST[0];
        for(int i = 1; i < n; i++) {
            gcd = __gcd(lcm, LIST[i]);
            lcm = lcm / gcd * LIST[i];
            if(lcm > 1e9) {
                break;
            }
        }
        if(lcm > 1e9) {
            printf("-1\n");
        }else {
            printf("%lld\n", lcm);
        }
    }
}