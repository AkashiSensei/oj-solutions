/*
 * Problem Link: https://leetcode.cn/problems/combination-sum/
 * Problem Name: 39. Combination Sum
 * Difficulty: Medium
 * Problem Tags: array, backtracking, depth-first search
 *
 * Submission Record:
 * Approach: DFS backtracking with nondecreasing candidate indices
 * Language: C++
 * Status: Accepted
 * Submitted At: N/A
 * Runtime: 3 ms (beats 63.74%)
 * Memory: 14.44 MB (beats 28.77%)
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
 * Input candidates is not modified. Candidates retain their original order;
 * nondecreasing candidate indices prevent duplicate permutations without sorting.
 * Member vectors are cleared on each call; clear() may retain allocated capacity.
 * The public by-value return copies results because it is a member lvalue.
 *
 * Approach:
 * Filter out candidates larger than target, then explore with one shared path.
 * dfs(ca_start, tar) considers only candidate indices at least ca_start.
 * On an exact fill, copy path into results and append the final candidate.
 * Otherwise, recurse with the same index i to allow reuse of that candidate,
 * then pop the chosen value to restore path before exploring another branch.
 * Only remainders greater than one are explored: every candidate is at least
 * two, so a remainder of one cannot be completed. Larger candidates are skipped
 * without breaking the loop because the input is not sorted.
 *
 * Complexity:
 * Let N be the original candidate count, n the filtered count, T the target,
 * R the answer count, and L = floor(T / min(candi)) when n > 0 (otherwise zero).
 * Filtering takes O(N). Recursion depth and path length are O(L).
 * For n >= 2, ignoring index and sum pruning gives O(n^L) recursion nodes.
 * Each node scans at most n candidates, yielding the loose O(n^(L + 1)) bound.
 * Collecting R answers of length at most L costs O(R*L), including amortized
 * vector growth. Returning the member results copies the answers once more,
 * which is still O(R*L). Total time is O(N + n^(L + 1) + R*L) for n >= 2.
 * For n = 1, the search is a chain and time is O(N + L + R*L); for n = 0,
 * only filtering and an empty DFS call remain, taking O(N).
 * For a fresh invocation, space is O(n + L + R*L): filtered candidates,
 * shared path, recursion stack, and the member-held answers. Excluding answer
 * storage, search workspace is O(n + L). The returned copy adds O(R*L) peak
 * space without changing the bound. The O(L) term still matters when R = 0.
 * Reusing the object can retain capacity allocated by earlier calls.
 */

#include <cstdio>
#include <vector>

using namespace std;

class Solution {
private:
    // Shared partial combination; each recursive choice is undone after returning.
    vector<int> path;
    vector<int> candi;
    vector<vector<int>> results;

    void dfs(int ca_start, int tar) {
        // Nondecreasing indices give each combination a unique selection order.
        for (int i = ca_start; i < candi.size(); i++) {
            if (tar - candi[i] == 0) {
                // Copy only a completed combination, rather than intermediate states.
                results.push_back(path);
                results.back().push_back(candi[i]);
                continue;
            }

            // All candidates are at least two, so a remainder of one is impossible.
            if (tar - candi[i] > 1) {
                path.push_back(candi[i]);
                // Keeping i allows the current candidate to be selected again.
                dfs(i, tar - candi[i]);
                path.pop_back();  // Restore the path for the next branch.
            }
        }
    }

public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        // Reset logical state so repeated calls on the same object stay independent.
        path.clear();
        results.clear();
        candi.clear();
        for (auto candidate: candidates)
            if (candidate <= target)
                candi.push_back(candidate);

        dfs(0, target);

        // Returning a member lvalue by value copies the final answer list.
        return results;
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
