/*
 * Problem Link: https://leetcode.cn/problems/merge-intervals/
 * Problem Name: 56. Merge Intervals
 * Difficulty: Medium
 * Problem Tags: array, sorting
 *
 * Submission Record:
 * Approach: Sort by start endpoint, then merge in a linear scan
 * Language: C++
 * Status: Accepted
 * Submitted At: N/A
 * Runtime: 3 ms (beats 92.61%)
 * Memory: 23.31 MB (beats 75.37%)
 * Submission Link: N/A
 * Recorded On: 2026-10-22
 * Record Source: User-provided accepted-submission screenshot
 *
 * Problem Description:
 * Each entry intervals[i] = [start, end] represents a closed interval.
 * Merge all overlapping intervals and return non-overlapping intervals
 * that cover exactly the same values as the input intervals.
 * Intervals sharing an endpoint are considered overlapping.
 *
 * Constraints:
 * 1. 1 <= intervals.length <= 10000
 * 2. intervals[i].length == 2
 * 3. 0 <= start <= end <= 10000
 *
 * Example 1:
 * Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
 * Output: [[1,6],[8,10],[15,18]]
 * Explanation: [1,3] and [2,6] overlap and merge into [1,6].
 *
 * Example 2:
 * Input: intervals = [[1,4],[4,5]]
 * Output: [[1,5]]
 * Explanation: The shared endpoint 4 makes these intervals overlap.
 *
 * Example 3:
 * Input: intervals = [[4,7],[1,4]]
 * Output: [[1,7]]
 * Explanation: [1,4] and [4,7] overlap at endpoint 4.
 *
 * Note:
 * The local main() runs all three official examples directly.
 * Sorting modifies the order of the input intervals in place.
 * The problem guarantees nonempty input, so initializing from intervals[0] is valid.
 * Equal-start intervals may appear in either order; taking the maximum end
 * correctly handles both ties and nested intervals.
 *
 * Approach:
 * Sort intervals by increasing start endpoint with a strict comparator.
 * Maintain the start and end of the current merged interval. If the next start
 * is greater than end, emit the current interval and start a new one. Otherwise,
 * extend end to the maximum of the two ends. Emit the last interval after scanning.
 * Closed intervals sharing an endpoint overlap; intervals separated by a gap
 * remain distinct, even when their integer endpoints differ by only one.
 *
 * Complexity:
 * Let n be the input interval count and k the number of returned intervals.
 * Sorting takes O(n log n) comparisons, each O(1); scanning and constructing
 * the output take amortized O(n) time, giving O(n log n) total time.
 * The scan uses O(1) workspace, excluding the O(k) returned vector.
 * Typical std::sort implementations use O(log n) auxiliary stack space,
 * giving O(log n) auxiliary space excluding output, or O(log n + k) including
 * output. The sorting workspace bound depends on the library implementation.
 */

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

// Compare starts only; const references avoid copying interval vectors.
bool ivCmp(const vector<int>& a, const vector<int>& b) {
    return a[0] < b[0];
}

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        // O(n log n): sorting ensures later intervals cannot start before this one.
        sort(intervals.begin(), intervals.end(), ivCmp);

        vector<vector<int>> results;
        int start, end;

        // Nonempty input is guaranteed by the problem.
        start = intervals[0][0];
        end = intervals[0][1];
        for (int i = 1; i < intervals.size(); i++) {
            // A strict gap finishes the current merged interval.
            if (intervals[i][0] > end) {
                results.push_back({start, end});
                start = intervals[i][0];
                end = intervals[i][1];
                continue;
            }

            // Overlapping or touching intervals extend the current right endpoint.
            end = max(intervals[i][1], end);
        }
        // The final merged interval has not yet been emitted by a gap.
        results.push_back({start, end});

        return results;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> inputs[] = {
        {{1, 3}, {2, 6}, {8, 10}, {15, 18}},
        {{1, 4}, {4, 5}},
        {{4, 7}, {1, 4}}
    };

    // Expected: [[1,6],[8,10],[15,18]], [[1,5]], [[1,7]].
    for (int i = 0; i < 3; i++) {
        vector<vector<int>> result = sol.merge(inputs[i]);
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
