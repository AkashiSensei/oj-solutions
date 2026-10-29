/*
 * Problem Link: https://leetcode.cn/problems/linked-list-cycle-ii/
 * Problem Name: 142. Linked List Cycle II
 * Difficulty: Medium
 * Problem Tags: linked list, hash table
 *
 * Submission Record:
 * Approach: Hash-table tracking of previously visited node pointers
 * Language: C++
 * Status: Accepted
 * Submitted At: N/A
 * Runtime: 19 ms (beats 6.10%)
 * Memory: 13.50 MB (beats 5.02%)
 * Submission Link: N/A
 * Recorded On: 2026-10-29
 * Record Source: User-provided accepted-submission screenshot
 *
 * Problem Description:
 * Given the head of a linked list, return the node where its cycle begins.
 * If there is no cycle, return nullptr. Do not modify the linked list.
 * A cycle exists if following next pointers can revisit a node.
 * The test description uses pos to identify the zero-based index connected
 * to the tail, or -1 for no cycle. pos is not passed to detectCycle().
 * Return the original node pointer, not its value or index.
 *
 * Constraints:
 * 1. The number of nodes is in [0, 10000].
 * 2. -100000 <= Node.val <= 100000
 * 3. pos is -1 or a valid index in the linked list.
 *
 * Example 1:
 * Input: head = [3,2,0,-4], pos = 1
 * Output: The node at index 1.
 * Explanation: The tail connects to the second node.
 *
 * Example 2:
 * Input: head = [1,2], pos = 0
 * Output: The node at index 0.
 * Explanation: The tail connects to the first node.
 *
 * Example 3:
 * Input: head = [1], pos = -1
 * Output: nullptr
 * Explanation: The linked list has no cycle.
 *
 * Follow-up:
 * Can you solve the problem using O(1) extra space?
 *
 * Note:
 * ListNode is defined here for local compilation; LeetCode provides it.
 * The local main() constructs all three official examples, checks pointer
 * identity, and prints the returned node's original index when available.
 * The node vector is only test scaffolding and is not passed to the solution.
 * Test nodes are deleted using the saved pointers, without traversing the cycle.
 * The solution leaves all input nodes and links unchanged.
 * Pointer identity is used, so repeated node values do not affect correctness.
 *
 * Approach:
 * Traverse the list from head, keeping an unordered_map keyed by ListNode*.
 * Before recording a node, check whether its pointer has already been seen.
 * The first repeated node is the cycle entry: traversal visits the non-cyclic
 * prefix once, then visits the cycle once before returning to its entry.
 * Return that original pointer, or nullptr if traversal reaches the end.
 * The map stores each node's value, but those mapped integers are never
 * queried; only membership of the node pointer is needed by this version.
 *
 * Complexity:
 * Let n be the number of distinct nodes reachable from head. There are at
 * most n insertions and n + 1 membership checks. Hash lookup takes O(1)
 * average time, and insertion takes amortized O(1) average time, giving
 * O(n) average/amortized time overall. Worst-case hash collisions can
 * make the total time O(n^2). The map holds up to n entries, so auxiliary
 * space is O(n). This implementation does not meet the O(1)-space follow-up.
 * Local test construction, printing, and node cleanup are excluded.
 */

#include <cstdio>
#include <vector>
#include <unordered_map>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* detectCycle(ListNode* head) {
        // Keys identify nodes by address, independently of their values.
        unordered_map<ListNode*, int> mp;
        ListNode* p = head;

        while (p != nullptr) {
            // The first revisited node is the entry of the cycle.
            if (mp.count(p) != 0) {
                return p;
            }
            // Record this node before following its next pointer.
            mp[p] = p->val;
            p = p->next;
        }

        // Reaching the end means the list has no cycle.
        return nullptr;
    }
};

// Print a returned pointer using the known test nodes, without following next.
void printEntry(const vector<ListNode*>& nodes, const ListNode* entry) {
    if (entry == nullptr) {
        printf("nullptr");
        return;
    }
    for (size_t i = 0; i < nodes.size(); ++i) {
        if (nodes[i] == entry) {
            printf("node at index %zu (value %d)", i, nodes[i]->val);
            return;
        }
    }
    printf("pointer outside the input list");
}

int main() {
    Solution sol;
    vector<int> inputs[] = {
        {3, 2, 0, -4},
        {1, 2},
        {1}
    };
    int positions[] = {1, 0, -1};

    for (int i = 0; i < 3; ++i) {
        // Keep ownership separately so cleanup never needs to traverse a cycle.
        vector<ListNode*> nodes;
        for (int value : inputs[i]) {
            nodes.push_back(new ListNode(value));
        }
        for (size_t j = 1; j < nodes.size(); ++j) {
            nodes[j - 1]->next = nodes[j];
        }
        if (!nodes.empty() && positions[i] >= 0) {
            nodes.back()->next = nodes[positions[i]];
        }

        ListNode* head = nodes.empty() ? nullptr : nodes.front();
        ListNode* expected = positions[i] < 0 ? nullptr : nodes[positions[i]];
        ListNode* actual = sol.detectCycle(head);

        printf("Example %d: ", i + 1);
        printEntry(nodes, actual);
        printf("\nExpected: ");
        printEntry(nodes, expected);
        printf("\n%s\n", actual == expected ? "PASS" : "FAIL");

        for (ListNode* node : nodes) {
            delete node;
        }
    }

    return 0;
}
