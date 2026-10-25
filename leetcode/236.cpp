/*
 * Problem Link: https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/
 * Problem Name: 236. Lowest Common Ancestor of a Binary Tree
 * Difficulty: Medium
 * Problem Tags: tree, depth-first search, binary tree
 *
 * Submission Record:
 * Approach: Postorder DFS with boolean subtree-presence flags
 * Language: C++
 * Status: Accepted
 * Submitted At: N/A
 * Runtime: 79 ms (beats 27.59%)
 * Memory: 41.54 MB (beats 97.64%)
 * Submission Link: N/A
 * Recorded On: 2026-10-25
 * Record Source: User-provided accepted-submission screenshot
 *
 * Problem Description:
 * Given a binary tree and two distinct nodes p and q in that tree, return
 * their lowest common ancestor: the deepest node that is an ancestor of both.
 * A node is considered an ancestor of itself.
 * Return the actual node pointer, rather than its value or a newly created node.
 *
 * Constraints:
 * 1. The tree contains between 2 and 100000 nodes.
 * 2. -1000000000 <= Node.val <= 1000000000
 * 3. All node values are distinct.
 * 4. p != q, and both nodes exist in the tree.
 *
 * Example 1:
 * Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
 * Output: 3
 *
 * Example 2:
 * Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
 * Output: 5
 * Explanation: Node 5 is also an ancestor of itself.
 *
 * Example 3:
 * Input: root = [1,2], p = 1, q = 2
 * Output: 1
 *
 * Note:
 * TreeNode is defined here for local compilation; LeetCode provides it.
 * The local main() directly constructs the three official examples.
 * p and q point to existing nodes inside each example tree.
 * Example nodes have automatic storage duration; do not delete these pointers.
 * The tree is not modified and no new tree nodes are allocated.
 * Member state is reset for each public call, allowing the same object to be reused.
 *
 * Approach:
 * hasTarget(node) reports whether the subtree contains at least one target.
 * Process both children, then sum their boolean presence flags and the current
 * node's identity matches with p and q. Explicit bool-to-int casts produce 0 or 1.
 * A sum of two identifies the lowest common ancestor: either the targets occur
 * in separate child subtrees, or the current node is one target and a descendant
 * is the other. Store that existing node in parent.
 * Above this node, both targets are summarized by one true child flag, so higher
 * ancestors do not overwrite the answer. The returned flag reports presence,
 * rather than the total number of target nodes in the subtree.
 * Arithmetic addition evaluates both child calls; traversal continues even after
 * the answer has been identified, so the entire tree is visited.
 *
 * Complexity:
 * Let n be the node count and h the tree height. Every node is visited once and
 * performs O(1) local work, giving O(n) time. Auxiliary space is O(h) for the
 * recursive stack plus O(1) member pointers. This is O(log n) for balanced trees
 * and O(n) for a skewed tree. Input tree storage is excluded; the output is one
 * pointer to an existing node.
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
private:
    // The answer points into the input tree.
    TreeNode* parent;
    TreeNode* p;
    TreeNode* q;
    // Return presence of either target in this subtree, not a target count.
    bool hasTarget(TreeNode* root) {
        if (root == nullptr) return false;

        // Both children are evaluated; each contributes only a boolean presence flag.
        int find_cnt = (int) hasTarget(root->left) +
                       (int) (root == p) +
                       (int) (root == q) +
                       (int) hasTarget(root->right);

        // Two independent target-presence contributions meet at their lowest ancestor.
        if (find_cnt == 2) parent = root;

        // Collapse the subtree to one flag so ancestors do not count its targets twice.
        return find_cnt != 0;
    }
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // Reset query state for repeated calls on the same Solution object.
        parent = nullptr;
        this->p = p;
        this->q = q;

        hasTarget(root);
        return parent;
    }
};

// Local output helper: print the returned node's value, or null if absent.
void printAnswer(int example, TreeNode* answer) {
    printf("Example %d: ", example);
    if (answer != nullptr) printf("%d\n", answer->val);
    else printf("null\n");
}

int main() {
    Solution sol;

    // Examples 1 and 2 use this same tree:
    //         3
    //       /   ╲
    //      5     1
    //     / ╲   / ╲
    //    6   2 0   8
    //       / ╲
    //      7   4
    TreeNode node6(6);
    TreeNode node7(7);
    TreeNode node4(4);
    TreeNode node2(2, &node7, &node4);
    TreeNode node5(5, &node6, &node2);
    TreeNode node0(0);
    TreeNode node8(8);
    TreeNode node1(1, &node0, &node8);
    TreeNode root1(3, &node5, &node1);

    // Example 1: p = 5, q = 1; expected returned node: &root1 (value 3).
    printAnswer(1, sol.lowestCommonAncestor(&root1, &node5, &node1));

    // Example 2: p = 5, q = 4; expected returned node: &node5 (value 5).
    printAnswer(2, sol.lowestCommonAncestor(&root1, &node5, &node4));

    // Example 3: root = [1,2], p = 1, q = 2.
    TreeNode left3(2);
    TreeNode root3(1, &left3, nullptr);
    // Expected returned node: &root3 (value 1).
    printAnswer(3, sol.lowestCommonAncestor(&root3, &root3, &left3));

    return 0;
}
