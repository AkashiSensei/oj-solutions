/*
 * Problem Link: https://leetcode.cn/problems/top-k-frequent-elements/
 * Problem Name: 347. Top K Frequent Elements
 * Difficulty: Medium
 * Problem Tags: array, hash table, heap (priority queue)
 *
 * Submission Record:
 * Approach: Hash-table frequency counting + size-k min heap
 * Language: C++
 * Status: Accepted
 * Submitted At: N/A
 * Runtime: 0 ms (beats 100.00%)
 * Memory: 17.75 MB (beats 46.00%)
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
 * The input vector is not modified; counters and heap state are local to each call.
 * Structured bindings in the map traversal require C++17 or later.
 *
 * Approach:
 * Count occurrences with unordered_map, then visit each distinct value once.
 * Keep at most k records in a min heap ordered by frequency. Fill it until
 * it has k elements; afterward, replace its top only for a larger frequency.
 * The heap top is the least frequent retained candidate, so the final heap
 * contains the k most frequent values. Pop those values into the answer.
 * Equal-frequency records have no guaranteed relative order.
 *
 * Complexity:
 * Let n be nums.size() and d the number of distinct input values.
 * The log k bounds below assume k >= 2; for k = 1, heap operations take O(1),
 * candidate processing takes O(d), and total average/amortized time is O(n).
 * Counting takes average/amortized O(n) time with unordered_map.
 * Scanning d records while maintaining a heap of at most k elements takes
 * O(d log k) time; extracting all k records takes O(k log k).
 * Since k <= d, total average/amortized time is O(n + d log k).
 * Hash collisions can increase counting to O(n*d) worst-case time, giving
 * O(n*d + d log k) worst-case total time.
 * Auxiliary space is O(d + k): O(d) hash entries and O(k) heap records,
 * excluding the O(k) returned answer. Since k <= d, this is also O(d).
 */

#include <cstdio>
#include <vector>
#include <queue>
#include <unordered_map>
#include <functional>
#include <utility>

using namespace std;

struct NumCnt {
    int num;
    int cnt;
};

struct NumCntCmp {
    bool operator()(const NumCnt& a, const NumCnt& b) const {
        // A larger count has lower priority, so the smallest count stays on top.
        return a.cnt > b.cnt;
    }
};

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> counting;
        priority_queue<NumCnt, vector<NumCnt>, NumCntCmp> pq;
        
        // Average/amortized O(n) counting time and O(d) hash-table storage.
        for (int i = 0; i < nums.size(); i++) {
            counting[nums[i]]++;
        }

        // O(d log k) time; the heap never contains more than k records.
        for (auto& [num, cnt]:counting) {
            if (pq.size() < k) pq.push({num, cnt});
            else if (cnt > pq.top().cnt) {
                pq.pop();
                pq.push({num, cnt});
            }
        }

        // O(k log k) extraction; answer order is unrestricted.
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
