/*
 * Problem Link: https://leetcode.cn/problems/kth-largest-element-in-an-array/
 * Problem Name: 215. Kth Largest Element in an Array
 * Difficulty: Medium
 * Problem Tags: array, divide and conquer, quickselect
 *
 * Submission Record:
 * Approach: Recursive quickselect with a fixed first-element pivot
 * Language: C++
 * Status: Accepted
 * Submitted At: N/A
 * Runtime: 2917 ms (beats 5.01%)
 * Memory: 67.51 MB (beats 83.84%)
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
 * This implementation rearranges nums in place.
 *
 * Approach:
 * Search the half-open interval [start, end) for an absolute, zero-based
 * descending rank k. Choose nums[start] as the pivot and scan backward,
 * moving values strictly smaller than the pivot to the right.
 * Place the pivot at r: values in [start, r) are greater than or equal
 * to it, and values in [r + 1, end) are strictly smaller.
 * Return when r equals the target; otherwise recurse only into the side
 * containing that target. Equal values remain on the left side.
 *
 * Complexity:
 * A partition of m elements takes O(m) time and O(1) local extra space.
 * With balanced shrinking intervals, total time is O(n) and recursive
 * depth is O(log n). Standard average O(n) quickselect analysis assumes
 * suitable pivot-rank distributions, e.g. distinct keys in random order.
 * This implementation uses a fixed pivot and provides no randomized
 * expected-time guarantee. Repeated extreme pivots, or all-equal values
 * with a target near the start, can shrink the interval by only one each
 * time: worst-case time is O(n^2) and recursion stack space is O(n).
 * The input vector is passed by reference, so its elements are not copied.
 */

#include <vector>
#include <cstdio>
#include <utility>

using namespace std;

class Solution {
private:
    int splitFindK(vector<int>& nums, int start, int end, int k) {
        // start <= k < end; k is an absolute descending-order index.
        // O(1) pivot choice; its rank can be highly unbalanced.
        int pivot = nums[start];
        int l, r;

        // O(end - start) scan; swaps move strictly smaller values right.
        for (l = end-1, r = end-1; l > start; l--) {
            if (nums[l] < pivot) {
                swap(nums[l], nums[r]);
                r--;
            }
        }

        // The pivot reaches its final descending rank within this interval.
        swap(nums[start], nums[r]);

        if (r == k) return nums[r];

        // Recurse into only one side; worst-case depth is O(n).
        if (k > r) return splitFindK(nums, r + 1, end, k);
        else return splitFindK(nums, start, r, k);
    }


public:
    // Convert the 1-based kth-largest rank to a zero-based descending index.
    int findKthLargest(vector<int>& nums, int k) {
        return splitFindK(nums, 0, nums.size(), k - 1);

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
