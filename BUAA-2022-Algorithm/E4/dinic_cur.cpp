/*
 * Alternative Dinic implementation for directed-network maximum flow.
 * This version traverses adjacency lists directly; current-arc setup is commented out.
 */

//这个版本是尝试模仿原板子，加了cur数组，但正如预期，运行时间并没有缩短，不知道这样做的意义何在
#include<stdio.h>
#include<queue>
#include<string.h>

#define MAX_VERTEX 105
#define MAX_ARC 5005
#define MAX_VALUE __LONG_LONG_MAX__

using namespace std;

struct Arc {
    int toV;
    long long rest;
    int next;
}ARCS[MAX_ARC * 2];
int ARC_CNT, N;

int A_HEAD[MAX_VERTEX];
int DEPTH[MAX_VERTEX];




void add_arc(int from, int to, long long rest);

long long dinic(int s, int t);

bool bfs(int s, int t);

long long dfs(int s, int t, long long flow);

int main() {
    int t, m, u, v, s, target;
    long long cap;
    scanf("%d", &t);

    for(int group = 0; group < t; group++) {
        scanf("%d%d%d%d", &N, &m, &s, &target);
        ARC_CNT = 0;
        memset(A_HEAD, -1, sizeof(A_HEAD));

        for(int arc_line = 0; arc_line < m; arc_line++) {
            scanf("%d%d%lld", &u, &v, &cap);
            add_arc(u, v, cap);
            add_arc(v, u, 0);
        }

        printf("%lld\n", dinic(s, target));
    }
}




void add_arc(int from, int to, long long rest) {
    ARCS[ARC_CNT].toV = to;
    ARCS[ARC_CNT].rest = rest;
    ARCS[ARC_CNT].next = A_HEAD[from];
    A_HEAD[from] = ARC_CNT;
    ARC_CNT++;
}

long long dinic(int s, int t) {
    long long result = 0;
    while(bfs(s, t)) {
        result += dfs(s, t, MAX_VALUE);
    }
    return result;
}

bool bfs(int s, int t) {
    memset(DEPTH, 0, sizeof(DEPTH));
    queue<int> q;
    int from, to;

    DEPTH[s] = 1;
    q.push(s);
    //CUR[s] = A_HEAD[s];

    while(!q.empty()) {
        from = q.front();
        q.pop();

        for(int arc_now = A_HEAD[from]; ~arc_now; arc_now = ARCS[arc_now].next) {
            to = ARCS[arc_now].toV;
            if(ARCS[arc_now].rest && !DEPTH[to]) {
                DEPTH[to] = DEPTH[from] + 1;
                //CUR[to] = A_HEAD[to];
                if(to == t) {
                    return 1;
                }
                q.push(to);
            }
        }
    }
    return false;
}

long long dfs(int from, int t, long long flow) {
    if(from == t || !flow) {
        return flow;
    }
    long long rest = flow, acceptable;
    int to;

    for(int arc_now = A_HEAD[from]; ~arc_now && rest; arc_now = ARCS[arc_now].next){
        to = ARCS[arc_now].toV;
        if(ARCS[arc_now].rest && DEPTH[to] == DEPTH[from] + 1) {
            acceptable = dfs(to, t, min(rest, ARCS[arc_now].rest));
            if(!acceptable) {
                DEPTH[to] = 0;
            }
            rest -= acceptable;
            ARCS[arc_now].rest -= acceptable;
            ARCS[arc_now ^ 1].rest += acceptable;
        }
    }
    return flow - rest;
}