/*
 * Problem Link: https://leetcode.cn/problems/longest-increasing-subsequence/
 * Problem Name: 300. Longest Increasing Subsequence
 * Difficulty: Medium
 * Problem Tags: array, dynamic programming
 *
 * Submission Record:
 * Approach: Bottom-up DP for the longest increasing subsequence ending at each index
 * Language: C++
 * Status: Accepted
 * Submitted At: N/A
 * Runtime: 87 ms (beats 37.46%)
 * Memory: 14.15 MB (beats 40.73%)
 * Submission Link: N/A
 * Recorded On: 2026-10-26
 * Record Source: User-provided accepted-submission screenshot
 *
 * Problem Description:
 * Given an integer array nums, return the length of its longest strictly
 * increasing subsequence.
 * A subsequence is obtained by deleting zero or more elements without
 * changing the relative order of the remaining elements. Its elements
 * need not occupy consecutive positions in the original array.
 * Strictly increasing means each selected value is greater than the previous one.
 *
 * Constraints:
 * 1. 1 <= nums.length <= 2500
 * 2. -10000 <= nums[i] <= 10000
 *
 * Example 1:
 * Input: nums = [10,9,2,5,3,7,101,18]
 * Output: 4
 * Explanation: [2,3,7,101] is an increasing subsequence of length 4.
 *
 * Example 2:
 * Input: nums = [0,1,0,3,2,3]
 * Output: 4
 *
 * Example 3:
 * Input: nums = [7,7,7,7,7,7,7]
 * Output: 1
 *
 * Note:
 * The local main() runs all three official examples directly.
 * Return only the length, not the subsequence itself.
 * The input vector is not modified. All state is local to each call.
 * Equal values cannot extend each other because the subsequence is strictly increasing.
 *
 * Approach:
 * table[i] stores the longest strictly increasing subsequence ending exactly
 * at nums[i], rather than the best length anywhere in the prefix.
 * Scan all earlier indices t with nums[t] < nums[i] and find the largest
 * table[t]. Add one for nums[i]; if there is no eligible predecessor, the
 * resulting length is one. Every dependency is already computed because t < i.
 * Track the maximum over all ending positions: the answer need not end at
 * the last array element. No subsequence reconstruction is required.
 *
 * Complexity:
 * Let n be nums.size(). The inner loop performs 0 + 1 + ... + (n - 1)
 * = n*(n - 1)/2 checks, each taking O(1) work. Together with O(n) table
 * initialization and updates, total time is O(n^2).
 * The table stores n integers and the other local variables take O(1) space,
 * giving O(n) auxiliary space. No recursion or input copy is used.
 */

#include <cstdio>
#include <vector>

using namespace std;

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int len = nums.size();

        // table[i] describes subsequences that must include nums[i] as their last value.
        vector<int> table(len);
        int result = 0, maxl;

        for (int i = 0; i < len; i++) {
            // Find the best earlier subsequence that this value can extend.
            maxl = 0;
            for (int t = 0; t < i; t++) {
                if (nums[t] < nums[i] && table[t] > maxl) {
                    maxl = table[t];
                }
            }
            maxl++;  // Include nums[i], or start a length-one subsequence.

            table[i] = maxl;
            // The global optimum may finish at any position.
            if (maxl > result) {
                result = maxl;
            }
        }

        return result;
    }
};

int main() {
    Solution sol;
    vector<int> inputs[] = {
        {10, 9, 2, 5, 3, 7, 101, 18},
        {0, 1, 0, 3, 2, 3},
        {7, 7, 7, 7, 7, 7, 7}
    };

    // Expected outputs: 4, 4, 1.
    for (int i = 0; i < 3; i++) {
        printf("Example %d: %d\n", i + 1, sol.lengthOfLIS(inputs[i]));
    }

    return 0;
}
