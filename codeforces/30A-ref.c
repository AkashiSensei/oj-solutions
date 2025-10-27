#include <stdio.h>

long long power(long long x, int n) {
    long long result = 1;
    for (int i = 0; i < n; i++) {
        result *= x;
    }
    return result;
}

int main() {
    long long a, b, n;
    scanf("%lld%lld%lld", &a, &b, &n);
    
    // 特殊情况：A = 0
    if (a == 0) {
        printf("%s\n", b == 0 ? "5" : "No solution");
        return 0;
    }
    
    // 检查B是否能被A整除
    if (b % a != 0) {
        printf("No solution\n");
        return 0;
    }
    
    long long target = b / a;
    
    // 特殊情况：target = 0
    if (target == 0) {
        printf("0\n");
        return 0;
    }
    
    // 特殊情况：target = 1
    if (target == 1) {
        printf("1\n");
        return 0;
    }
    
    // 特殊情况：target = -1
    if (target == -1) {
        printf("%s\n", n % 2 == 1 ? "-1" : "No solution");
        return 0;
    }
    
    // 检查符号是否合理
    if (target < 0 && n % 2 == 0) {
        printf("No solution\n");
        return 0;
    }
    
    // 正数情况：从2开始搜索
    if (target > 0) {
        for (long long x = 2; x <= 1000; x++) {
            if (power(x, n) == target) {
                printf("%lld\n", x);
                return 0;
            }
        }
    }
    
    // 负数情况：从-2开始搜索（当n为奇数时）
    if (target < 0 && n % 2 == 1) {
        for (long long x = -2; x >= -1000; x--) {
            if (power(x, n) == target) {
                printf("%lld\n", x);
                return 0;
            }
        }
    }
    
    printf("No solution\n");
    return 0;
}