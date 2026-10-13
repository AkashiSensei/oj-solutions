/*
 * Problem Link: https://leetcode.cn/problems/validate-binary-search-tree/
 * Problem Name: 98. Validate Binary Search Tree
 * Difficulty: Medium
 * Problem Tags: tree, depth-first search, binary search tree, binary tree
 *
 * Submission Record:
 * Approach: Recursive DFS with inclusive integer bounds
 * Language: C++
 * Status: Accepted
 * Submitted At: N/A
 * Runtime: 0 ms (beats 100.00%)
 * Memory: 21.55 MB (beats 41.33%)
 * Submission Link:
 * N/A
 * Recorded On: 2026-10-13
 * Record Source: User-provided accepted-submission screenshot
 *
 * Problem Description:
 * Given the root of a binary tree, determine whether it is a valid binary
 * search tree (BST).
 * For every node, all values in its left subtree must be strictly smaller
 * than its value, and all values in its right subtree must be strictly
 * larger. Both subtrees must also be valid binary search trees.
 *
 * Input Specification (LeetCode):
 * 1. The tree contains between 1 and 10000 nodes.
 * 2. -2147483648 <= Node.val <= 2147483647
 *
 * Output Specification:
 * Return true if the tree is a valid BST; otherwise, return false.
 *
 * Example 1:
 * Input: root = [2,1,3]
 * Output: true
 *
 * Example 2:
 * Input: root = [5,1,4,null,null,3,6]
 * Output: false
 *
 * Note:
 * Input arrays describe trees in level order; null denotes a missing node.
 * The local main() constructs the two official examples directly.
 * TreeNode is defined here for local compilation; LeetCode provides it.
 * The problem guarantees a non-null root.
 *
 * Approach:
 * Pass an inclusive allowed interval [min, max] down the tree, preserving
 * constraints from all ancestors. Reject a node outside this interval.
 * The left subtree receives [min, node->val - 1]; the right subtree
 * receives [node->val + 1, max], so equal values are rejected.
 * At the minimum int value, any left child is invalid; at the maximum
 * int value, any right child is invalid. Short-circuit evaluation checks
 * these cases before subtracting or adding 1, avoiding signed overflow.
 * Initial bounds cover the full signed 32-bit range, computed using 1LL.
 * Only existing children are visited; the input tree is not modified.
 *
 * Complexity:
 * Let n be the node count and h be the tree height. Each visited node
 * takes O(1) local work and is visited at most once, giving O(n) worst-case
 * time. Recursive calls use O(h) auxiliary stack space: O(log n) for a
 * balanced tree and O(n) for a completely skewed tree. Invalid trees may
 * terminate early. The input tree storage is excluded from auxiliary space.
 */

#include <cstdio>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};


class Solution {
public:
    // O(1) work per node; the active recursive path uses O(h) stack space.
    bool isValid(TreeNode* node, int min, int max) {
        // The inclusive interval carries constraints from every ancestor.
        if (node->val < min || node->val > max) return false;

        // Reject an impossible left child before evaluating val - 1.
        if (node->left != nullptr && (node->val == -(1LL << 31) || !isValid(node->left, min, node->val - 1)))
            return false;

        // Reject an impossible right child before evaluating val + 1.
        if (node->right != nullptr && (node->val == (1LL << 31) - 1 || !isValid(node->right, node->val + 1, max)))
            return false;

        return true;
    }

    // O(n) worst-case time; start with the full signed 32-bit value range.
    bool isValidBST(TreeNode* root) {
        return isValid(root, -(1LL << 31), (1LL << 31) - 1);
    }
};

int main() {
    // Example 1: [2,1,3]
    //     2
    //    / ╲
    //   1   3
    TreeNode left1(1);
    TreeNode right1(3);
    TreeNode root1(2, &left1, &right1);

    // Example 2: [5,1,4,null,null,3,6]
    //     5
    //    / ╲
    //   1   4
    //      / ╲
    //     3   6
    TreeNode left2(1);
    TreeNode rightLeft2(3);
    TreeNode rightRight2(6);
    TreeNode right2(4, &rightLeft2, &rightRight2);
    TreeNode root2(5, &left2, &right2);

    Solution sol;

    // Expected: true
    printf("%s\n", sol.isValidBST(&root1) ? "true" : "false");
    // Expected: false
    printf("%s\n", sol.isValidBST(&root2) ? "true" : "false");

    return 0;
}
