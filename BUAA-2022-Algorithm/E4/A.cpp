/*
 * Compute all-pairs shortest distances in a directed weighted graph
 * with Floyd-Warshall, then answer distance queries or report no route.
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll d[1000][1000]; // d[u][v]表示边e=(u,v)的权值(不存在时设为INF,不过d[i][i]=0)
int n, m, q;      //顶点数
void warshall_floyd()
{
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (d[i][k] != LONG_LONG_MAX && d[k][j] != LONG_LONG_MAX)
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}

int main()
{
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i != j)
                d[i][j] = LONG_LONG_MAX;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        ll w;
        scanf("%d%d%lld", &u, &v, &w);
        if (w < d[u][v])
            d[u][v] = w;
    }
    warshall_floyd();
    for (int i = 0; i < q; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        if (d[x][y] != LONG_LONG_MAX)
            printf("%lld\n", d[x][y]);
        else
            puts("No So1ution");
    }
    return 0;
}