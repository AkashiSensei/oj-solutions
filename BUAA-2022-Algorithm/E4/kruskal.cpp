/*
 * Find a minimum spanning tree's total weight using Kruskal's algorithm:
 * sort edges by weight and use disjoint sets to avoid cycles.
 */

//使用边列表保存图，使用数组模拟并查集，允许重边的自环
#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<algorithm>

#define MAX_VERTEX 200005
#define MAX_EDGE 500005

using namespace std;

struct Edge {
    int u, v;
    long long w;
}EDGE[MAX_EDGE];

//实现类似并查集的功能
//初始时每个元素值均为其下标，表示自己即为各自集合的根
//如果一个元素的值与其下标不同，即表示该元素被合并到其他集合中了
//但不一定被连接到其他集合的根，需要通过遍历，寻找被链接集合的根
int FIND_A[MAX_VERTEX];

//用于C++sort()的排序函数，返回true时表示元素顺序符合要求
bool edge_cmp(Edge left, Edge right);
//输入已经排序好的边列表，以及图的节点个数，元素个数
//能够处理掉重边和自环
long long kruskal(Edge *, int, int);
//寻找输入的顶点所对应的集合的根
int find(int);

int main() {
    int n, m, u, v;
    long long w;
    
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        scanf("%d%d%lld", &EDGE[i].u, &EDGE[i].v, &EDGE[i].w);
    }

    sort(EDGE, EDGE + m, edge_cmp);
    
    cout << kruskal(EDGE, n, m);
}

bool edge_cmp(Edge left, Edge right) {
    return left.w < right.w;
}

long long kruskal(Edge *edges, int v_cnt, int e_cnt) {
    //初始化并查集
    for(int i = 0; i < v_cnt; i++) {
        FIND_A[i] = i;
    }

    //记录始点在并查集中的根，终点在并查集中的根
    int a_e_start, a_e_end;
    
    //当已经插入的边的数目 == n-1 时停止
    int r_cnt = 1;
    long long length = 0;

    for(int i = 0; i < e_cnt && r_cnt < v_cnt; i++) {
        a_e_start = find(edges[i].u);
        a_e_end = find(edges[i].v);

        if(a_e_end == a_e_start) {
            continue;
        }
        //这里需要将目标节点集合整个集合合并到源节点集合中，故不能FIND_A[edges[i].v] = a_e_start，这样只能合并一个或一部分节点
        FIND_A[a_e_end] = a_e_start;
        length += edges[i].w;
        r_cnt++;
    }

    return length;
}

int find(int vertex) {
    while(vertex != FIND_A[vertex]) {
        vertex = FIND_A[vertex] = FIND_A[FIND_A[vertex]];
    }
    return vertex;
}