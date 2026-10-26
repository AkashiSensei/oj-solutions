/*
 * Problem Link: https://leetcode.cn/problems/subarray-sum-equals-k/
 * Problem Name: 560. Subarray Sum Equals K
 * Difficulty: Medium
 * Problem Tags: array, hash table, prefix sum
 *
 * Submission Record:
 * Approach: Running prefix sum with hash-table frequency counting
 * Language: C++
 * Status: Accepted
 * Submitted At: N/A
 * Runtime: 55 ms (beats 34.67%)
 * Memory: 49.82 MB (beats 15.98%)
 * Submission Link: N/A
 * Recorded On: 2026-10-26
 * Record Source: User-provided accepted-submission screenshot
 *
 * Problem Description:
 * Given an integer array nums and an integer k, return the number of
 * subarrays whose sum equals k.
 * A subarray is a contiguous, nonempty sequence of elements within the array.
 *
 * Constraints:
 * 1. 1 <= nums.length <= 20000
 * 2. -1000 <= nums[i] <= 1000
 * 3. -10000000 <= k <= 10000000
 *
 * Example 1:
 * Input: nums = [1,1,1], k = 2
 * Output: 2
 *
 * Example 2:
 * Input: nums = [1,2,3], k = 3
 * Output: 2
 *
 * Note:
 * The local main() runs both official examples directly.
 * Elements may be negative, zero, or positive.
 * Input nums is not modified. All counters are local to each call.
 * operator[] inserts a zero-valued entry when a queried key does not exist;
 * the map may therefore contain keys that are not actual prefix sums yet.
 *
 * Approach:
 * Maintain the running prefix sum sums and frequencies of all earlier prefix
 * sums. A subarray ending at the current position sums to k exactly when its
 * earlier prefix sum equals sums - k. Add that frequency to result, then
 * increment the frequency of sums for subsequent positions.
 * Seed frequency zero with one occurrence for the empty prefix, allowing
 * subarrays starting at index zero to be counted. Query before incrementing
 * the current prefix to exclude an empty subarray, especially when k is zero.
 * Frequencies account for repeated prefix sums, including those caused by
 * negative values and zeros; prefix sums do not need to be monotonic.
 *
 * Complexity:
 * Let n be nums.size(). Each of n iterations performs two hash-table accesses.
 * With average O(1) lookup and amortized insertion costs, total time is
 * average/amortized O(n). Severe hash collisions can yield O(n^2) worst-case time.
 * At most two keys are inserted per iteration plus the initial zero key, so
 * auxiliary space is O(n), even with zero entries inserted by lookup via [].
 * No prefix array or recursive stack is needed.
 */

#include <cstdio>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        // Earlier prefix sum -> occurrence count; absent lookups also create zero entries.
        unordered_map<int, int> counting;
        int sums = 0;
        int result = 0;

        // The empty prefix precedes the first element and has sum zero.
        counting[0]++;

        for (int i = 0; i < nums.size(); i++) {
            sums += nums[i];
            // Match earlier prefixes before recording the current one.
            result += counting[sums - k];
            counting[sums]++;  // Make this prefix available to later endpoints.
        }

        return result;
    }
};

int main() {
    Solution sol;
    vector<int> inputs[] = {
        {1, 1, 1},
        {1, 2, 3}
    };
    int ks[] = {2, 3};

    // Expected outputs: 2, 2.
    for (int i = 0; i < 2; i++) {
        printf("Example %d: %d\n", i + 1, sol.subarraySum(inputs[i], ks[i]));
    }

    return 0;
}
