/*
 * Problem Link: https://leetcode.cn/problems/kth-largest-element-in-an-array/
 * Problem Name: 215. Kth Largest Element in an Array
 * Difficulty: Medium
 * Problem Tags: array, divide and conquer, quickselect
 *
 * Submission Record:
 * Approach: Recursive three-way quickselect with a fixed first-element pivot
 * Language: C++
 * Status: Accepted
 * Submitted At: N/A
 * Runtime: 67 ms (beats 15.91%)
 * Memory: 67.70 MB (beats 46.33%)
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
 * Search the half-open interval [front, back) for an absolute, zero-based
 * descending rank k. Keep nums[front] as the fixed pivot during the scan.
 * Scan backward with l while maintaining three processed regions:
 * (l, m] contains greater values, (m, r] contains equal values, and
 * (r, back) contains smaller values. Equal values move to the middle;
 * smaller values move to the right through a three-position rotation.
 * Finally swap the pivot into m, producing [front, m) > pivot,
 * [m, r] == pivot, and [r + 1, back) < pivot.
 * If the target lies in [m, r], return immediately; otherwise recurse
 * only into the relevant strict-greater or strict-smaller region.
 *
 * Complexity:
 * A partition of s elements takes O(s) time and O(1) local extra space.
 * Equal values are excluded together, so an all-equal input finishes in
 * one O(n) scan with O(1) stack depth. Balanced shrinking intervals give
 * O(n) total time and O(log n) recursive stack space.
 * The pivot is still the first element, with no randomization. Repeated
 * extreme pivots on distinct values can shrink by one per call, yielding
 * O(n^2) worst-case time and O(n) worst-case recursive stack space.
 * The input is passed by reference; partitioning does not allocate arrays.
 */

#include <vector>
#include <cstdio>
#include <utility>

using namespace std;

class Solution {
private:
    // front <= k < back; k is an absolute descending-order index.
    int find3(vector<int>&nums, int front, int back, int k) {
        int l, m, r, tmp;
        l = m = r = back - 1;

        // O(back - front) scan; nums[front] remains unchanged as the pivot.
        for (; l > front; l--) {
            // O(1): extend the equal-value region to the left.
            if (nums[l] == nums[front]) {
                swap(nums[l], nums[m]);
                m--;
                continue;
            }

            // O(1): move a smaller value right while preserving both regions.
            if (nums[l] < nums[front]) {
                tmp = nums[l];
                nums[l] = nums[m];
                nums[m] = nums[r];
                nums[r] = tmp;
                m--;
                r--;
            }
        }

        // The equal-value block is now [m, r], inclusive.
        swap(nums[front], nums[m]);

        // Any rank in the equal block has the same answer; no more recursion.
        if (m <= k && k <= r) return nums[m];

        // Recurse into one side; fixed-pivot worst-case depth remains O(n).
        if (k < m) return find3(nums, front, m, k);
        else return find3(nums, r + 1, back, k);
    }

public:
    // Convert the 1-based kth-largest rank to a zero-based descending index.
    int findKthLargest(vector<int>& nums, int k) {
        return find3(nums, 0, nums.size(), k-1);
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
