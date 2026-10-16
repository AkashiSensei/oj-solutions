/*
 * Problem Link: https://leetcode.cn/problems/top-k-frequent-elements/
 * Problem Name: 347. Top K Frequent Elements
 * Difficulty: Medium
 * Problem Tags: array, counting, heap (priority queue)
 *
 * Submission Record:
 * Approach: Bounded-range frequency counting + max heap of distinct values
 * Language: C++
 * Status: Accepted
 * Submitted At: N/A
 * Runtime: 4 ms (beats 37.75%)
 * Memory: 19.90 MB (beats 5.04%)
 * Submission Link:
 * N/A
 * Recorded On: 2026-10-16
 * Record Source: User-provided accepted-submission screenshot
 *
 * Problem Description:
 * Given an integer array nums and an integer k, return the k distinct
 * elements that occur most frequently. The answer may be in any order.
 * The set of elements in the answer is guaranteed to be unique.
 *
 * Constraints:
 * 1. 1 <= nums.length <= 100000
 * 2. -10000 <= nums[i] <= 10000
 * 3. 1 <= k <= the number of distinct elements in nums
 *
 * Follow-up:
 * Design an algorithm faster than O(n log n), where n is nums.length.
 *
 * Example 1:
 * Input: nums = [1,1,1,2,2,3], k = 2
 * Output: [1,2]
 *
 * Example 2:
 * Input: nums = [1], k = 1
 * Output: [1]
 *
 * Example 3:
 * Input: nums = [1,2,1,2,1,2,3,1,3,2], k = 2
 * Output: [1,2]
 *
 * Note:
 * The local main() runs all three official examples directly.
 * Output order may differ from the examples and still be correct.
 * The input vector is not modified. Counting and heap state are local to each call.
 *
 * Approach:
 * Count values in a direct-address vector by adding 10000 to each value.
 * Scan all buckets and push only values with nonzero counts into a max heap.
 * The comparator prioritizes larger counts; pop k values to form the answer.
 * Values with equal counts have no guaranteed relative order.
 *
 * Complexity:
 * Let n be nums.size(), d the number of distinct values, and U = 20002.
 * The buffer has 20001 valid value buckets and one unused zero slot.
 * Initialization and scanning take O(U); counting takes O(n).
 * Inserting d records one by one takes O(d log(d + 1)); extracting k records
 * takes O(k log(d + 1)), with amortized O(k) answer-vector appends.
 * Total: O(n + U + (d + k) log(d + 1)), which simplifies to
 * O(n + U + d log(d + 1)) because k <= d.
 * Auxiliary space is O(U + d), excluding the O(k) returned answer.
 * Under the fixed problem value range, d <= 20001 and U is constant,
 * so time is O(n) and auxiliary space is O(1) with respect to n alone.
 */

#include <cstdio>
#include <vector>
#include <queue>
#include <unordered_map>
#include <functional>

using namespace std;

struct NumCnt{
    int num;
    int cnt;
};

struct NumCntCmp {
    bool operator()(const NumCnt& a, const NumCnt& b) const {
        // A smaller count has lower priority, so the heap top has the largest count.
        return a.cnt < b.cnt;
    }
};

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // O(U) initialization and storage; index 20001 remains unused.
        vector<int>counting(20002, 0);
        priority_queue<NumCnt, vector<NumCnt>, NumCntCmp> pq;

        // O(n): translate values in [-10000, 10000] to nonnegative bucket indices.
        for (int i = 0; i < nums.size(); i++ ) {
            counting[nums[i] + 10000]++;
        }

        // O(U) scan plus O(d log(d + 1)) for individual heap insertions.
        for (int i = 0; i < counting.size(); i++) {
            if (counting[i] != 0) pq.push({i - 10000, counting[i]});
        }

        // O(k log(d + 1)) extraction; the returned vector stores O(k) values.
        vector<int> results;
        for (int i = 0; i < k; i++) {
            results.push_back(pq.top().num);
            pq.pop();
        }

        return results;
    }

};

int main() {
    Solution sol;

    vector<int> inputs[] = {
        {1,1,1,2,2,3},
        {1},
        {1,2,1,2,1,2,3,1,3,2}
    };
    int ks[] = {2, 1, 2};

    // Expected outputs: [1,2], [1], [1,2]; element order does not matter.
    for (int i = 0; i < 3; i++) {
        vector<int> result = sol.topKFrequent(inputs[i], ks[i]);
        printf("Example %d: [", i + 1);
        for (int j = 0; j < result.size(); j++) {
            if (j > 0) printf(",");
            printf("%d", result[j]);
        }
        printf("]\n");
    }

    return 0;
}
