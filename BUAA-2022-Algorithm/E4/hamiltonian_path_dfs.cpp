/*
 * Check whether a directed acyclic graph has a Hamiltonian path.
 * Build a topological order with DFS and test edges between consecutive vertices.
 */

//判断没有环路没有重边（本算法使用dfs方法允许有重边）的有向图是否存在哈密顿路径
//使用链式前向星保存图
//有机会可以补充一下使用其他方法找寻拓扑排序的算法

#include<stdio.h>
#include<string.h>
#include<string.h>
#include<queue>
#include<algorithm>

#define MAX_VERTEX 100005
#define MAX_ARC 200005

using namespace std;

//链式前向星保存边信息，但没有权重了
struct Arc {
    int toV;
    int next_index;
}ARCS[MAX_ARC];
int ARC_CNT;

//由于递归调用dfs_visit，为了节省栈空间，尽量少传参数
int N;

bool IS_VISIT[MAX_VERTEX];
int A_HEAD[MAX_VERTEX];

//倒序的拓扑排序序列
int TOPOLOGICAL_LIST[MAX_VERTEX];
int TP_CNT;

//使用dfs方法求出拓扑排序，并判断是否有哈密顿路径
bool topological_sort_dfs();

inline void add_arc(int from, int to);

void dfs_visit(int v);

//判断两顶点之间是否有弧
bool has_arc(int from, int to);

int main() {
    int t, u, v, m = -1;
    scanf("%d", &t);
    for(int group = 0; group < t; group++) {
        scanf("%d%d", &N, &m);

        ARC_CNT = 0;
        memset(A_HEAD, 0, (N + 1) * sizeof(A_HEAD[0]));

        for(int arc_line = 0; arc_line < m; arc_line++) {
            scanf("%d%d", &u, &v);
            add_arc(u, v);
        }

        if(topological_sort_dfs()) {
            printf("yy\n");
        }else {
            printf("nn\n");
        }
    }
}

inline void add_arc(int from, int to) {
    ARC_CNT++;
    ARCS[ARC_CNT].toV = to;
    ARCS[ARC_CNT].next_index = A_HEAD[from];
    A_HEAD[from] = ARC_CNT;
}

bool topological_sort_dfs() {
    memset(IS_VISIT, 0, (N + 1) * sizeof(IS_VISIT[0]));
    TP_CNT = 0;

    for(int i = 1; i <= N; i++) {
        dfs_visit(i);
    }

    for(TP_CNT--; TP_CNT; TP_CNT--) {
        if(!has_arc(TOPOLOGICAL_LIST[TP_CNT], TOPOLOGICAL_LIST[TP_CNT - 1])) {
            return 0;
        }
    }
    return 1;
}

void dfs_visit(int v) {
    if(IS_VISIT[v]) {
        return;
    }
    IS_VISIT[v] = 1;
    for(int arc_now = A_HEAD[v]; arc_now; arc_now = ARCS[arc_now].next_index) {
        dfs_visit(ARCS[arc_now].toV);
    }
    TOPOLOGICAL_LIST[TP_CNT++] = v;
}

bool has_arc(int from, int to) {
    for(int arc_now = A_HEAD[from]; arc_now; arc_now = ARCS[arc_now].next_index) {
        if(ARCS[arc_now].toV == to) {
            return 1;
        }
    }
    return 0;
}