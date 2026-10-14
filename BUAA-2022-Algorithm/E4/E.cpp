/*
 * Check for a Hamiltonian path in a directed acyclic graph by topologically
 * sorting it and testing for an edge between each consecutive pair.
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 100005, M = 300000;
int head[N], to[M], ne[M], cnt = 0;
int n, m, t;
int inn[N];

int hasPath(int x, int y)
{
    for (int i = head[x]; i; i = ne[i])
    {
        if (to[i] == y)
            return 1;
    }
    return 0;
}

int top_sort()
{
    int q[N], hh = 0, tt = 0;
    int ans[N], c = 0;
    for (int i = 1; i <= n; i++)
        if (inn[i] == 0)
        {
            q[tt++] = i;
            ans[c++] = i;
        }
    while (hh < tt)
    {
        int ss = q[hh++];
        for (int i = head[ss]; i; i = ne[i])
        {
            int j = to[i];
            inn[j]--;
            if (!inn[j])
            {
                q[tt++] = j;
                ans[c++] = j;
            }
        }
    }

    for (int i = 0; i < n - 1; i++)
    {
        if (!hasPath(ans[i], ans[i + 1]))
            return 0;
    }
    return 1;
}

void add(int a, int b)
{
    cnt++;
    to[cnt] = b;
    ne[cnt] = head[a];
    head[a] = cnt;
}

int main()
{
    cin >> t;

    while (t--)
    {
        memset(inn, 0, sizeof inn);
        memset(head, 0, sizeof(head));
        cnt = 0;
        scanf("%d%d", &n, &m);
        for (int i = 0; i < m; i++)
        {
            int a, b;
            scanf("%d%d", &a, &b);
            inn[b]++;
            add(a, b);
        }
        if (top_sort())
            puts("yy");
        else
            puts("nn");
    }

    return 0;
}
