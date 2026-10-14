/*
 * Graph-traversal practice scaffold using adjacency arrays and a queue.
 * The visit helper also recurses; main does not read or traverse a graph yet.
 */

#include <bits/stdc++.h>
#define maxn 100000
#define maxm 200000

using namespace std;

int h[maxn], e[maxm], ne[maxm], cnt;
long long w[maxm];

bool is_visit[maxn];
void bfs_visit(int v) {
    is_visit[v] = 1;
    queue<int> q;
    q.push(v);
    while (!q.empty()) {
        v = q.front();
        q.pop();
        for(int edge_inx = h[v]; ~edge_inx; edge_inx = ne[edge_inx]) {
            if(!is_visit[e[edge_inx]]) {
                // 访问逻辑
                bfs_visit(e[edge_inx]);
                q.push(e[edge_inx]);
            }
        }
    }
}

void bfs(int n) {
    memset(is_visit, 0, sizeof(bool) * (n + 2));
    for(int i = 1; i <= n; i++) {
        if(!is_visit[i]) {
            bfs_visit(i);
        }
    }
}

int main() {
    return 0;
}