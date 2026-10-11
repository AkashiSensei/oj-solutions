/*
 * Problem Link: https://leetcode.cn/problems/daily-temperatures/
 * Problem Name: 739. Daily Temperatures
 * Difficulty: Medium
 * Problem Tags: array, stack, monotonic stack
 *
 * Submission Record:
 * Approach: Monotonic stack of unresolved days and temperatures
 * Language: C++
 * Status: Accepted
 * Submitted At: N/A
 * Runtime: 27 ms (beats 55.13%)
 * Memory: 109.27 MB (beats 6.81%)
 * Submission Link:
 * N/A
 * Recorded On: 2026-10-11
 * Record Source: User-provided accepted-submission screenshot
 *
 * Problem Description:
 * Given an array temperatures representing daily temperatures, return an
 * array answer where answer[i] is the number of days until the first
 * warmer day after day i. If no warmer day exists, answer[i] is 0.
 *
 * Input Specification (LeetCode):
 * 1. 1 <= temperatures.length <= 100000
 * 2. 30 <= temperatures[i] <= 100
 *
 * Output Specification:
 * Return an integer array of the same length as temperatures.
 *
 * Example 1:
 * Input: temperatures = [73,74,75,71,69,72,76,73]
 * Output: [1,1,4,2,1,1,0,0]
 *
 * Example 2:
 * Input: temperatures = [30,40,50,60]
 * Output: [1,1,1,0]
 *
 * Example 3:
 * Input: temperatures = [30,60,90]
 * Output: [1,1,0]
 *
 * Note:
 * A warmer day must have a strictly higher temperature.
 * The local main() runs the three examples directly.
 *
 * Approach:
 * Keep unresolved days in a stack whose temperatures are non-increasing
 * from bottom to top. A strictly warmer day resolves entries at the top;
 * their answers are the differences between the current and stored days.
 * Entries never resolved retain the initial answer of 0.
 *
 * Complexity:
 * Let n be temperatures.size(). Initializing the answer takes O(n) time.
 * This implementation creates n + 1 stack entries: one initial seed and
 * one push per loop iteration. Each entry is popped at most once, so the
 * entire scan takes O(n) time despite the nested while loop.
 * The stack uses O(n) auxiliary space in the worst case. The returned
 * answer uses another O(n) space; the input is passed by reference.
 */

#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

struct DT {
    int day;
    int tem;
};

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        // O(n) time and output space; days without a warmer successor stay 0.
        vector<int> after(temperatures.size(), 0);

        // O(n) auxiliary space for unresolved days in the worst case.
        stack<DT> less;
        less.push({0, temperatures[0]});

        DT dt;

        // O(n) total pushes, including the initial seed outside the loop.
        for (int i = 0; i < temperatures.size(); i++) {
            // O(n) total pops across all iterations; equal temperatures do not resolve a day.
            while (!less.empty() && temperatures[i] > less.top().tem) {
                dt = less.top();
                // This is the first strictly warmer day for the popped entry.
                after[dt.day] = i - dt.day;
                less.pop();
            }
            // Restore non-increasing temperatures from bottom to top.
            less.push({i, temperatures[i]});
        }

        return after;
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
    vector<int> input1 = {73, 74, 75, 71, 69, 72, 76, 73};
    vector<int> input2 = {30, 40, 50, 60};
    vector<int> input3 = {30, 60, 90};

    Solution sol;

    // Expected: [1,1,4,2,1,1,0,0]
    printVector(sol.dailyTemperatures(input1));
    // Expected: [1,1,1,0]
    printVector(sol.dailyTemperatures(input2));
    // Expected: [1,1,0]
    printVector(sol.dailyTemperatures(input3));

    return 0;
}
