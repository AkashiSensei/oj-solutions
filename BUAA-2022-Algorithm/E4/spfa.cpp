/*
 * Attempt to detect any negative cycle with SPFA by initially queuing all vertices;
 * otherwise print the computed shortest-distance labels from vertex 1.
 */

//给定一个可能有负环的有向带权图，首先判断其是否有负环，如果没有，给出最短路径
//使用spfa算法，这是bellman_ford算法的改进版
//仍使用链式前向星存储图

#include<stdio.h>
#include<iostream>
#include<queue>
#include<string.h>

#define MAX_VERTEX 2005
#define MAX_ARC 6005
//题目中给出的数值，用于表示正无穷
#define MAX_DIS 1000000000

using namespace std;

struct Arc {
    int toV;
    long long weight;
    int next_index;
}ARCS[MAX_ARC];
int ARC_CNT;

long long DIS[MAX_VERTEX];
//标记目前该节点是否在队中
bool IS_IN_QUEUE[MAX_VERTEX];

//标记目前到该节点的最短路径所经历的弧数量
int VIA_CNT[MAX_VERTEX];

//链式前向星所使用的列表
int A_HEAD[MAX_VERTEX];

//传入以链式前向星表示的图，图的顶点数以及源顶点
bool spfa(Arc *arcs, int *a_head, int n, int s);
void add_arc(int from, int to, long long weight);

int main() {
    int t, n = 0, m = 0;
    int u, v;
    long long w;
    cin >> t;
    for(int group = 0; group < t; group++) {
        cin >> n >> m;
        ARC_CNT = 0;
        //memset(ARCS, 0, (m + 1) * sizeof(ARCS[0]));
        memset(A_HEAD, 0, (n + 1) * sizeof(A_HEAD[0]));
        for(int arc_line = 0; arc_line < m; arc_line++) {
            scanf("%d%d%lld", &u, &v, &w);
            add_arc(u, v, w);
        }

        if(!spfa(ARCS, A_HEAD, n, 1)) {
            printf("boo how\n");
            continue;
        }

        for(int output_v = 1; output_v <= n; output_v++) {
            printf("%lld ", DIS[output_v]);
        }
        printf("\n");
    }
    return 0;
}

void add_arc(int from, int to, long long weight) {
    ARC_CNT++;
    ARCS[ARC_CNT].toV = to;
    ARCS[ARC_CNT].weight = weight;
    ARCS[ARC_CNT].next_index = A_HEAD[from];
    A_HEAD[from] = ARC_CNT;
}

bool spfa(Arc *arcs, int *a_head, int n, int s) {
    fill(DIS, DIS + n + 1, MAX_DIS);
    memset(VIA_CNT, 0, (n + 1) * sizeof(VIA_CNT[0]));
    memset(IS_IN_QUEUE, 0, (n + 1) * sizeof(IS_IN_QUEUE[0]));

    DIS[s] = 0;
    
    queue<int> q;
    q.push(s);
    IS_IN_QUEUE[s] = 1;

    //该for循环是本题最大的坑点，由于题目要求判断“是否存在负环”，而不是“是否有源顶点能够到达的负环”，故需要将所有顶点入队一次以判断负环
    //最严谨的做法是建立超级源点，以0权重通向所有顶点
    //一般的spfa算法不需要该for循环
    for(int i = 1; i <= n; i++) {
        q.push(i);
        IS_IN_QUEUE[i] = 1;
    }

    int vertex, to;
    long long w;
    while(!q.empty()) {
        vertex = q.front();
        q.pop();
        IS_IN_QUEUE[vertex] = 0;

        for(int arc_ind = a_head[vertex]; arc_ind; arc_ind = arcs[arc_ind].next_index) {
            to = arcs[arc_ind].toV;
            w = arcs[arc_ind].weight;
            
            if(DIS[vertex] + w < DIS[to]) {
                DIS[to] = DIS[vertex] + w;
                VIA_CNT[to] = VIA_CNT[vertex] + 1;

                //当到达该顶点的最短路径包含的弧数达到n时，说明有负环
                if(VIA_CNT[to] >= n) {
                    return false;
                }

                //只有点该顶点的DIS在本轮被更新，才将该顶点入队，考虑松弛以它为始点的边，当然，如果顶点已经在队列中，则不再重复加入
                if(!IS_IN_QUEUE[to]) {
                    q.push(to);
                    IS_IN_QUEUE[to] = 1;
                }
            }
        }
    }
    return true;
}