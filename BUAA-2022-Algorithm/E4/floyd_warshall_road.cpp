/*
 * Compute all-pairs shortest paths with Floyd-Warshall and predecessor tracking.
 * For each reachable query, print the distance and reconstruct the vertex sequence.
 */

//使用邻接矩阵表示的图，允许有负边、自环、重边
#include<stdio.h>
#include<string.h>

#define MAXSIZE 10

long long int D0[MAXSIZE][MAXSIZE];
int PI[MAXSIZE][MAXSIZE];

//输入待计算的邻接矩阵，算法执行完毕后二维数组中保存的将是最终结果
void floyd_warshall(long long int d[MAXSIZE][MAXSIZE], int pi[MAXSIZE][MAXSIZE], int n);

//使用floyd_warshell算法计算完毕后，使用该函数输出计算结果
void print_shortest(int u, int v);
void print_vertex(int u, int v);

int main() {
    int n, m, q;
    int u, v;
    long long int temp;

    //这种初始化方式要求各边权值，以及各路径长均小于0x3f3f3f3f3f3f3f3f
    memset(D0, 0x3f, sizeof(D0));
    
    //输入图的顶点数、边数、查询次数
    scanf("%d %d %d", &n, &m, &q);
    for(int i = 0; i < m; i++) {
        scanf("%d %d %lld", &u, &v, &temp);
        //能够同时处理重边
        if(temp < D0[u][v]) {
            D0[u][v] = temp;
            PI[u][v] = u;
        }
    }

    //初始化+处理自环
    for(int i = 1; i <= n; i++) {
        D0[i][i] = 0;
        PI[i][i] = 0;
    }

    floyd_warshall(D0, PI, n);

    for(int i = 0; i < q; i++) {
        scanf("%d %d", &u, &v);
        if(D0[u][v] != 0x3f3f3f3f3f3f3f3f) {
            printf("%lld\n", D0[u][v]);
            print_shortest(u, v);
        }else {
            printf("No So1ution\n");
        }        
    }
}

void floyd_warshall(long long int d[MAXSIZE][MAXSIZE], int pi[MAXSIZE][MAXSIZE], int n) {

    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                //注意这里的等于号，去掉等于号不会导致路径长度错误，但会导致求不出来具体路径
                if(d[i][j] <= d[i][k] + d[k][j]) {
                    d[i][j] = d[i][j];
                }else {
                    d[i][j] = d[i][k] + d[k][j];
                    pi[i][j] = pi[k][j];
                    /*
                    该段文字用于简要证明可以直接原表修改元素：

                    首先我们容易观察到：
                    对于每个不同的k值，每次比较操作相当于，在自身以及两元素和之间选择最小值，
                    而这两元素和，分别为（i，j）在第k行和第k列上的投影。

                    其次：
                    对于在第k行和第k列的元素，比较操作不会改变其值。

                    最后：
                    对于第k行和第k列以外的元素，比较操作只会用到自身的值以及第k行和第k列上元素的值，同时只有可能更改自身的值，
                    因而前者不会受其他位置元素的操作影响，而后者在本轮操作中恒定不变。

                    综上：
                    可以原表修改元素。

                    */
                }
            }
        }
    }
}

void print_shortest(int u, int v) {
    if(PI[u][v] || u == v) {
        print_vertex(u, v);
        printf("%d\n", v);
    }else{
        printf("No\n");
    }
}


void print_vertex(int u, int v) {
    if(u == v) {
        return;
    }
    print_vertex(u, PI[u][v]);
    printf("%d ", PI[u][v]);
}