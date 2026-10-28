/*
 * Problem Link: https://leetcode.cn/problems/3sum/
 * Problem Name: 15. 3Sum
 * Difficulty: Medium
 * Problem Tags: array, sorting, two pointers
 *
 * Submission Record:
 * Approach: Sort + two-pointer search with duplicate-value skipping
 * Language: C++
 * Status: Accepted
 * Submitted At: N/A
 * Runtime: 59 ms (beats 40.76%)
 * Memory: 28.42 MB (beats 75.59%)
 * Submission Link: N/A
 * Recorded On: 2026-10-28
 * Record Source: User-provided accepted-submission screenshot
 *
 * Problem Description:
 * Given an integer array nums, return all triplets [nums[i], nums[j], nums[k]]
 * whose sum is zero, with i, j, and k pairwise distinct.
 * The result must not contain duplicate triplets.
 * The order of the triplets and the order of elements within each triplet
 * do not matter.
 *
 * Constraints:
 * 1. 3 <= nums.length <= 3000
 * 2. -100000 <= nums[i] <= 100000
 *
 * Example 1:
 * Input: nums = [-1,0,1,2,-1,-4]
 * Output: [[-1,-1,2],[-1,0,1]]
 * Explanation: These are the two distinct triplets whose sum is zero.
 *
 * Example 2:
 * Input: nums = [0,1,1]
 * Output: []
 * Explanation: The only possible triplet does not sum to zero.
 *
 * Example 3:
 * Input: nums = [0,0,0]
 * Output: [[0,0,0]]
 * Explanation: The only possible triplet sums to zero.
 *
 * Note:
 * The local main() runs the user-provided regression case first, followed
 * by all three official examples, and prints actual and expected results.
 * The input vector is sorted in place.
 * The sentinel value 1000000 lies outside the allowed input range.
 * Expected outputs are shown in one valid order; other orders are allowed.
 *
 * Approach:
 * Sort nums in ascending order. For each distinct first value l at index li,
 * search the suffix using mi = li + 1 and ri = nums.size() - 1.
 * If nums[mi] + nums[ri] is less than -l, advance mi; if it is greater,
 * decrease ri. Sorted order makes these moves safe: the discarded value
 * cannot form a solution with any remaining value at the opposite pointer.
 * On equality, append the triplet and move both pointers inward.
 * Each pointer move uses do-while to advance at least once and skip values
 * equal to the value just processed, while stopping when the pointers meet.
 * Skip repeated first values as well, advancing li before continue so that
 * the outer loop always progresses. These skips avoid duplicate triplets.
 *
 * Complexity:
 * Let n be nums.size() and R the number of returned triplets. Sorting takes
 * O(n log n) time. For each fixed first value, mi only increases and ri only
 * decreases, so all inner iterations and duplicate skips take O(n) time
 * in total. Across at most n first positions, worst-case time is O(n^2).
 * The pointer scan uses O(1) auxiliary space. Assuming the usual std::sort
 * implementation with O(log n) stack space, auxiliary space excluding the
 * output is O(log n); the C++ standard does not mandate this space bound.
 * Including the R fixed-size triplets, total extra space is O(log n + R).
 */

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        auto cmp = [](const int a, const int b) {
            return a < b;
        };

        sort(nums.begin(), nums.end(), cmp);

        vector<vector<int>> results;
        int l, m, r;
        // This sentinel cannot equal any valid input value.
        l = m = r = 1000000;

        int li = 0;
        while (li < nums.size() - 2) {
            // Skip duplicate first values, but still advance the outer index.
            if (nums[li] == l) {
                li++;
                m = r = 1000000;
                continue;
            }
            l = nums[li];

            int mi = li + 1;
            int ri = nums.size() - 1;
            // All triplets here use three distinct, increasing indices.
            while (mi < ri) {
                r = nums[ri];
                m = nums[mi];

                if (r + m == -l) {
                    results.push_back({l, m, r});
                    // Advance both pointers past the values in the recorded triplet.
                    do {
                        ++mi;
                    }while (mi < ri && nums[mi] == m);
                    do {
                        --ri;
                    }while (mi < ri && nums[ri] == r);
                }else if ( r + m < -l) {
                    // The sum is too small; try a larger middle value.
                    do {
                        ++mi;
                    }while (mi < ri && nums[mi] == m);
                }else if (r + m > -l) {
                    // The sum is too large; try a smaller right value.
                    do {
                        --ri;
                    }while (mi < ri && nums[ri] == r);
                }
            }

            li++;
            m = r = 1000000;
        }

        return results;
    }
};

void printTriplets(const vector<vector<int>>& triplets) {
    printf("[");
    for (size_t i = 0; i < triplets.size(); i++) {
        if (i > 0) printf(",");
        printf("[");
        for (size_t j = 0; j < triplets[i].size(); j++) {
            if (j > 0) printf(",");
            printf("%d", triplets[i][j]);
        }
        printf("]");
    }
    printf("]\n");
}

int main() {
    Solution sol;
    vector<int> inputs[] = {
        {-100, -70, -60, 110, 120, 130, 160},
        {-1, 0, 1, 2, -1, -4},
        {0, 1, 1},
        {0, 0, 0}
    };
    const char* expected[] = {
        "[[-100,-60,160],[-70,-60,130]]",
        "[[-1,-1,2],[-1,0,1]]",
        "[]",
        "[[0,0,0]]"
    };

    for (int i = 0; i < 4; i++) {
        printf("Example %d: ", i + 1);
        printTriplets(sol.threeSum(inputs[i]));
        printf("Expected: %s\n", expected[i]);
    }

    return 0;
}
