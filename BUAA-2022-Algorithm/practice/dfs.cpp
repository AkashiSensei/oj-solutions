/*
 * Depth-first graph-traversal scaffold using adjacency arrays and recursion.
 * Visit every component; main and the per-vertex processing are left empty.
 */

#include <bits/stdc++.h>
#define maxn 100000
#define maxm 200000

using namespace std;

int h[maxn], e[maxm], ne[maxm], cnt;
long long w[maxm];


bool is_visit[maxn];
void dfs_visit(int v) {
    is_visit[v] = 1;
    // 此处添加访问逻辑
    for(int edge_inx = h[v]; ~edge_inx; edge_inx = ne[edge_inx]) {
        if(!is_visit[e[edge_inx]]) {
            dfs_visit(e[edge_inx]);
        }
    }
    // 访问退出时间戳
}

void dfs(int n) {
    memset(is_visit, 0, sizeof(bool) * (n + 2));
    for(int i = 1; i <= n; i++) {
        if(!is_visit[i]) {
            dfs_visit(i);
        }
    }
}

int main() {
    
}