/*
 * Use Floyd-Warshall on an undirected weighted graph to find its largest
 * finite shortest-path distance and list the ordered vertex pairs attaining it.
 */

//使用邻接矩阵表示的图，允许有负边、自环、重边
#include<stdio.h>
#include<string.h>

#define MAXSIZE 305

long long int D0[MAXSIZE][MAXSIZE];

//输入待计算的邻接矩阵，算法执行完毕后二维数组中保存的将是最终结果
long long floyd_warshall(long long int d[MAXSIZE][MAXSIZE], int n);

int main() {
    int n, m, t;
    int u, v;
    long long int temp;

    scanf("%d", &t);
    for(int i = 0; i < t; i++) {
        //这种初始化方式要求各边权值，以及各路径长均小于0x3f3f3f3f3f3f3f3f
        memset(D0, 0x3f, sizeof(D0));
        
        //输入图的顶点数、边数、查询次数
        scanf("%d%d", &n, &m);
        for(int i = 0; i < m; i++) {
            scanf("%d %d %lld", &u, &v, &temp);
            //能够同时处理重边
            if(temp < D0[u][v]) {
                D0[u][v] = temp;
                D0[v][u] = temp;
            }
        }

        //初始化+处理自环
        for(int i = 1; i <= n; i++) {
            D0[i][i] = 0;
        }

        long long maxd = floyd_warshall(D0, n);
        int cnt = 0;

        for(int i = 0; i <= n; i++) {
            for(int j = 0; j <= n; j++) {
                if(D0[i][j] == maxd) {
                    cnt++;
                }
            }
        }
        printf("%d %d\n", maxd, cnt);

        for(int i = 0; i <= n; i++) {
            for(int j = 0; j <= n; j++) {
                if(D0[i][j] == maxd) {
                    printf("%d %d\n", i, j);
                }
            }
        }
    }

    

    
}

long long floyd_warshall(long long int d[MAXSIZE][MAXSIZE], int n) {
    for(int k = 1; k < n; k++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if(d[i][j] <= d[i][k] + d[k][j]) {
                    d[i][j] = d[i][j];
                }else {
                    d[i][j] = d[i][k] + d[k][j];
                }
            }
        }
    }

    long long maxd = -1;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(d[i][j] <= d[i][n] + d[n][j]) {
                d[i][j] = d[i][j];
            }else {
                d[i][j] = d[i][n] + d[n][j];
            }
            if(d[i][j] > maxd && d[i][j] != 0x3f3f3f3f3f3f3f3f) {
                maxd = d[i][j];
            }
        }
    }
    return maxd;
}