/*
 * Problem Link: https://leetcode.cn/problems/daily-temperatures/
 * Problem Name: 739. Daily Temperatures
 * Difficulty: Medium
 * Problem Tags: array, stack, monotonic stack
 *
 * Submission Record:
 * Approach: Array-backed monotonic stack of day indices
 * Language: C++
 * Status: Accepted
 * Submitted At: N/A
 * Runtime: 18 ms (beats 88.65%)
 * Memory: 101.01 MB (beats 84.77%)
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
 * Store unresolved day indices in a fixed global array; read each stored
 * day's temperature from the input array when comparing the stack top.
 * SP is the top index; -1 denotes an empty stack. Temperatures are
 * non-increasing from bottom to top. A strictly warmer day pops and
 * resolves earlier records, while equal temperatures remain unresolved.
 * Reset SP on every call so records from previous test cases are ignored.
 *
 * Complexity:
 * Let n be the input length and C = 100005 be the reserved stack capacity.
 * Initializing the answer takes O(n) time. Each day is pushed once and
 * popped at most once, so all stack operations together take O(n) time.
 * At most n stack entries are used. The fixed global buffer reserves
 * O(C) auxiliary storage regardless of n; the algorithm requires O(n)
 * stack capacity in the worst case. The returned answer uses O(n) space.
 * Resetting SP takes O(1) time and does not clear the entire buffer.
 * The input is passed by reference and is not copied.
 *
 */

#include <cstdio>
#include <vector>

using namespace std;

// O(C) reserved static storage, C = 100005; each entry stores only a day index.
int STACK[100005];
int SP = -1;

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        // O(1) logical reset: global state must not carry over between calls.
        SP = -1;
        // Alias the input vector without copying its elements.
        vector<int>& tems = temperatures;
        // O(n) initialization and output space; unresolved days retain 0.
        vector<int> after(tems.size(), 0);

        // O(n) total: each day is pushed once and popped at most once.
        for (int i = 0; i < tems.size(); i++ ) {
            // O(n) pops over the whole scan, not O(n) for each day.
            // Read the stored day first, then look up its temperature in the input.
            while (SP >= 0 && tems[STACK[SP]] < tems[i]) {
                // The current day is the first strictly warmer day for this entry.
                after[STACK[SP]] = i - STACK[SP];
                SP--;
            }
            // O(1) push; retain non-increasing temperatures from bottom to top.
            STACK[++SP] = i;
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
