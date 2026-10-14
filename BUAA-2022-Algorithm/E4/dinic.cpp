/*
 * Compute maximum flow in a directed capacity network with Dinic,
 * using residual edges, BFS levels, and current-arc optimization.
 */

//使用链式前向星存储图，使用dinic算法计算最大流，加以多路增广和当前弧优化
#include<stdio.h>
#include<queue>
#include<string.h>

#define MAX_VERTEX 105
#define MAX_ARC 5005
#define MAX_VALUE __LONG_LONG_MAX__

using namespace std;

//链式前向星的弧结构体，直接保存残量网络，在读入边时即创建初始的残量网络，保存当前弧上的残余流量
//第一条弧的下标必须是0，这样就不需要保存反向弧下标
struct Arc {
    int toV;
    long long rest;
    int next;
}ARCS[MAX_ARC * 2];
int ARC_CNT, N;

//链式前向星中记录顶点的弧链表的下标
int A_HEAD[MAX_VERTEX];
int CUR[MAX_VERTEX];

//该数组用于保存bfs给出的节点分层，层间的弧以及比目标点还深的顶点将会被忽略
int DEPTH[MAX_VERTEX];



//添加一条单向弧，在本算法实现中必须两条反向的弧一起添加
void add_arc(int from, int to, long long rest);

//输入源顶点以及目标顶点，使用优化dinic算法计算最大流并返回
long long dinic(int s, int t);

//记源顶点为第一层，将各顶点分层，将在到达目标顶点时停止，返回真
//如果残量网络中不存在源顶点到目标顶点的增广路，则返回假
bool bfs(int s, int t);

//给出期望加载给s的入流量，返回在目标点为t的情况下，s最大能接受的流量
//不同于以往的dfs，该dfs在到达某顶点之后，并不会简单将其标记为“以访问”，而是当起不能再接受流量之后再不再访问，即“多路增广”
//当发现本次分层后，某顶点不能再接受更多流量，即不再询问它能接受多少流量，即“当前弧优化”
long long dfs(int s, int t, long long flow);

int main() {
    int t, m, u, v, s, target;
    long long cap;
    scanf("%d", &t);

    for(int group = 0; group < t; group++) {
        scanf("%d%d%d%d", &N, &m, &s, &target);
        ARC_CNT = 0;
        //由于ARCS第一条弧下标为0，故初始值置为-1，表示没有后续弧
        memset(A_HEAD, -1, sizeof(A_HEAD));

        for(int arc_line = 0; arc_line < m; arc_line++) {
            scanf("%d%d%lld", &u, &v, &cap);
            //必须同时添加原弧以及反向弧，使得可以直接通过将边下标抑或1获取反向边
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
    CUR[s] = A_HEAD[s];

    while(!q.empty()) {
        from = q.front();
        q.pop();

        for(int arc_now = A_HEAD[from]; ~arc_now; arc_now = ARCS[arc_now].next) {
            to = ARCS[arc_now].toV;
            if(ARCS[arc_now].rest && !DEPTH[to]) {
                DEPTH[to] = DEPTH[from] + 1;
                CUR[to] = A_HEAD[to];
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

    for(int arc_now = CUR[from]; ~arc_now && rest; arc_now = ARCS[arc_now].next){
        to = ARCS[arc_now].toV;
        // 这个地方是关键优化，搜索到当前弧表示之前的都没了
        CUR[from] = arc_now;
        if(ARCS[arc_now].rest && DEPTH[to] == DEPTH[from] + 1) {
            acceptable = dfs(to, t, min(rest, ARCS[arc_now].rest));
            if(!acceptable) {
                DEPTH[to] = 0;
            }
            rest -= acceptable;
            ARCS[arc_now].rest -= acceptable;
            //反向弧
            ARCS[arc_now ^ 1].rest += acceptable;
        }
    }
    //rest为剩下的流量，flow - rest即为能够接受的流量
    return flow - rest;
}