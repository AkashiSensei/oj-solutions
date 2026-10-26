/*
 * Problem Link: https://leetcode.cn/problems/partition-equal-subset-sum/
 * Problem Name: 416. Partition Equal Subset Sum
 * Difficulty: Medium
 * Problem Tags: array, dynamic programming
 *
 * Submission Record:
 * Approach: Bottom-up 0/1 subset-sum DP with a two-dimensional boolean table
 * Language: C++
 * Status: Accepted
 * Submitted At: N/A
 * Runtime: 179 ms (beats 9.57%)
 * Memory: 17.01 MB (beats 35.93%)
 * Submission Link: N/A
 * Recorded On: 2026-10-26
 * Record Source: User-provided accepted-submission screenshot
 *
 * Problem Description:
 * Given a nonempty array nums containing only positive integers, determine
 * whether its elements can be partitioned into two subsets with equal sums.
 * Every array element belongs to exactly one of the two subsets.
 * Equal values at different positions are separate elements.
 *
 * Constraints:
 * 1. 1 <= nums.length <= 200
 * 2. 1 <= nums[i] <= 100
 *
 * Example 1:
 * Input: nums = [1,5,11,5]
 * Output: true
 * Explanation: The array can be partitioned into [1,5,5] and [11].
 *
 * Example 2:
 * Input: nums = [1,2,3,5]
 * Output: false
 * Explanation: No partition into two equal-sum subsets exists.
 *
 * Note:
 * The local main() runs both official examples directly.
 * Subsets do not need to be contiguous segments of the input.
 * The input vector is not modified; all DP state is local to each call.
 * table[l][t] uses zero-based l: it considers nums[0] through nums[l], inclusive.
 * Distinct array positions can hold equal values and may each be chosen once.
 *
 * Approach:
 * Compute the total sum. An odd total cannot be split equally; otherwise set
 * the subset target T to half the total. Finding one subset of sum T suffices,
 * since its complement then has the same sum.
 * Build table[l][t], indicating whether the first l + 1 elements can form t.
 * Sum zero is reachable with the empty subset. With only nums[0] available,
 * a positive sum is reachable exactly when it equals nums[0].
 * For later rows, either skip nums[l] and inherit table[l-1][t], or select it
 * once and check table[l-1][t-nums[l]] when the remainder is nonnegative.
 * Both alternatives use the previous row, preventing reuse of the same element.
 * Return the final row's entry for T.
 *
 * Complexity:
 * Let n be nums.size() and T half the total when that total is even.
 * Summation takes O(n), and an odd total exits immediately in O(n) time and
 * O(1) auxiliary space. For an even total, n rows each scan T + 1 sums with
 * O(1) work per state, giving O(n*T) total time and O(n*T) auxiliary DP space.
 * vector<bool> typically packs its logical states into bits; the space bound
 * counts n*(T + 1) boolean states rather than assuming one byte per state.
 * There is no recursion. This bound depends on the numeric target, so it is
 * pseudo-polynomial. Under the constraints, T <= 10000.
 */

#include <cstdio>
#include <vector>
#include <numeric>

using namespace std;

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int len = nums.size();
        // O(n) summation; integer accumulation is safe under the stated bounds.
        int sums = accumulate(nums.begin(), nums.end(), 0);
        if (sums % 2 == 1) return false;

        sums /= 2;  // A subset of this sum leaves an equally large complement.
        // Row l considers the first l + 1 elements; all states initially false.
        vector<vector<bool>> table(len, vector<bool>(sums + 1));

        for (int l = 0; l < len; l++) {
            for (int t = 0; t <= sums; t++) {
                // Choosing no elements always forms sum zero.
                if (t == 0) {
                    table[l][0] = true;
                    continue;
                }

                // The first row has only the single element nums[0] available.
                if (l == 0) {
                    table[0][t] = nums[0] == t;
                    continue;
                }

                // Skip or take the current element once, using only the previous row.
                table[l][t] = table[l-1][t] || (t - nums[l] >= 0 && table[l-1][t-nums[l]]);
            }
        }

        return table[len - 1][sums];
    }
};

int main() {
    Solution sol;
    vector<int> inputs[] = {
        {1, 5, 11, 5},
        {1, 2, 3, 5}
    };

    // Expected outputs: true, false.
    for (int i = 0; i < 2; i++) {
        printf("Example %d: %s\n", i + 1,
               sol.canPartition(inputs[i]) ? "true" : "false");
    }

    return 0;
}
