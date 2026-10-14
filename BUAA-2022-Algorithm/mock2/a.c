/*
 * For each input triple n, m, k, print the arithmetic-progression sum
 * n + (n+m) + ... + (n+k*m) using its closed-form formula.
 */

#include <stdio.h>
int main()
{
    int n, m, k;

    while(scanf("%d%d%d", &n, &m, &k) != EOF)  // 本行实现输入3个整数到变量n, m, k 
    {
        long long result = 0;
        result += n * (k + 1);
        result += k * (k + 1) / 2 * m;
        printf("%lld\n", result);

    }

    return 0;
}