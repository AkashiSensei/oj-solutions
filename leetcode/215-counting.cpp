/*
 * Problem Link: https://leetcode.cn/problems/kth-largest-element-in-an-array/
 * Problem Name: 215. Kth Largest Element in an Array
 * Difficulty: Medium
 * Problem Tags: array, counting
 *
 * Submission Record:
 * Approach: Frequency counting over a bounded integer range
 * Language: C++
 * Status: Accepted
 * Submitted At: N/A
 * Runtime: 3 ms (beats 95.04%)
 * Memory: 71.95 MB (beats 14.62%)
 * Submission Link:
 * N/A
 * Recorded On: 2026-10-14
 * Record Source: User-provided accepted-submission screenshot
 *
 * Problem Description:
 * Given an integer array nums and an integer k, return its kth largest
 * element. Duplicate values count separately in the sorted order.
 * The problem asks for an O(n)-time selection algorithm.
 *
 * Constraints:
 * 1. 1 <= k <= nums.length <= 100000
 * 2. -10000 <= nums[i] <= 10000
 *
 * Example 1:
 * Input: nums = [3,2,1,5,6,4], k = 2
 * Output: 5
 *
 * Example 2:
 * Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
 * Output: 4
 *
 * Note:
 * The local main() runs the two official examples directly.
 * The input vector is passed by reference and is not modified.
 *
 * Approach:
 * Map each value to a nonnegative index by adding 10000, then count its
 * frequency in a local vector. Traverse indices from high to low and
 * accumulate counts; the first index whose cumulative count reaches k
 * identifies the kth largest value, including duplicates.
 * The buffer has 20002 entries; valid values use indices 0 through 20000.
 * The extra highest slot remains zero and does not affect the answer.
 * A fresh zero-filled vector is created for every call, so repeated calls
 * do not share counting state.
 *
 * Complexity:
 * Let n be nums.size() and U = 20002 be the counting-buffer length.
 * Zero-initialization takes O(U) time, frequency counting takes O(n), and
 * the descending scan takes O(U) worst-case time. Total time is O(n + U),
 * with O(U) auxiliary space and no recursive stack. Since the value range
 * is fixed by the problem, U is constant with respect to n, giving O(n)
 * time and O(1) auxiliary space when only n is treated as variable.
 */

#include <vector>
#include <cstdio>

using namespace std;

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        // O(U) initialization and storage; all counters start at zero per call.
        vector<int> counting(20002, 0);

        // O(n): translate values from [-10000, 10000] to array indices.
        for (int i = 0; i < nums.size(); i++) {
            counting[nums[i] + 10000]++;
        }

        // O(U) worst-case scan; cnt tracks how many largest elements are covered.
        int cnt = 0;
        for (int i = 20001; i >= 0; i--) {
            cnt += counting[i];
            // Convert the bucket index back to its original integer value.
            if (cnt >= k) return i - 10000;
        }

        // Unreachable for valid input: 1 <= k <= nums.size().
        return 0;
    }
};

int main() {
    Solution sol;

    vector<int> input1 = {3,2,1,5,6,4};
    vector<int> input2 = {3,2,3,1,2,4,5,5,6};

    // Expected output: 5, then 4 on the next line.
    printf("%d\n%d\n",
           sol.findKthLargest(input1, 2),
           sol.findKthLargest(input2, 4)
          );

    return 0;
}
