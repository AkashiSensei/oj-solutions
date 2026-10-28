/*
 * Problem Link: https://leetcode.cn/problems/jump-game/
 * Problem Name: 55. Jump Game
 * Difficulty: Medium
 * Problem Tags: array, greedy
 *
 * Submission Record:
 * Approach: Greedy forward scan tracking the farthest reachable index
 * Language: C++
 * Status: Accepted
 * Submitted At: N/A
 * Runtime: 0 ms (beats 100.00%)
 * Memory: 51.21 MB (beats 56.81%)
 * Submission Link: N/A
 * Recorded On: 2026-10-28
 * Record Source: User-provided accepted-submission screenshot
 *
 * Problem Description:
 * Given a non-negative integer array nums, you are initially positioned
 * at the first index. Each element represents the maximum number of
 * positions you can jump forward from that index.
 * Return true if you can reach the last index, or false otherwise.
 * A jump may be shorter than the maximum length at the current position.
 *
 * Constraints:
 * 1. 1 <= nums.length <= 10000
 * 2. 0 <= nums[i] <= 100000
 *
 * Example 1:
 * Input: nums = [2,3,1,1,4]
 * Output: true
 * Explanation: Jump 1 step from index 0 to index 1, then jump 3 steps
 * from index 1 to the last index.
 *
 * Example 2:
 * Input: nums = [3,2,1,0,4]
 * Output: false
 * Explanation: Index 3 cannot be bypassed on the way to the last index,
 * and its maximum jump length is zero.
 *
 * Note:
 * The local main() contains both official examples.
 * The input vector is not modified.
 * A single-element array is already at the destination.
 *
 * Approach:
 * Maintain farest, the farthest index reachable from the positions scanned
 * so far. Because a jump can be shorter than its maximum, every index
 * between zero and this boundary is reachable as well.
 * Scan indices in increasing order while i <= farest. At each reachable
 * position, extend the boundary with i + nums[i] if possible. Return true
 * immediately when the boundary reaches or passes the last index.
 * If scanning passes the boundary, no reachable position can extend it
 * further, so the last index is unreachable. The early success return
 * also ensures that the loop never accesses an index beyond the array.
 *
 * Complexity:
 * Let n be nums.size(). Each visited index is processed once with O(1)
 * work, giving O(n) worst-case time; an early return may take O(1) time.
 * Only a fixed number of scalar variables are used, so auxiliary space
 * is O(1). There is no recursion or input copy.
 */

#include <cstdio>
#include <vector>

using namespace std;

class Solution {
public:
    bool canJump(vector<int>& nums) {
        if (nums.size() == 1) return true;

        // All indices up to this boundary are reachable.
        int farest = 0;

        // Only reachable positions can contribute a longer jump.
        for (int i = 0; i <= farest; i++) {
            if (nums[i] + i > farest) {
                farest = nums[i] + i;
                // Stop before an extended boundary could take the scan out of bounds.
                if (farest >= nums.size() - 1) return true;
            }
        }

        // The scan exhausted the reachable prefix without reaching the destination.
        return false;
    }
};

int main() {
    Solution sol;
    vector<int> inputs[] = {
        {2, 3, 1, 1, 4},
        {3, 2, 1, 0, 4}
    };

    // Expected outputs: true, false.
    for (int i = 0; i < 2; i++) {
        printf("Example %d: %s\n", i + 1,
               sol.canJump(inputs[i]) ? "true" : "false");
    }

    return 0;
}
