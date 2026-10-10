/*
 * Problem Link: https://leetcode.cn/problems/number-of-islands/
 * Problem Name: 200. Number of Islands
 * Difficulty: Medium
 * Problem Tags: array, depth-first search, breadth-first search,
 * union find, matrix
 *
 * Problem Description:
 * Given an m x n grid containing '1' (land) and '0' (water), count
 * its islands. An island consists of land cells connected horizontally
 * or vertically. Assume water surrounds the outer edges of the grid.
 *
 * Input Specification (LeetCode):
 * The input is a two-dimensional character array grid:
 * 1. m == grid.length
 * 2. n == grid[i].length
 * 3. 1 <= m, n <= 300
 * 4. grid[i][j] is either '0' or '1'.
 *
 * Output Specification:
 * Return a single integer: the number of islands.
 *
 * Example Input:
 * grid = [
 *   ['1','1','1','1','0'],
 *   ['1','1','0','1','0'],
 *   ['1','1','0','0','0'],
 *   ['0','0','0','0','0']
 * ]
 * grid = [
 *   ['1','1','0','0','0'],
 *   ['1','1','0','0','0'],
 *   ['0','0','1','0','0'],
 *   ['0','0','0','1','1']
 * ]
 *
 * Example Output:
 * 1
 * 3
 *
 * Local ACM Practice Format (not specified by LeetCode):
 * Read m and n, then m strings of length n containing only 0 and 1.
 * Each run contains one test case. Print the island count.
 *
 * Local Example Input:
 * 4 5
 * 11000
 * 11000
 * 00100
 * 00011
 *
 * Local Example Output:
 * 3
 *
 * Note:
 * Diagonal neighbors are not connected.
 */

#include <set>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

void checkAndMove(int x, int y, set<pair<int, int>> * land, queue<pair<int, int>> * q) {
    // Erase by value: O(log(L + 1)); enqueue only unvisited land.
    if (land->erase({x, y}) == 0) return;
    // Queue push: O(1).
    q->push({x, y});
}

class Solution {
public:
    // m = rows, n = columns, L = total number of land cells.
    // Total time: O(m * n + L * log(L + 1)); extra space: O(L).
    int numIslands(vector<vector<char>>& grid) {
        // The set stores up to L coordinates: O(L) space.
        set<pair<int, int>> land;

        // Scan: O(m * n); L set insertions: O(L * log(L + 1)).
        for (int x = 0; x < grid.size(); x++) {
            for (int y = 0; y < grid[0].size(); y++) {
                if (grid[x][y] == '1') {
                    land.insert({x+1, y+1});
                }
            }
        }

        int cnt = 0;

        // Each land cell is enqueued once across all islands.
        while (!land.empty()) {
            cnt++;

            auto cell = *land.begin();
            // Remove the starting cell: O(log(L + 1)) per island.
            land.erase(cell);

            // Queue space: O(L) in the worst case.
            queue<pair<int, int>> q;
            q.push(cell);
            
            // O(L) iterations in total; queue front/pop are O(1).
            while (!q.empty()) {
                cell = q.front();
                q.pop();
                int x = cell.first;
                int y = cell.second;

                // Four set checks per cell: O(L * log(L + 1)) total.
                checkAndMove(x-1, y, &land, &q);
                checkAndMove(x+1, y, &land, &q);
                checkAndMove(x, y-1, &land, &q);
                checkAndMove(x, y+1, &land, &q);
            }
        }

        return cnt;
    }
};

int main() {
    Solution sol;

    vector<vector<char>> input1 = {
        {'1', '1', '1', '1', '0'},
        {'1', '1', '0', '1', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '0', '0', '0'}
    };

    vector<vector<char>> input2 = {
        {'1', '1', '0', '0', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '1', '0', '0'},
        {'0', '0', '0', '1', '1'}
    };

    printf("%d\n%d\n", sol.numIslands(input1), sol.numIslands(input2));

    return 0;

}
