/*
 * Problem Link: https://codeforces.com/problemset/problem/1987/C
 * Problem Name: C. Basil's Garden
 * Difficulty: 1200 (Codeforces Rating)
 * Problem Tags: dp, greedy
 * Time Limit per Test: 2 seconds
 * Memory Limit per Test: 256 megabytes
 * 
 * Problem Description:
 * There are n flowers arranged in a row. The i-th flower initially has a 
 * positive height of h_i meters.
 * Every second, the wind blows from the left, causing some flowers' heights to 
 * decrease. The specific rule is:
 * Every second, process each i from 1 to n in this order. For each i:
 * If i = n (the last flower) OR h_i (height of i-th flower) > h_{i+1} 
 * (height of (i+1)-th flower), then set h_i to max(0, h_i - 1) — decrease by 1,
 * but not below 0.
 * Find the number of seconds until all flowers have height 0 (h_i = 0 for all 
 * 1 ≤ i ≤ n) for the first time.
 * 
 * Input Specification:
 * The input contains multiple test cases:
 * 1. First line: single integer t (1 ≤ t ≤ 10^4) — number of test cases.
 * 2. For each test case:
 *    a. First line: single integer n (1 ≤ n ≤ 10^5) — number of flowers.
 *    b. Second line: n integers h_1, h_2, …, h_n (1 ≤ h_i ≤ 10^9) — initial 
 *       heights of the flowers.
 * It is guaranteed that the sum of n over all test cases does not exceed 10^5.
 * 
 * Output Specification:
 * For each test case, output a single integer — seconds needed for all flowers 
 * to become 0 for the first time.
 * 
 * Example Input:
 * 4
 * 3
 * 1 1 2
 * 2
 * 3 1
 * 1
 * 9
 * 5
 * 7 4 4 3 2
 * 
 * Example Output:
 * 4
 * 3
 * 9
 * 7
 * 
 * Note:
 * In the first test case, flower heights change as follows:
 * [1, 1, 2] → [1, 1, 1] → [1, 1, 0] → [1, 0, 0] → [0, 0, 0]
 * 
 * In the second test case, flower heights change as follows:
 * [3, 1] → [2, 0] → [1, 0] → [0, 0]
 */



#include <stdio.h>

unsigned int H[100005];

int main() {
    int t, n;
    unsigned int time;
    scanf("%d", &t);

    while(t--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%u", H + i);
        }

        if (n == 1) {
            printf("%d\n", H[0]);
            continue;
        }

        time = H[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            time = H[i] >= time + 1 ? H[i] : time + 1;
        }
        printf("%u\n", time);
    }

    return 0;
}
