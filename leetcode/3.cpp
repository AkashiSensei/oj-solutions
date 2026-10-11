/*
 * Problem Link: https://leetcode.cn/problems/longest-substring-without-repeating-characters/
 * Problem Name: 3. Longest Substring Without Repeating Characters
 * Difficulty: Medium
 * Problem Tags: hash table, string, sliding window
 *
 * Submission Record:
 * Approach: Sliding window with last-seen character indices
 * Language: C++
 * Status: Accepted
 * Submitted At: N/A
 * Runtime: 7 ms (beats 90.94%)
 * Memory: 18.45 MB (beats 67.25%)
 * Submission Link:
 * N/A
 * Recorded On: 2026-10-11
 * Record Source: User-provided accepted-submission screenshot
 *
 * Problem Description:
 * Given a string s, return the length of its longest contiguous substring
 * whose characters are all distinct. A subsequence may skip characters,
 * but a substring must be contiguous.
 *
 * Input Specification (LeetCode):
 * 1. 0 <= s.length <= 100000
 * 2. s consists of English letters, digits, symbols, and spaces.
 *
 * Output Specification:
 * Return a single integer: the longest length without repeated characters.
 *
 * Example Input:
 * s = "abcabcbb"
 * s = "bbbbb"
 * s = "pwwkew"
 *
 * Example Output:
 * 3
 * 1
 * 3
 *
 * Note:
 * "abc" is a valid answer for the first example, and "wke" for the third.
 * "pwke" is not a substring because its characters are not contiguous.
 * The local main() runs these three examples directly.
 *
 * Complexity:
 * Let n be the string length. One scan takes O(n) time, with O(1) work
 * per character. The 128-entry ASCII lookup table uses O(1) auxiliary space.
 * The parameter is passed by value: calls with an lvalue string, as in
 * main(), also copy O(n) characters and use O(n) space for that copy.
 * The index table reports auxiliary space excluding this input copy.
 */

#include <string>
#include <cstring>
#include <algorithm>
#include <cstdio>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // O(128) = O(1) space and initialization time for the ASCII table.
        int lastIdx[128];
        memset(lastIdx, 0xff, sizeof(lastIdx));

        int max = 0;
        // lastOkIdx is the excluded left boundary; the window is (lastOkIdx, i].
        int lastOkIdx = -1, lastC;
        int len;
        
        // O(n) total: process each character once with O(1) lookup and updates.
        for (int i = 0; i < s.size(); i++){
            lastC = lastIdx[(int)(s[i])];
            // Exclude a repeated character inside the window; never move left.
            if (lastC > lastOkIdx) lastOkIdx = lastC;

            // The current window has i - lastOkIdx distinct characters.
            if (i - lastOkIdx > max) max = i - lastOkIdx;

            // Save the latest occurrence for subsequent characters.
            lastIdx[(int)(s[i])] = i;
        }

        return max;
    }
};

int main() {
    string s1 = "abcabcbb";
    string s2 = "bbbbb";
    string s3 = "pwwkew";

    Solution sol;

    printf("%d\n%d\n%d\n", 
           sol.lengthOfLongestSubstring(s1),
           sol.lengthOfLongestSubstring(s2),
           sol.lengthOfLongestSubstring(s3)
          );

    return 0;
}
