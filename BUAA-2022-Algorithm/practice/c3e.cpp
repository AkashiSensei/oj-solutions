/*
 * Find a maximum-sum path from the top-left to the bottom-right of a grid,
 * moving only right or down, using dynamic programming.
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 1e3+5;

LL DP[maxn][maxn];

int main() {
    int g, m, n;
    cin >> g;
    while(g--) {
        cin >> n >> m;
        memset(DP, 0, sizeof(DP));
        for(int i = 1; i <= n; i ++) {
            for(int j = 1; j <= m;j++) {
                scanf("%lld", &DP[i][j]);
            }
        }

        for(int i = 2; i <= n; i++) {
            DP[i][1] = DP[i - 1][1] + DP[i][1];
        }
        for(int i = 2; i <= m; i++) {
            DP[1][i] = DP[1][i - 1] + DP[1][i];
        }
        for(int i = 2; i <= n; i++) {
            for(int j = 2; j <= m; j++) {
                DP[i][j] = max(DP[i - 1][j], DP[i][j - 1]) + DP[i][j];
            }
        }
        cout << DP[n][m] << endl;
    }
}