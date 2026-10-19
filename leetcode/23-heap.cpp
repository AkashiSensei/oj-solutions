/*
 * Problem Link: https://leetcode.cn/problems/merge-k-sorted-lists/
 * Problem Name: 23. Merge k Sorted Lists
 * Difficulty: Hard
 * Problem Tags: linked list, heap (priority queue)
 *
 * Submission Record:
 * Approach: Min heap of current list nodes + in-place node relinking
 * Language: C++
 * Status: Accepted
 * Submitted At: N/A
 * Runtime: 3 ms (beats 70.49%)
 * Memory: 18.03 MB (beats 81.38%)
 * Submission Link:
 * N/A
 * Recorded On: 2026-10-19
 * Record Source: User-provided accepted-submission screenshot
 *
 * Problem Description:
 * Given an array of k linked lists, each sorted in ascending order,
 * merge them into one ascending linked list and return its head.
 *
 * Constraints:
 * 1. k == lists.size(), and 0 <= k <= 10000
 * 2. Each input list contains between 0 and 500 nodes.
 * 3. -10000 <= Node.val <= 10000
 * 4. Each input list is sorted in ascending order.
 * 5. The total number of nodes across all lists is at most 10000.
 *
 * Example 1:
 * Input: lists = [[1,4,5],[1,3,4],[2,6]]
 * Output: [1,1,2,3,4,4,5,6]
 *
 * Example 2:
 * Input: lists = []
 * Output: []
 *
 * Example 3:
 * Input: lists = [[]]
 * Output: []
 *
 * Note:
 * ListNode is defined here for local compilation; LeetCode provides it.
 * The local main() constructs and runs all three official examples.
 * Input example nodes are local objects; they must not be deleted or freed.
 * Output nodes are reused from the input lists; their next links are modified.
 * The temporary heap-allocated dummy head is deleted before returning.
 *
 * Approach:
 * Insert each non-null list head into a min heap of ListNode pointers.
 * Repeatedly append the smallest node to the output chain, pop it from the heap,
 * and insert its original successor if present. The heap keeps at most one
 * candidate from each input list, so its size never exceeds k.
 * Save the output head, delete the dummy node, and return the saved pointer.
 * No new output nodes are allocated; equal-valued nodes need no fixed tie order.
 *
 * Complexity:
 * Let N be the total input node count, k the number of input lists, and
 * m the number of non-empty input lists, where m <= min(k, N).
 * Scanning heads costs O(k), with O(m log m) for individual initial insertions
 * when m >= 2. Each node is pushed and popped once from a heap of size at most m.
 * For k >= 2, total time is O(k + N log k); for k <= 1, heap operations
 * take O(1) each and total work is O(k + N), with O(1) work for empty input.
 * Auxiliary space is O(k), more precisely O(m) heap pointers plus one dummy.
 * The returned list reuses input nodes and needs no O(N) output allocation.
 */

#include <cstdio>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct ListNodeCmp {
    bool operator()(const ListNode* a, const ListNode* b) {
        // A larger node value has lower priority, creating a min heap.
        return b->val < a->val;
    }
};

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, ListNodeCmp> pq;

        // One temporary dummy node; it is released after saving the result head.
        ListNode* tail = new ListNode();
        ListNode* head = tail;

        // O(k) head scan, plus the initial heap insertion costs.
        for (ListNode* list: lists) {
            if (list != nullptr)
                pq.push(list);
        }

        // Each input node is processed once; heap size stays at most k.
        while (!pq.empty()) {
            tail->next = pq.top();
            tail = tail->next;
            pq.pop();

            // Queue this node's successor before the next output link is changed.
            if (tail->next != nullptr) {
                pq.push(tail->next);
            }
        }

        // Preserve the result before deleting only the temporary dummy.
        tail = head->next;
        delete head;
        return tail;
    }
};

// Local test helper: print a linked list without modifying its nodes.
void printList(const ListNode* head) {
    printf("[");
    for (const ListNode* node = head; node != nullptr; node = node->next) {
        if (node != head) printf(",");
        printf("%d", node->val);
    }
    printf("]\n");
}

int main() {
    Solution sol;

    // Example 1: [[1,4,5],[1,3,4],[2,6]]
    // First list: 1 -> 4 -> 5
    ListNode a3(5);
    ListNode a2(4, &a3);
    ListNode a1(1, &a2);

    // Second list: 1 -> 3 -> 4
    ListNode b3(4);
    ListNode b2(3, &b3);
    ListNode b1(1, &b2);

    // Third list: 2 -> 6
    ListNode c2(6);
    ListNode c1(2, &c2);

    vector<ListNode*> input1 = {&a1, &b1, &c1};
    printf("Example 1: ");
    printList(sol.mergeKLists(input1));
    // Expected output: [1,1,2,3,4,4,5,6]

    // Example 2: [] means there are no input lists.
    vector<ListNode*> input2;
    printf("Example 2: ");
    printList(sol.mergeKLists(input2));
    // Expected output: []

    // Example 3: [[]] means there is one empty input list.
    vector<ListNode*> input3 = {nullptr};
    printf("Example 3: ");
    printList(sol.mergeKLists(input3));
    // Expected output: []

    return 0;
}
