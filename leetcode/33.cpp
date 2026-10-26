/*
 * Problem Link: https://leetcode.cn/problems/search-in-rotated-sorted-array/
 * Problem Name: 33. Search in Rotated Sorted Array
 * Difficulty: Medium
 * Problem Tags: array, binary search
 *
 * Submission Record:
 * Approach: lower_bound with a pivot-based virtual ordering
 * Language: C++
 * Status: Accepted
 * Submitted At: N/A
 * Runtime: 0 ms (beats 100.00%)
 * Memory: 15.04 MB (beats 20.19%)
 * Submission Link: N/A
 * Recorded On: 2026-10-26
 * Record Source: User-provided accepted-submission screenshot
 *
 * Problem Description:
 * An ascending array of distinct integers has been left-rotated at an unknown
 * index k, where 0 <= k < nums.length. Its resulting order is
 * [nums[k], ..., nums[n-1], nums[0], ..., nums[k-1]].
 * Given the rotated array and target, return the target's index, or -1 if absent.
 * Your algorithm must run in O(log n) time.
 *
 * Constraints:
 * 1. 1 <= nums.length <= 5000
 * 2. -10000 <= nums[i] <= 10000
 * 3. All elements in nums are distinct.
 * 4. nums is a rotation of an ascending array; k may be zero.
 * 5. -10000 <= target <= 10000
 *
 * Example 1:
 * Input: nums = [4,5,6,7,0,1,2], target = 0
 * Output: 4
 *
 * Example 2:
 * Input: nums = [4,5,6,7,0,1,2], target = 3
 * Output: -1
 *
 * Example 3:
 * Input: nums = [1], target = 0
 * Output: -1
 *
 * Note:
 * The local main() runs all three official examples directly.
 * Return an index in the supplied rotated array.
 * The input vector is not modified or copied. Only comparison arguments and
 * the local target value are transformed; the returned index uses original order.
 * The offset and restoration threshold rely on the stated [-10000, 10000]
 * value bounds. Shifted keys lie in [90000, 110000], above all unshifted values.
 *
 * Approach:
 * Let pivot be nums[0]. Values at least pivot form the initial ascending run;
 * values below pivot form the second ascending run. Map second-run values to
 * value + 100000, creating a strictly increasing sequence of virtual keys.
 * Apply the same mapping to target. Capture pivot by value in the comparator,
 * which maps its arguments before comparing them. A pre-shifted target is above
 * pivot and therefore is not shifted again inside the comparator.
 * Use lower_bound to locate the first virtual key not less than the target key.
 * Restore the original target using threshold 50000, then check end() and exact
 * equality before converting the iterator to an index. A lower-bound position
 * alone does not imply that target exists.
 *
 * Complexity:
 * Let n be nums.size(). Each comparison performs O(1) work, and vector iterators
 * support O(1) distance calculations and midpoint jumps. lower_bound uses
 * O(log n) comparisons and iterations, so total time is O(log n).
 * The comparator captures one integer, and the algorithm maintains only a fixed
 * number of local values and iterators. Auxiliary space is O(1); no transformed
 * array is materialized and the iterative binary search needs no recursion stack.
 */

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        // Nonempty input is guaranteed; pivot separates the two ascending runs.
        int pivot = nums[0];
        // Shift a second-run target into the same virtual key range as its elements.
        if (target < pivot) {
            target += 100000;
        }

        // Compare virtual keys without changing the stored array elements.
        auto cmp = [pivot](int a, int b) {
            if (a < pivot) a += 100000;
            if (b < pivot) b += 100000;
            return a < b;
        };

        // Find the first element whose virtual key is not before the target key.
        auto lb_it = lower_bound(nums.begin(),
                                 nums.end(),
                                 target,
                                 cmp
                                );

        // The disjoint value ranges make this test identify a shifted target.
        if (target >= 50000) target -= 100000;

        // Check end() before dereferencing, then verify the original value matches.
        if (lb_it == nums.end() || *lb_it != target) return -1;
        return lb_it - nums.begin();


    }
};

int main() {
    Solution sol;
    vector<int> inputs[] = {
        {4, 5, 6, 7, 0, 1, 2},
        {4, 5, 6, 7, 0, 1, 2},
        {1}
    };
    int targets[] = {0, 3, 0};

    // Expected outputs: 4, -1, -1.
    for (int i = 0; i < 3; i++) {
        printf("Example %d: %d\n", i + 1, sol.search(inputs[i], targets[i]));
    }

    return 0;
}
