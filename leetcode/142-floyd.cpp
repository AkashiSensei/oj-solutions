/*
 * Problem Link: https://leetcode.cn/problems/linked-list-cycle-ii/
 * Problem Name: 142. Linked List Cycle II
 * Difficulty: Medium
 * Problem Tags: linked list, two pointers
 *
 * Submission Record:
 * Approach: Floyd cycle detection + equal-speed search for the cycle entry
 * Language: C++
 * Status: Accepted
 * Submitted At: N/A
 * Runtime: 3 ms (beats 99.01%)
 * Memory: 11.19 MB (beats 55.89%)
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
 * The solution leaves all input nodes, values, and links unchanged.
 * Pointers are compared by node identity, so duplicate values are allowed.
 *
 * Approach:
 * Start fp and sp at head. On each iteration, advance sp once and fp twice,
 * checking fp after its first step before taking its second step.
 * If fp reaches nullptr, the list has no cycle; this also handles an empty
 * list. Otherwise, stop when fp and sp meet after moving inside the cycle.
 * Reset fp to head, keep sp at the meeting node, and advance both one step
 * at a time. Their next meeting is the cycle entry, which is returned.
 * To see why, let a be the distance from head to the entry, b the forward
 * offset from the entry to the meeting node, and L the cycle length.
 * At the first meeting, the difference between the distances traveled is
 * a multiple of L. Since fp travels twice as far as sp, sp's distance is
 * also a multiple of L, implying a + b is a multiple of L. Thus, moving
 * a steps from the meeting node reaches the entry, just as moving a steps
 * from head does. If a is zero, the pointers already agree after the reset.
 *
 * Complexity:
 * Let n be the number of distinct nodes reachable from head. Without a
 * cycle, the first phase takes O(n) time. With a cycle, sp reaches the
 * cycle after a steps and meets fp within at most L further steps;
 * the second phase takes a steps. Total time is O(a + L) = O(n).
 * Only two node pointers are used, so auxiliary space is O(1), excluding
 * the local test scaffolding. There is no recursion or hash table.
 */

#include <cstdio>
#include <vector>

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
        ListNode* fp = head;
        ListNode* sp = head;

        // Phase 1: move at different speeds until a meeting or the list end.
        while (fp != nullptr) {
            sp = sp->next;
            fp = fp->next;
            // A second fast step is valid only if the first did not reach nullptr.
            if (fp != nullptr) {
                fp = fp->next;
            }else {
                break;
            }

            if (sp == fp) break;
        }

        if (fp == nullptr) return nullptr;

        // Phase 2: restart one pointer and move both at the same speed.
        fp = head;
        while (fp != sp) {
            sp = sp->next;
            fp = fp->next;
        }

        return fp;
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
