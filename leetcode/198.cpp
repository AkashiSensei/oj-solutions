/*
 * Problem Link: https://leetcode.cn/problems/house-robber/
 * Problem Name: 198. House Robber
 * Difficulty: Medium
 * Problem Tags: array, dynamic programming
 *
 * Submission Record:
 * Approach: Dynamic programming with rolling states
 * Language: C++
 * Status: Accepted
 * Submitted At: 2026-10-09 15:35 (Asia/Shanghai)
 * Runtime: 0 ms (beats 100.00%)
 * Memory: 9.78 MB (beats 99.39%)
 * Submission Link:
 * https://leetcode.cn/problems/house-robber/submissions/753639575/
 * Recorded On: 2026-10-10
 *
 * Problem Description:
 * You are a robber planning to rob houses along a street. Each house
 * has some money. Adjacent houses share a security system: if two
 * adjacent houses are robbed on the same night, the system alarms.
 * Given an integer array of the money in each house, return the maximum
 * amount you can rob tonight without triggering the alarm.
 *
 * Input Specification:
 * The input is an integer array nums of length n:
 * 1. 1 <= n <= 100
 * 2. 0 <= nums[i] <= 400
 * nums[i] is the money in the i-th house.
 *
 * Output Specification:
 * Return a single integer: the maximum amount that can be robbed
 * without robbing two adjacent houses.
 *
 * Example Input:
 * nums = [1,2,3,1]
 * nums = [2,7,9,3,1]
 *
 * Example Output:
 * 4
 * 12
 *
 * Note:
 * In the first example, rob house 1 (money = 1) and house 3
 * (money = 3). The total is 1 + 3 = 4.
 * In the second example, rob house 1 (money = 2), house 3 (money = 9),
 * and house 5 (money = 1). The total is 2 + 9 + 1 = 12.
 */


#include <cstdio>
#include <vector>
#include <algorithm>


using namespace std;

class Solution {
public:
    int rob(vector<int>& nums) {
        int last, last2, maxnow;

        last2 = nums[0];
        if (nums.size() == 1) return last2;

        last = max(nums[1], last2);
        if (nums.size() == 2) return last;

        for (int i = 2; i < nums.size(); i++) {
            maxnow = max(last2 + nums[i], last);
            last2 = last;
            last = maxnow;
        }

        return maxnow;
    }

};

int main() {
    Solution sol;
    vector<int> input1 = {1, 2, 3, 1};
    vector<int> input2 = {2, 7, 9, 3, 1};

    printf("%d\n%d\n", sol.rob(input1), sol.rob(input2));

    return 0;
}

