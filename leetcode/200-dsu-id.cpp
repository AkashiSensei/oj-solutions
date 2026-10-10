/*
 * Problem Link: https://leetcode.cn/problems/number-of-islands/
 * Problem Name: 200. Number of Islands
 * Difficulty: Medium
 * Problem Tags: array, depth-first search, breadth-first search,
 * union find, matrix
 *
 * Submission Record:
 * Approach: Union-find by size on adjacent land, coordinates packed into one index
 * Language: C++
 * Status: Accepted
 * Submitted At: N/A
 * Runtime: 30 ms (beats 48.88%)
 * Memory: 17.54 MB (beats 24.50%)
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

using namespace std;

struct Dsu {
    int parent;
    int size;
};

int id(int x, int y, int n) {
    return x * n + y;
}

int dsu_find(vector<Dsu> *dsu, int v) {
    if ((*dsu)[v].parent != v) {
        (*dsu)[v].parent = dsu_find(dsu, (*dsu)[v].parent);
    }
    return (*dsu)[v].parent;
}

bool dsu_merge(vector<Dsu> *dsu, int a, int b) {
    int p1 = dsu_find(dsu, a);
    int p2 = dsu_find(dsu, b);

    if (p1 == p2) return false;

    if ((*dsu)[p1].size < (*dsu)[p2].size) {
        (*dsu)[p1].parent = p2;
        (*dsu)[p2].size += (*dsu)[p1].size;
    } else {
        (*dsu)[p2].parent = p1;
        (*dsu)[p1].size += (*dsu)[p2].size;
    }

    return true;
}

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int cnt = 0;
        int n = grid[0].size();
        vector<Dsu> dsu(grid.size() * n, {0, 1});

        for (int x = 0; x < grid.size(); x++) {
            for (int y = 0; y < n; y++) {
                if (grid[x][y] == '1') {
                    cnt++;

                    int v = id(x, y, n);
                    dsu[v].parent = v;

                    if (x > 0 && grid[x - 1][y] == '1' && dsu_merge(&dsu, v, id(x - 1, y, n))) cnt--;
                    if (y > 0 && grid[x][y - 1] == '1' && dsu_merge(&dsu, v, id(x, y - 1, n))) cnt--;
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
