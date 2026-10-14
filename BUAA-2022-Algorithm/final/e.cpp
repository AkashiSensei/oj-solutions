/*
 * Find a minimum-cost route through stations on multiple assembly lines
 * with transfer costs, and reconstruct the selected line at each station.
 */

#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

int pi[12][105];
void print_station(int line, int sta) {
    if(sta == 1) {
        printf("%d\n", line);
        return;
    }
    print_station(pi[line][sta], sta - 1);
    printf("%d\n", line);
}

int main()
{
    ios::sync_with_stdio(false);
    int num,n;
    int fend;
    int i,j;
    int tempf;
    int g;
    cin >> g;
    while(g--) {
        //num 流水线  n 站台
        cin >> num >> n;
        int a[num + 1][n+1],t[num + 1][num + 1];
        for(i = 1;i<=num;i++)
            for(j = 1;j<=n;j++)
                cin >> a[i][j];//i条线j站台的花费 
        
        for(i = 1;i<=num;i++)
            for(j = 1;j<=num;j++)
                cin >> t[i][j];//i条线到j条线的调度费用 

        int f[num + 1][n+1];//一维为当前线路，二维为站台位置 
        for(i = 1;i<=num;i++)
        {
            f[i][1] = a[i][1];//每条线第一个站台的最小花费就是第一个 
            pi[i][1] = i;
        }
        for(i = 2;i<=n;i++)
        {
            for(j = 1;j<=num;j++)
            {
                tempf = 2147483647;//为了找到最小值先设定最大的 
                for(int k = 1;k<=num;k++)
                {//循环判断所有条道路的情况 
                    if(tempf > f[k][i-1]+t[k][j]+a[j][i])
                    {
                        tempf = f[k][i-1]+t[k][j]+a[j][i];
                        pi[j][i] = k;
                    }
                }
                f[j][i] = tempf;//存储j条线在i站台的最小值 
            }
        }
        int findn;
        //tempf = f[0][n];
        tempf = 2147483647;
        for(i = 1;i<=num;i++) //!!!!!!!!!!
        {
            if(tempf > f[i][n])
            {
                tempf = f[i][n];
                findn = i;
            }
        }
        fend = tempf;//得到最大值 
        printf("%d\n", fend);
        print_station(findn, n);

    }
    return 0;
}
