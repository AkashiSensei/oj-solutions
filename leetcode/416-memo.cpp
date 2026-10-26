/*
 * Problem Link: https://leetcode.cn/problems/partition-equal-subset-sum/
 * Problem Name: 416. Partition Equal Subset Sum
 * Difficulty: Medium
 * Problem Tags: array, dynamic programming, memoization
 *
 * Submission Record:
 * Approach: Top-down 0/1 subset-sum recursion with separate result and visited tables
 * Language: C++
 * Status: Accepted
 * Submitted At: N/A
 * Runtime: 87 ms (beats 55.65%)
 * Memory: 20.89 MB (beats 19.77%)
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
 * Input nums is borrowed through a member pointer and is not modified or copied.
 * Each even-total call rebuilds both memo tables before starting the search.
 * An odd-total call returns before rebuilding them, so earlier allocations may
 * remain in a reused object without affecting that call's result.
 *
 * Approach:
 * Reject an odd total; otherwise search for a subset summing to half the total.
 * checkSum(l, t) asks whether nums[0] through nums[l] can form sum t.
 * Sum zero is always reachable. With only the first element available, compare
 * that value with t. Other states either skip nums[l] or select it once and
 * search the shorter prefix for the remaining sum, provided it is nonnegative.
 * table stores the boolean result and valid distinguishes cached results from
 * uncomputed states, so impossible states are cached as well as possible ones.
 * The logical OR short-circuits after a successful skip branch, avoiding an
 * unnecessary take branch. Every recursive call reduces l, so no cycle exists.
 * The constant-time base cases are returned directly rather than memoized.
 *
 * Complexity:
 * Let n be nums.size() and T half the total for an even total.
 * Summation costs O(n). At most n*(T + 1) states can be computed, each with
 * O(1) local work and at most two transitions. Memoization bounds search time
 * by O(n*T), and allocating both full tables also stays within O(n*T).
 * Total worst-case time is O(n*T); short-circuiting can reduce explored states
 * but does not remove the full table allocations.
 * The two tables use O(n*T) logical boolean states, and the recursion stack
 * uses O(n) space, for O(n*T) auxiliary space overall. vector<bool> typically
 * packs these states into bits. No output collection or input copy is created.
 * An odd total takes O(n) time and allocates no new DP tables; on a fresh object
 * it uses O(1) extra space. This is a pseudo-polynomial bound; T <= 10000 here.
 */

#include <cstdio>
#include <vector>
#include <numeric>

using namespace std;

class Solution {
private:
    // Cached feasibility for each prefix endpoint and remaining target.
    vector<vector<bool>> table;
    // A cached false result must remain distinguishable from an uncomputed state.
    vector<vector<bool>> valid;
    vector<int>* p_nums;

    bool checkSum(int l, int t) {
        // The empty subset forms zero; a single-element prefix has one nonzero choice.
        if (t == 0) return true;

        if (l == 0) return (*p_nums)[0] == t;

        if (valid[l][t]) return table[l][t];

        // l strictly decreases along recursion, so this state cannot be reentered.
        valid[l][t] = true;
        // Skip first; if it fails, take this element once when the target permits it.
        table[l][t] = checkSum(l-1, t) || (t - (*p_nums)[l] >= 0 && checkSum(l-1, t-(*p_nums)[l]));

        return table[l][t];
    }

public:
    bool canPartition(vector<int>& nums) {
        int len = nums.size();
        int sums = accumulate(nums.begin(), nums.end(), 0);
        if (sums % 2 == 1) return false;
        sums /= 2;

        // Reinitialize full memo storage for this even-total query.
        table.assign(len, vector<bool>(sums + 1));
        valid.assign(len, vector<bool>(sums + 1));
        p_nums = &nums;

        return checkSum(len - 1, sums);
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
