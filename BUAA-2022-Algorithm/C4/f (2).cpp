/*
 * Shortest-path attempt for an undirected weighted graph, using an adjacency
 * matrix and a Dijkstra-style priority queue to query a source-to-target distance.
 */

#include <iostream>
#include <string.h>
#include <queue>
using namespace std;


#define vertexNum 3000
#define MAX 9223372036854775807ll
typedef long long int ll;
ll adjMat[vertexNum][vertexNum];
int n, t;
typedef struct Vertex
{
    int id;
    ll dis;
    int pre;
} vertex, *Pvertex;
Pvertex V[vertexNum];
struct cmp
{
    bool operator()(Pvertex f1, Pvertex f2)
    {
        return f1->dis > f2->dis;
    }
};

void Dijkstra(int src)
{
    for (int i = 1; i <= n; i++)
    {
        if (adjMat[src][i] < MAX)
        {
            V[i]->dis = adjMat[src][i];
        }
    }
    V[src]->dis = 0;

    priority_queue<Pvertex, vector<Pvertex>, cmp> q;
    for (int i = 1; i <= n; i++)
    {
        q.push(V[i]);
    }
    vector<Pvertex> s;
    while (!q.empty())
    {
        Pvertex u = q.top();
        q.pop();
        s.push_back(u);
        for (int i = 1; i <= n; i++)
        {
            if (adjMat[u->id][i] < MAX)
            {
                if (V[i]->dis == MAX || V[i]->dis > u->dis + adjMat[u->id][i])
                {
                    V[i]->dis = u->dis + adjMat[u->id][i];
                    V[i]->pre = u->id;
                }
            }
        }
    }
}

int main()
{
    int m, s;
    scanf("%d %d %d %d", &n, &m, &s, &t);
    for (int i = 1; i <= n; i++)
    {
        Pvertex tmp = new vertex;
        tmp->id = i;
        tmp->pre = -1;
        tmp->dis = MAX;
        V[i] = tmp;
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            adjMat[i][j] = MAX;
        }
    }
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        if (w < adjMat[u][v])
        {
            adjMat[u][v] = w;
            adjMat[v][u] = w;
        }
    }
    Dijkstra(s);
    printf("%lld", V[t]->dis);
    return 0;
}