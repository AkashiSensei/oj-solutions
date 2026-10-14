/*
 * Answer distance queries in an undirected graph when only vertices 1 through
 * limit may be intermediate stops, using a restricted Floyd-Warshall pass.
 */

//使用邻接矩阵表示的图，允许有负边、自环、重边
#include<stdio.h>
#include<string.h>

#define MAXSIZE 105

long long int D0[MAXSIZE][MAXSIZE];

//输入待计算的邻接矩阵，算法执行完毕后二维数组中保存的将是最终结果
void floyd_warshall(long long int d[MAXSIZE][MAXSIZE], int n, int limit);

int main() {
    int n, m, q;
    int u, v, limit;
    long long int temp;

    int g;
    scanf("%d", &g);
    while(g--) {
        //这种初始化方式要求各边权值，以及各路径长均小于0x3f3f3f3f3f3f3f3f
        memset(D0, 0x3f, sizeof(D0));
        
        //输入图的顶点数、边数、查询次数
        scanf("%d %d %d", &n, &m, &limit);
        for(int i = 0; i < m; i++) {
            scanf("%d %d %lld", &u, &v, &temp);
            if(temp < D0[u][v]) {
                D0[u][v] = temp;
            }
            if(temp < D0[v][u]) {
                D0[v][u] = temp;
            }
        }

        for(int i = 1; i <= n; i++) {
            D0[i][i] = 0;
        }

        floyd_warshall(D0, n, limit);
        scanf("%d", &q);

        for(int i = 0; i < q; i++) {
            scanf("%d %d", &u, &v);
            if(D0[u][v] != 0x3f3f3f3f3f3f3f3f) {
                printf("%lld\n", D0[u][v]);
                //print_shortest(u, v);
            }else {
                printf("QAQ\n");
            }        
        }
    }


}

void floyd_warshall(long long int d[MAXSIZE][MAXSIZE], int n, int limit) {

    for(int k = 1; k <= limit; k++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if(d[i][j] <= d[i][k] + d[k][j]) {
                    d[i][j] = d[i][j];
                }else {
                    d[i][j] = d[i][k] + d[k][j];
                    //pi[i][j] = pi[k][j];
                }
            }
        }
    }
}