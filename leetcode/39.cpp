/*
 * Problem Link: https://leetcode.cn/problems/combination-sum/
 * Problem Name: 39. Combination Sum
 * Difficulty: Medium
 * Problem Tags: array, dynamic programming, memoization
 *
 * Submission Record:
 * Approach: Memoized prefix/target DP storing all combinations
 * Language: C++
 * Status: Accepted
 * Submitted At: N/A
 * Runtime: 8 ms (beats 14.87%)
 * Memory: 19.46 MB (beats 8.18%)
 * Submission Link: N/A
 * Recorded On: 2026-10-22
 * Record Source: User-provided accepted-submission screenshot
 *
 * Problem Description:
 * Given an array of distinct integers candidates and a target integer,
 * return all unique combinations whose sum equals target.
 * Each candidate may be chosen an unlimited number of times.
 * Two combinations are different if at least one candidate has a different
 * frequency. The combinations may be returned in any order.
 * The input guarantees fewer than 150 distinct combinations for target.
 *
 * Constraints:
 * 1. 1 <= candidates.length <= 30
 * 2. 2 <= candidates[i] <= 40
 * 3. All elements in candidates are distinct.
 * 4. 1 <= target <= 40
 *
 * Example 1:
 * Input: candidates = [2,3,6,7], target = 7
 * Output: [[2,2,3],[7]]
 * Explanation: 2 + 2 + 3 = 7 and 7 = 7; a candidate may be reused.
 *
 * Example 2:
 * Input: candidates = [2,3,5], target = 8
 * Output: [[2,2,2,2],[2,3,3],[3,5]]
 *
 * Example 3:
 * Input: candidates = [2], target = 1
 * Output: []
 *
 * Note:
 * The local main() runs all three official examples directly.
 * Combination order and element order within a combination do not matter.
 * Input candidates is not modified. Member tables and filtered candidates are
 * reset on each call, so the same Solution object can be reused.
 * Candidate order is preserved; sorting is not required.
 * The returned reference from find() avoids copying during recursive lookup.
 * The public by-value return still copies the final cached combination list.
 *
 * Approach:
 * Remove candidates greater than target because all input values are positive.
 * State (before, tar) stores all combinations summing to tar using only the
 * first before filtered candidates. A separate valid flag caches empty results too.
 * For the last available value, enumerate its multiplicity i from zero through
 * floor(tar / value). For a positive remainder, obtain combinations from the
 * shorter prefix, copy each combination, and append i copies of value.
 * When the remainder reaches zero, directly construct the all-value combination;
 * this handles exact fills without storing an empty-combination base case.
 * Restricting recursive calls to a shorter prefix avoids permutation duplicates.
 * Start with candi.size(), not the original input size, including an empty prefix
 * when every candidate exceeds target.
 *
 * Complexity:
 * Let n be the original candidate count, T the target, and L the maximum
 * combination length, bounded by floor(T / min(candi)); let L = 0 if candi is empty.
 * Let S count all stored combination records plus their integer elements across
 * cached states, including intermediate combinations rather than just final output.
 * Allocating the tables costs O(n*T). Each of at most n*T computed states
 * enumerates at most L + 1 multiplicities. Copying and extending stored
 * combinations costs O(S) in total, including amortized vector growth.
 * The final by-value answer copy is also bounded by O(S).
 * Total time is O(n*T*(L + 1) + S); auxiliary space is O(n*T + S), including
 * the cached combinations and O(n) recursive stack, but excluding the returned copy.
 * This is not a scalar O(n*T) DP: storing all intermediate combinations can
 * grow combinatorially as the input bounds increase.
 */

#include <cstdio>
#include <vector>

using namespace std;

class Solution {
private:
    // table[before][tar] is a list of complete combinations for this state.
    vector<vector<vector<vector<int>>>> table;
    // Distinguish an uncomputed state from a computed state with no combinations.
    vector<vector<bool>> valid;
    vector<int> candi;

    vector<vector<int>>& find(int before, int tar) {
        if (valid[before][tar]) return table[before][tar];
        // Exact fills are constructed below; no candidate means no positive-sum solution.
        if (tar == 0 || before == 0) return table[before][tar];

        int value = candi[before - 1];
        // Enumerate how often the last candidate is used; recurse on a shorter prefix.
        for (int i = 0; tar - i * value >= 0; i++) {
            if (tar - i * value == 0) {
                // The selected copies alone fill tar, so no subproblem is needed.
                table[before][tar].emplace_back(i, value);
                break;
            }

            // Read cached results by reference; copy before extending each combination.
            auto& sublist = find(before - 1, tar - i * value);
            for (auto& line: sublist) {
                table[before][tar].push_back(line);
                for (int j = 0; j < i; j++)
                    table[before][tar].back().push_back(value);
            }
        }

        valid[before][tar] = true;

        return table[before][tar];
    }


public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        // Allocate prefix/target slots and discard all results from the previous call.
        table.assign(
                     candidates.size() + 1,
                     vector<vector<vector<int>>>(target + 1)
                    );
        valid.assign(
                     candidates.size() + 1,
                     vector<bool>(target + 1, false)
                    );

        // Positive candidates larger than target cannot appear in an answer.
        candi.clear();
        for (auto candidate: candidates) {
            if (candidate <= target) {
                candi.push_back(candidate);
            }
        }


        // Filtering can leave zero candidates. This by-value return copies the cached result.
        return find(candi.size(), target);
    }
};

int main() {
    Solution sol;
    vector<int> inputs[] = {
        {2, 3, 6, 7},
        {2, 3, 5},
        {2}
    };
    int targets[] = {7, 8, 1};

    // Expected: [[2,2,3],[7]], [[2,2,2,2],[2,3,3],[3,5]], [].
    for (int i = 0; i < 3; i++) {
        vector<vector<int>> result = sol.combinationSum(inputs[i], targets[i]);
        printf("Example %d: [", i + 1);
        for (int j = 0; j < static_cast<int>(result.size()); j++) {
            if (j > 0) printf(",");
            printf("[");
            for (int k = 0; k < static_cast<int>(result[j].size()); k++) {
                if (k > 0) printf(",");
                printf("%d", result[j][k]);
            }
            printf("]");
        }
        printf("]\n");
    }

    return 0;
}
