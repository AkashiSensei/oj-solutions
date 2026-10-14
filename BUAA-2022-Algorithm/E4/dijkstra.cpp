/*
 * Use an adjacency list and heap-based Dijkstra to find a source-to-target
 * shortest distance in an undirected graph with nonnegative edge weights.
 */

//使用链式前向星保存图，允许环路，重边，但不允许负边
#include<stdio.h>
#include<iostream>
#include<queue>
#include<string.h>

#define MAX_VERTEX 1000005
#define MAX_EDGE 2000005

using namespace std;

//链式前向星所使用的边，数组下标为0处不存数据
struct Edge {
    //目标顶点
    int toV;
    //该顶点的下一个边
    int nextE;
    unsigned long long weight;
}EDGE[MAX_EDGE * 2];
int EDGE_CNT;

//优先队列中顶点集合
struct Vertex {
    int num;
    unsigned long long dis;
    bool operator<(const Vertex &pNext) const{
        return dis > pNext.dis;
    }
};
priority_queue<Vertex> Q;
//在dijkstra算法中，保存目前已经得到的，各个顶点到源点的最短距离
unsigned long long DIS[MAX_VERTEX];
int IS_VISIT[MAX_VERTEX];

//记录连接到对应顶点的边链表的头数组下标，如果值为0表示没有边
int HEAD[MAX_VERTEX];





//为链式前向星链表添加节点，在链表头添加
void addEdge(int, int, unsigned long long);

//给出使用链式前向星保存的边信息，顶点数目，以及源顶点
void dijkstra(Edge *edges, int * head, int n, int s);

int main() {
    int n, m, s, t, u, v;
    cin >> n >> m >> s >> t;

    unsigned long long w;
    for(int i = 0; i < m; i++) {
        scanf("%d%d%llu", &u, &v, &w);
        addEdge(u, v, w);
        addEdge(v, u, w);
    }

    dijkstra(EDGE, HEAD, n, s);

    printf("%llu", DIS[t]);
    return 0;
}

void addEdge(int start, int to, unsigned long long weight) {
    //初始值为0，先增加，下标为0处空着
    EDGE_CNT++;
    EDGE[EDGE_CNT].toV = to;
    EDGE[EDGE_CNT].weight = weight;
    EDGE[EDGE_CNT].nextE = HEAD[start];
    HEAD[start] = EDGE_CNT;
}

void dijkstra(Edge *edges, int * head, int n, int s) {
    Vertex temp;
    int t_num, end_v;

    memset(DIS, -1, (n + 1) * sizeof(unsigned long long));

    DIS[s] = 0;
    Q.push((Vertex){s, 0});

    while(!Q.empty()) {
        temp = Q.top();
        Q.pop();

        //由于每达到一个顶点，就会对以它为始点的边进行松弛，松弛成功就会把后续点加入队列，因此可能会重复添加
        if(IS_VISIT[temp.num]) {
            continue;
        }
        IS_VISIT[temp.num] = 1;

        t_num = temp.num;

        for(int e_now = head[t_num]; e_now; e_now = edges[e_now].nextE) {
            end_v = edges[e_now].toV;
            if(DIS[end_v] > DIS[t_num] + edges[e_now].weight) {
                DIS[end_v] = DIS[t_num] + edges[e_now].weight;
                if(!IS_VISIT[end_v]) {
                    Q.push((Vertex){end_v, DIS[end_v]});
                }
            }
        }
    }
}