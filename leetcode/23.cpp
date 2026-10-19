/*
 * Problem Link: https://leetcode.cn/problems/merge-k-sorted-lists/
 * Problem Name: 23. Merge k Sorted Lists
 * Difficulty: Hard
 * Problem Tags: linked list, counting
 *
 * Submission Record:
 * Approach: Bounded-range counting + newly allocated output list
 * Language: C++
 * Status: Accepted
 * Submitted At: N/A
 * Runtime: 15 ms (beats 23.70%)
 * Memory: 30.97 MB (beats 5.03%)
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
 * Input nodes and links are left unchanged; output nodes are allocated with new.
 * The current implementation does not release its heap-allocated dummy head.
 * The local main() also leaves the newly allocated output nodes unreleased.
 *
 * Approach:
 * Traverse every input list and count each value in a direct-address vector,
 * using value + 10000 as its index. Scan buckets in increasing value order
 * and append as many new nodes as each bucket's count requires.
 * This reconstructs a sorted list without relying on the input lists' order.
 * The returned head is dummy->next; no original nodes are reused.
 *
 * Complexity:
 * Let N be the total input node count, k the number of input lists, and U = 20001.
 * Zero-initializing counters takes O(U). Traversing all list heads and nodes
 * takes O(k + N), including empty lists. Scanning buckets and constructing
 * N output nodes takes O(U + N), for O(k + N + U) total time.
 * Auxiliary space is O(U), excluding the O(N) newly allocated output list.
 * Including output nodes, allocated storage is O(U + N), plus one dummy node.
 * Under the fixed value range, U is constant, so time is O(k + N) and
 * auxiliary space is O(1) with respect to k and N.
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

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // O(U) initialization and storage for values in [-10000, 10000].
        vector<int> counting(20001, 0);

        // O(k + N): inspect every list head and visit every input node once.
        for (auto list: lists) {
            ListNode * nextp = list;
            while (nextp != nullptr) {
                counting[nextp->val + 10000]++;
                nextp = nextp->next;
            }
        }

        // Dummy head; this version returns head->next without deleting head.
        ListNode* head = new ListNode();
        ListNode* tail = head;

        // O(U + N): scan all buckets and allocate exactly N output nodes.
        for (int i = 0; i < 20001; i++) {
            for (int cnt = 0; cnt < counting[i]; cnt++) {
                tail->next = new ListNode(i - 10000);
                tail = tail->next;
            }
        }

        return head->next;
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
