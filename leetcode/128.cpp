/*
 * Problem Link: https://leetcode.cn/problems/longest-consecutive-sequence/
 * Problem Name: 128. Longest Consecutive Sequence
 * Difficulty: Medium
 * Problem Tags: array, sorting
 *
 * Submission Record:
 * Approach: Sort + linear scan of consecutive distinct values
 * Language: C++
 * Status: Accepted
 * Submitted At: N/A
 * Runtime: 28 ms (beats 90.58%)
 * Memory: 58.91 MB (beats 94.76%)
 * Submission Link: N/A
 * Recorded On: 2026-10-29
 * Record Source: User-provided accepted-submission screenshot
 *
 * Problem Description:
 * Given an unsorted integer array nums, return the length of the longest
 * sequence of consecutive integer values that can be formed from its elements.
 * The elements need not be adjacent or appear in sequence order in nums.
 * Repeated occurrences of the same value do not extend the sequence.
 * Design and implement an algorithm with O(n) time complexity.
 *
 * Constraints:
 * 1. 0 <= nums.length <= 100000
 * 2. -1000000000 <= nums[i] <= 1000000000
 *
 * Example 1:
 * Input: nums = [100,4,200,1,3,2]
 * Output: 4
 * Explanation: The longest consecutive sequence is [1,2,3,4].
 *
 * Example 2:
 * Input: nums = [0,3,7,2,5,8,4,6,0,1]
 * Output: 9
 *
 * Example 3:
 * Input: nums = [1,0,1,2]
 * Output: 3
 *
 * Note:
 * The local main() contains all three official examples and prints
 * actual and expected results.
 * The input vector is sorted in place when it has at least two elements.
 * This accepted sorting implementation takes O(n log n) time and does not
 * meet the problem statement's O(n) time requirement.
 *
 * Approach:
 * Return the array size directly for an empty or single-element input.
 * Otherwise, sort nums in ascending order and scan from index 1, comparing
 * each element with its predecessor. cnt counts the distinct consecutive
 * values in the current run. Increment it when the difference is one;
 * skip duplicates without changing cnt. On a gap, record the completed
 * run in result and restart cnt at one. After the scan, record the final
 * run as well, since it may not be followed by a gap.
 * Comparing adjacent sorted values finds consecutive integer sequences
 * regardless of their positions or order in the original array.
 *
 * Complexity:
 * Let n be nums.size(). Sorting takes O(n log n) time and the subsequent
 * scan takes O(n), for O(n log n) total time when n >= 2.
 * The scan uses O(1) auxiliary space. Assuming the usual std::sort
 * implementation with O(log n) stack space, total auxiliary space is
 * O(log n); the C++ standard does not mandate this space bound.
 * The early return for n < 2 takes O(1) time and space. No output array
 * or explicit auxiliary table is allocated.
 */

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if (nums.size() < 2) {
            return nums.size();
        }

        int result = 1;
        int cnt = 1;

        sort(nums.begin(), nums.end());

        // Start at 1 because each iteration also accesses nums[i - 1].
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == nums[i - 1] + 1) {
                cnt++;
            } else if (nums[i] == nums[i - 1]) {
                // Duplicate values do not lengthen or break the current run.
                continue;
            }else{
                // A gap completes the previous run and starts a new one.
                result = max(result, cnt);
                cnt = 1;
            }
        }

        // The last run also needs to be considered.
        result = max(result, cnt);

        return result;
    }
};

int main() {
    Solution sol;
    vector<int> inputs[] = {
        {100, 4, 200, 1, 3, 2},
        {0, 3, 7, 2, 5, 8, 4, 6, 0, 1},
        {1, 0, 1, 2}
    };
    int expected[] = {4, 9, 3};

    for (int i = 0; i < 3; ++i) {
        printf("Example %d: %d\n", i + 1, sol.longestConsecutive(inputs[i]));
        printf("Expected: %d\n", expected[i]);
    }

    return 0;
}
