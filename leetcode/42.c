/*
 * Problem Link: https://leetcode.cn/problems/trapping-rain-water/
 * Problem Name: 42. Trapping Rain Water
 * Difficulty: Hard
 * Problem Tags: array, two pointers, dynamic programming, stack,
 * monotonic stack
 *
 * Submission Record:
 * Approach: Suffix maxima + running prefix maximum
 * Language: C
 * Status: Accepted
 * Submitted At: 2026-10-02 21:11 (Asia/Shanghai)
 * Runtime: 0 ms (beats 100.00%)
 * Memory: 10.38 MB (beats 28.65%)
 * Submission Link:
 * https://leetcode.cn/problems/trapping-rain-water/submissions/752510213/
 * Recorded On: 2026-10-10
 *
 * Problem Description:
 * Given n non-negative integers representing an elevation map where the
 * width of each bar is 1, compute how much water it can trap after
 * raining.
 *
 * Input Specification:
 * The input is an integer array height of length n:
 * 1. n == height.length
 * 2. 1 <= n <= 2 * 10^4
 * 3. 0 <= height[i] <= 10^5
 * height[i] is the height of the i-th bar.
 *
 * Output Specification:
 * Return a single integer: the total units of rain water the elevation
 * map can trap.
 *
 * Example Input:
 * height = [0,1,0,2,1,0,1,3,2,1,2,1]
 * height = [4,2,0,3,2,5]
 *
 * Example Output:
 * 6
 * 9
 *
 * Note:
 * The first elevation map is represented by
 * [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water are
 * trapped. The blue region in the diagram is the trapped water.
 */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#define MAX_LENGTH 20005

int trap(int* height, int heightSize) {
    int ans = 0;
    int max = 0;
    int right_max[MAX_LENGTH];
    memset(right_max, 0, sizeof(right_max));

    for (int i = heightSize - 1; i >= 0; i--) {
        right_max[i] = max;
        if (height[i] > max) max = height[i];
    }

    max = 0;
    int min_side;

    for (int i = 0; i < heightSize; i++) {
        min_side = max < right_max[i] ? max : right_max[i];
        ans += min_side > height[i] ? min_side - height[i] : 0;
        if (height[i] > max) max = height[i];
    }

    return ans;

}

int main() {
    int height[12] = {0,1,0,2,1,0,1,3,2,1,2,1};

    printf("%d\n", trap(height, 12));

}

