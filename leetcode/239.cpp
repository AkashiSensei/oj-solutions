/*
 * Problem Link: https://leetcode.cn/problems/sliding-window-maximum/
 * Problem Name: 239. Sliding Window Maximum
 * Difficulty: Hard
 * Problem Tags: array, sliding window, monotonic deque
 *
 * Submission Record:
 * Approach: Monotonic deque of candidate indices, with first-window initialization
 * Language: C++
 * Status: Accepted
 * Submitted At: N/A
 * Runtime: 39 ms (beats 33.28%)
 * Memory: 136.05 MB (beats 54.48%)
 * Submission Link: N/A
 * Recorded On: 2026-10-29
 * Record Source: User-provided accepted-submission screenshot
 *
 * Problem Description:
 * Given an integer array nums and a window of size k, move the window
 * from the left end of the array to the right end, one position at a time.
 * Return the maximum value in each window, in the order the windows appear.
 * Each window contains exactly k consecutive array elements.
 *
 * Constraints:
 * 1. 1 <= nums.length <= 100000
 * 2. -10000 <= nums[i] <= 10000
 * 3. 1 <= k <= nums.length
 *
 * Example 1:
 * Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
 * Output: [3,3,5,5,6,7]
 * Explanation: The six windows have maxima 3, 3, 5, 5, 6, and 7.
 *
 * Example 2:
 * Input: nums = [1], k = 1
 * Output: [1]
 *
 * Note:
 * The local main() contains both official examples and prints actual
 * and expected results.
 * The input vector is not modified; all state is local to each call.
 * Equal-valued candidates are retained because comparisons use strict >.
 *
 * Approach:
 * Store candidate indices in increasing index order, with their values in
 * non-increasing order. The front always identifies the window maximum.
 * First build the deque for indices [0, k - 1] and record its maximum.
 * Before inserting each new index, remove candidates from the back whose
 * values are strictly smaller: the new value is larger and expires later,
 * so those candidates can never become a future window maximum.
 * For each later window starting at i, remove the front if its index is
 * i - 1, then insert the new right endpoint i + k - 1 in the same way.
 * Only one index leaves per shift, and all candidates were valid for the
 * previous window, so a single equality check at the front is sufficient.
 * Equal values may coexist; older equal candidates expire in index order.
 * Record nums[q.front()] after each insertion.
 *
 * Complexity:
 * Let n be nums.size(). Each index is pushed once and popped at most once,
 * either from the back when dominated or from the front when expired.
 * Total deque operations are O(n), despite a single insertion possibly
 * removing O(k) candidates. With amortized O(1) vector append, total time
 * is O(n). The deque contains at most k indices, so auxiliary space is
 * O(k), excluding the n - k + 1 output values. Including output, total
 * extra space is O(k + n - k + 1) = O(n).
 */

#include <cstdio>
#include <vector>
#include <deque>

using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        // Increasing indices; corresponding values are non-increasing.
        deque<int> q;
        vector<int> results;

        // Build the first complete window separately.
        q.push_back(0);
        for (int i = 1; i < k; i++) {
            while (!q.empty() && nums[i] > nums[q.back()]) {
                q.pop_back();
            }
            q.push_back(i);
        }
        results.push_back(nums[q.front()]);

        for (int i = 1; i + k - 1 < nums.size(); i++) {
            // This is the only index that can have just expired.
            if (q.front() == i - 1) {
                q.pop_front();
            }

            // A larger incoming value permanently dominates smaller older ones.
            while (!q.empty() && nums[i + k - 1] > nums[q.back()]) {
                q.pop_back();
            }
            q.push_back(i + k - 1);

            results.push_back(nums[q.front()]);
        }

        return results;
    }
};

void printVector(const vector<int>& values) {
    printf("[");
    for (size_t i = 0; i < values.size(); ++i) {
        if (i > 0) printf(",");
        printf("%d", values[i]);
    }
    printf("]\n");
}

int main() {
    Solution sol;
    vector<int> inputs[] = {
        {1, 3, -1, -3, 5, 3, 6, 7},
        {1}
    };
    int windowSizes[] = {3, 1};
    vector<int> expected[] = {
        {3, 3, 5, 5, 6, 7},
        {1}
    };

    for (int i = 0; i < 2; ++i) {
        printf("Example %d: ", i + 1);
        printVector(sol.maxSlidingWindow(inputs[i], windowSizes[i]));
        printf("Expected: ");
        printVector(expected[i]);
    }

    return 0;
}
