/*
 * Problem Link: https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
 * Problem Name: 105. Construct Binary Tree from Preorder and Inorder Traversal
 * Difficulty: Medium
 * Problem Tags: array, hash table, divide and conquer, tree, binary tree
 *
 * Submission Record:
 * Approach: Recursive range splitting with an inorder-index hash table
 * Language: C++
 * Status: Accepted
 * Submitted At: N/A
 * Runtime: 0 ms (beats 100.00%)
 * Memory: 26.96 MB (beats 46.91%)
 * Submission Link: N/A
 * Recorded On: 2026-10-25
 * Record Source: User-provided accepted-submission screenshot
 *
 * Problem Description:
 * Given preorder and inorder traversals of the same binary tree, construct
 * that tree and return its root. All node values are distinct.
 *
 * Constraints:
 * 1. 1 <= preorder.length <= 3000
 * 2. inorder.length == preorder.length
 * 3. -3000 <= preorder[i], inorder[i] <= 3000
 * 4. Both arrays contain distinct values and the same set of values.
 * 5. Both arrays are guaranteed to be valid traversals of the same tree.
 *
 * Example 1:
 * Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
 * Output: [3,9,20,null,null,15,7]
 *
 * Example 2:
 * Input: preorder = [-1], inorder = [-1]
 * Output: [-1]
 *
 * Note:
 * TreeNode is defined here for local compilation; LeetCode provides it.
 * The local main() runs both official examples and prints the returned tree
 * in level order, using null for missing children and omitting trailing nulls.
 * The local cleanup helper deletes nodes individually; allocate returned nodes
 * with new when using this harness.
 * The input traversal vectors are not modified or copied into subarrays.
 * Member pointers refer to the caller's vectors during construction; nodes
 * allocated with new form an independent returned tree.
 * The index map is retained between calls. Current inorder values overwrite
 * their positions; older keys are not queried for valid current traversals.
 *
 * Approach:
 * Map each inorder value to its position. Each recursive call receives matching
 * half-open preorder [p_s, p_e) and inorder [i_s, i_e) ranges for one subtree.
 * An empty preorder range represents a missing child and returns nullptr.
 * The first preorder value is the subtree root. Its inorder position separates
 * the left and right subtrees; the left range length also splits preorder.
 * Recursively construct both children and return a new node connecting them.
 *
 * Complexity:
 * Let n be the node count and h the constructed tree height. For a fresh
 * Solution object, building the index takes average/amortized O(n) time.
 * Each node is created once and uses an average O(1) hash lookup; ranges are
 * passed as integers, so no traversal slices are copied. Total time is
 * average/amortized O(n), with O(n^2) worst-case time under severe collisions.
 * Auxiliary space is O(n + h) = O(n): O(n) hash entries and O(h) recursive stack.
 * The stack alone is O(log n) for a balanced tree and O(n) for a skewed tree.
 * The returned tree occupies another O(n) space; including it remains O(n).
 * Across repeated calls, the uncleared map may retain keys from earlier inputs,
 * so its storage depends on the distinct values seen over the object's lifetime.
 * Local output and cleanup helpers are excluded from solution complexity.
 */

#include <cstdio>
#include <vector>
#include <utility>
#include <unordered_map>

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
    // Borrow traversal storage during buildTree(); no vector copies are made.
    vector<int>* pre;
    vector<int>* in;
    // Unique node value -> its current inorder position.
    unordered_map<int, int> index;

    TreeNode* buildSub(int p_s, int p_e, int i_s, int i_e) {
        // Both traversal ranges are half-open; an empty range is a missing child.
        if (p_e == p_s) return nullptr;

        // Preorder identifies the root; inorder determines the left subtree size.
        int r_val = (*pre)[p_s];
        int i_r_idx = index[r_val];
        int l_len = i_r_idx - i_s;

        // Partition both traversals consistently and connect the returned child roots.
        return new TreeNode(
                           r_val,
                           buildSub(p_s + 1, p_s + 1 + l_len, i_s, i_s + l_len),
                           buildSub(p_s + 1 + l_len, p_e, i_s + 1 + l_len, i_e)
                           );
    }

public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        pre = &preorder;
        in = &inorder;

        // Current values overwrite any positions left by earlier calls.
        for (int i = 0; i < inorder.size(); i++) {
            index[inorder[i]] = i;
        }

        return buildSub(0, preorder.size(), 0, inorder.size());
    }
};

// Local output helper: serialize a tree in LeetCode's level-order format.
void printTree(TreeNode* root) {
    vector<TreeNode*> nodes;
    if (root != nullptr) nodes.push_back(root);

    for (size_t i = 0; i < nodes.size(); i++) {
        TreeNode* node = nodes[i];
        if (node != nullptr) {
            nodes.push_back(node->left);
            nodes.push_back(node->right);
        }
    }
    while (!nodes.empty() && nodes.back() == nullptr) nodes.pop_back();

    printf("[");
    for (size_t i = 0; i < nodes.size(); i++) {
        if (i > 0) printf(",");
        if (nodes[i] == nullptr) printf("null");
        else printf("%d", nodes[i]->val);
    }
    printf("]\n");
}

// Local cleanup helper: release all nodes allocated with individual new calls.
void deleteTree(TreeNode* root) {
    vector<TreeNode*> pending;
    if (root != nullptr) pending.push_back(root);
    while (!pending.empty()) {
        TreeNode* node = pending.back();
        pending.pop_back();
        if (node->left != nullptr) pending.push_back(node->left);
        if (node->right != nullptr) pending.push_back(node->right);
        delete node;
    }
}

int main() {
    Solution sol;
    vector<int> preorders[] = {
        {3, 9, 20, 15, 7},
        {-1}
    };
    vector<int> inorders[] = {
        {9, 3, 15, 20, 7},
        {-1}
    };

    // Expected: [3,9,20,null,null,15,7], [-1].
    for (int i = 0; i < 2; i++) {
        TreeNode* root = sol.buildTree(preorders[i], inorders[i]);
        printf("Example %d: ", i + 1);
        printTree(root);
        deleteTree(root);
    }

    return 0;
}
