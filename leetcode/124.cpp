/*
 * Problem Link: https://leetcode.cn/problems/binary-tree-maximum-path-sum/
 * Problem Name: 124. Binary Tree Maximum Path Sum
 * Difficulty: Hard
 * Problem Tags: binary tree, depth-first search, dynamic programming
 *
 * Submission Record:
 * Approach: Postorder DFS returning one-branch gains and tracking complete paths
 * Language: C++
 * Status: Accepted
 * Submitted At: N/A
 * Runtime: 0 ms (beats 100.00%)
 * Memory: 27.32 MB (beats 62.93%)
 * Submission Link: N/A
 * Recorded On: 2026-10-29
 * Record Source: User-provided accepted-submission screenshot
 *
 * Problem Description:
 * A path in a binary tree is a sequence of nodes in which each adjacent
 * pair is connected by an edge. A node may appear at most once in a path.
 * A path must contain at least one node and need not pass through the root.
 * Its endpoints need not be leaves.
 * The path sum is the sum of the values of all nodes on the path.
 * Given the root of a binary tree, return its maximum path sum.
 *
 * Constraints:
 * 1. The number of nodes is in [1, 30000].
 * 2. -1000 <= Node.val <= 1000
 *
 * Example 1:
 * Input: root = [1,2,3]
 * Output: 6
 * Explanation: The path 2 -> 1 -> 3 has sum 2 + 1 + 3 = 6.
 *
 * Example 2:
 * Input: root = [-10,9,20,null,null,15,7]
 * Output: 42
 * Explanation: The path 15 -> 20 -> 7 has sum 15 + 20 + 7 = 42.
 *
 * Note:
 * TreeNode is defined here for local compilation; LeetCode provides it.
 * The local main() constructs and runs both official examples directly.
 * All test nodes are local objects and must not be deleted or freed manually.
 * The input tree is non-empty under the problem constraints and is not modified.
 * The answer is reset on every public call, including repeated calls on one object.
 * The initial result -1000000 is below every possible answer: a single node
 * is a valid path and each node value is at least -1000.
 *
 * Approach:
 * Process each node after its children. maxNode(node) returns maxEnd, the
 * best downward path sum within this subtree with node as one endpoint.
 * Extend through at most one child so that the path can still connect to
 * the parent without branching. Missing children contribute zero, and
 * non-positive child gains are omitted.
 * Separately compute maxPath, the best path passing through node, using
 * both child gains when they are positive. This complete path may connect
 * the left and right sides, but is not returned for extension by a parent.
 * Update the global result at every node, then return only maxEnd.
 * Every valid path has a highest node where its two sides meet, so these
 * candidates cover the optimum even when it does not pass through root.
 * A path always includes its current node, so all-negative trees correctly
 * return the largest node value rather than an empty path with sum zero.
 *
 * Complexity:
 * Let n be the number of nodes and h the tree height. Each node is visited
 * once and performs O(1) work after its children, giving O(n) time.
 * The recursion stack contains O(h) calls, each with O(1) local state,
 * so auxiliary space is O(h): O(log n) for a balanced tree and O(n) for
 * a tree that degenerates into a chain. No memoization table is allocated.
 */

#include <cstdio>
#include <algorithm>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};

class Solution {
private:
    int result;
    int maxNode(TreeNode* node) {
        // Extendable path: node itself plus at most one downward branch.
        int maxEnd = node->val;
        // Complete path through node: both downward branches may be included.
        int maxPath = node->val;
        int l = 0, r = 0;

        if (node->left != nullptr) {
            l = maxNode(node->left);
        }
        if (node->right != nullptr) {
            r = maxNode(node->right);
        }

        // Keep only child contributions that increase the path sum.
        if (l > 0 && r > 0) {
            maxPath += l + r;
            maxEnd += max(l, r);
        }else if (l > 0) {
            maxPath += l;
            maxEnd += l;
        }else if (r > 0) {
            maxPath += r;
            maxEnd += r;
        }

        // A two-sided path is a final candidate, not an extendable return value.
        result = max(result, maxPath);
        return maxEnd;
    }

public:
    int maxPathSum(TreeNode* root) {
        // Reset below the smallest possible answer, including all-negative trees.
        result = -1000000;
        maxNode(root);
        return result;
    }
};

int main() {
    Solution sol;

    // Example 1: root = [1,2,3].
    // Root 1 has left child 2 and right child 3.
    TreeNode left1(2);
    TreeNode right1(3);
    TreeNode root1(1, &left1, &right1);

    printf("Example 1: %d\n", sol.maxPathSum(&root1));
    printf("Expected: 6\n");

    // Example 2: root = [-10,9,20,null,null,15,7].
    // Root -10 has left child 9 and right child 20.
    // Node 20 has left child 15 and right child 7.
    TreeNode left2(9);
    TreeNode node15(15);
    TreeNode node7(7);
    TreeNode right2(20, &node15, &node7);
    TreeNode root2(-10, &left2, &right2);

    printf("Example 2: %d\n", sol.maxPathSum(&root2));
    printf("Expected: 42\n");

    return 0;
}
