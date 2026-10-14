/*
 * Find the shortest distance between a specified source and target
 * in an undirected weighted graph using heap-based Dijkstra.
 */

#include <bits/stdc++.h>

const int MaxN = 1000010, MaxM = 5000000;
typedef long long ll;
struct edge
{
    int to, next;
    ll dis;
};

edge e[MaxM];
int head[MaxN], cnt;
ll dis[MaxN];
bool vis[MaxN];
int n, m, s, t;

inline void add_edge(int u, int v, ll d)
{
    cnt++;
    e[cnt].dis = d;
    e[cnt].to = v;
    e[cnt].next = head[u];
    head[u] = cnt;
}

struct node
{
    ll dis;
    int pos;
    bool operator<(const node &x) const
    {
        return x.dis < dis;
    }
};

std::priority_queue<node> q;

inline void dijkstra()
{
    dis[s] = 0;
    q.push((node){0, s});
    while (!q.empty())
    {
        node tmp = q.top();
        q.pop();
        int x = tmp.pos;
        ll d = tmp.dis;
        if (vis[x])
            continue;
        vis[x] = 1;
        for (int i = head[x]; i; i = e[i].next)
        {
            int y = e[i].to;
            if (dis[y] > dis[x] + e[i].dis)
            {
                dis[y] = dis[x] + e[i].dis;
                if (!vis[y])
                {
                    q.push((node){dis[y], y});
                }
            }
        }
    }
}

int main()
{
    scanf("%d%d%d%d", &n, &m, &s, &t);
    for (int i = 1; i <= n; ++i)
        dis[i] = LONG_LONG_MAX;
    for (register int i = 0; i < m; ++i)
    {
        register int u, v;
        ll d;
        scanf("%d%d%lld", &u, &v, &d);
        add_edge(u, v, d);
        add_edge(v, u, d);
    }
    dijkstra();
    printf("%lld ", dis[t]);
    return 0;
}
