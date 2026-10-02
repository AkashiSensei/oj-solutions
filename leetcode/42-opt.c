/*
 * Problem Link: https://leetcode.cn/problems/trapping-rain-water/
 * Problem Name: 42. Trapping Rain Water
 * Difficulty: Hard
 * Problem Tags: array, two pointers, dynamic programming, stack,
 * monotonic stack
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

int trap(int* height, int heightSize) {
    int left = 0, right = heightSize - 1;
    int lmax = 0, rmax = 0;
    int ans = 0;

    while (left <= right) {
        if (lmax < rmax) {
            if (lmax > height[left]) ans += lmax - height[left];
            else lmax = height[left];
            left++;
        } else {
            if (rmax > height[right]) ans += rmax - height[right];
            else rmax = height[right];
            right--;
        }
    }

    return ans;
}

int main() {
    int height[12] = {0,1,0,2,1,0,1,3,2,1,2,1};
    printf("%d\n", trap(height, 12));

}

