/*
 * Problem Link: https://leetcode.cn/problems/trapping-rain-water/
 * Problem Name: 42. Trapping Rain Water
 * Difficulty: Hard
 * Problem Tags: array, two pointers, dynamic programming, stack,
 * monotonic stack
 *
 * Submission Record:
 * Approach: Two pointers comparing boundary heights
 * Language: C++
 * Status: Accepted
 * Submitted At: 2026-10-03 12:46 (Asia/Shanghai)
 * Runtime: 0 ms (beats 100.00%)
 * Memory: 25.52 MB (beats 65.47%)
 * Submission Link:
 * https://leetcode.cn/problems/trapping-rain-water/submissions/752574872/
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


#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        auto left = height.begin();
        auto right = height.end() - 1;
        int lmax = 0;
        int rmax = 0;
        int ans = 0;

        // This holds because rmax never exceeds *left while moving from the
        // right, and lmax never exceeds *right while moving from the left.

        // Move inward from the shorter end. The remaining bar is a tallest one
        // and traps no water, so <= is unnecessary.
        while (left < right) {
            if (*left < *right) {
                if (*left < lmax) ans += lmax - *left;
                else lmax = *left;
                ++left;
            } else {
                if (*right < rmax) ans += rmax - *right;
                else rmax = *right;
                --right;
            }
        }

        return ans;
    }
};

int main() {
    Solution sol;
    vector<int> example1 = {0,1,0,2,1,0,1,3,2,1,2,1};
    vector<int> example2 = {4,2,0,3,2,5};

    cout << sol.trap(example1) << "\n";
    cout << sol.trap(example2) << "\n";

    return 0;
}
