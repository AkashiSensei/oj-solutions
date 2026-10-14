/*
 * SPFA-based graph exercise: detect negative cycles and otherwise print
 * distances from vertex 1; all vertices are initially queued for cycle detection.
 */

#include <bits/stdc++.h>
#define inf 1000000000
using namespace std;
const int MAXN = 2010;
const int MAXM = 6010;
int n, m;

int en = -1, eh[MAXN];
struct edge
{
    int u, v, w, next;
    edge(int U = 0, int V = 0, int W = 0, int N = 0) : u(U), v(V), w(W), next(N) {}
};
edge e[MAXM];
inline void add_edge(int u, int v, int w)
{
    e[++en] = edge(u, v, w, eh[u]);
    eh[u] = en;
}

int dis[MAXN], cnt[MAXN];
bool vis[MAXN];

void spfa()
{
    fill(dis + 1, dis + n + 1, inf);
    memset(cnt, 0, sizeof(cnt));
    memset(vis, 0, sizeof(vis));
    queue<int> q;
    dis[1] = 0;
    vis[1] = 1;
    q.push(1);
    for (int i = 1; i <= n; i++)
    {
        q.push(i);
        vis[i] = true;
    }
    int u, v, w;
    while (!q.empty())
    {
        u = q.front();
        vis[u] = 0;
        q.pop();
        for (int i = eh[u]; i != -1; i = e[i].next)
        {
            v = e[i].v;
            w = e[i].w;
            if (dis[u] + w < dis[v])
            {
                dis[v] = dis[u] + w;
                cnt[v] = cnt[u] + 1; //记录最短路径的边数
                if (cnt[v] >= n)     //最短路径边数>=n，即存在被重复遍历的点，也就是存在负环
                {
                    puts("boo how");
                    return;
                }
                if (!vis[v])
                {
                    vis[v] = 1;
                    q.push(v);
                }
            }
        }
    }
    for (int i = 1; i <= n; i++)
        printf("%d ", dis[i]);
    printf("\n");
}

int main()
{
    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; ++i)
    {
        scanf("%d%d", &n, &m);
        en = -1;
        memset(eh, -1, sizeof(eh));
        int u, v, w;
        for (int i = 1; i <= m; ++i)
        {
            scanf("%d%d%d", &u, &v, &w);
            add_edge(u, v, w);
        }
        spfa();
    }
    return 0;
}