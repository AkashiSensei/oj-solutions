/*
 * Problem Link: https://leetcode.cn/problems/number-of-islands/
 * Problem Name: 200. Number of Islands
 * Difficulty: Medium
 * Problem Tags: array, depth-first search, breadth-first search,
 * union find, matrix
 *
 * Submission Record:
 * Approach: Union-find by size on adjacent land
 * Language: C++
 * Status: Accepted
 * Submitted At: N/A
 * Runtime: 30 ms (beats 48.88%)
 * Memory: 18.55 MB (beats 19.61%)
 * Submission Link:
 * N/A
 * Recorded On: 2026-10-10
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

#include <cstdio>
#include <vector>
#include <utility>

using namespace std;
using Node = pair<int, int>;

struct Dsu {
    Node parent;
    int size;
};

Node dsu_find(vector<vector<Dsu>> *dsu, Node n) {
    if ((*dsu)[n.first][n.second].parent != n) {
        (*dsu)[n.first][n.second].parent = dsu_find(dsu, (*dsu)[n.first][n.second].parent);
    }
    return (*dsu)[n.first][n.second].parent;
}

bool dsu_merge(vector<vector<Dsu>> *dsu, Node n1, Node n2) {
    Node p1 = dsu_find(dsu, n1);
    Node p2 = dsu_find(dsu, n2);

    if (p1 == p2) return false;

    if ((*dsu)[p1.first][p1.second].size < (*dsu)[p2.first][p2.second].size) {
        (*dsu)[p1.first][p1.second].parent = p2;
        (*dsu)[p2.first][p2.second].size += (*dsu)[p1.first][p1.second].size;
    }else {
        (*dsu)[p2.first][p2.second].parent = p1;
        (*dsu)[p1.first][p1.second].size += (*dsu)[p2.first][p2.second].size;
    }

    return true;
}

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int cnt = 0;
        vector<vector<Dsu>> dsu(grid.size(), vector<Dsu>(grid[0].size(),{{0, 0}, 1}));

        for (int x = 0; x < grid.size(); x++) {
            for (int y = 0; y < grid[0].size(); y++) {
                if (grid[x][y] == '1') {
                    cnt++;

                    Node n = {x, y};
                    dsu[x][y].parent = n;

                    if (x > 0 && grid[x-1][y] == '1' && dsu_merge(&dsu, n, {x-1, y})) cnt--;
                    if (y > 0 && grid[x][y-1] == '1' && dsu_merge(&dsu, n, {x, y-1})) cnt--;
                }
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
