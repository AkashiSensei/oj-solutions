/*
 * Problem Link: https://leetcode.cn/problems/network-delay-time/
 * Problem Name: 743. Network Delay Time
 * Difficulty: Medium
 * Problem Tags: directed graph, shortest path, heap (priority queue)
 *
 * Submission Record:
 * Approach: Min-heap Dijkstra with tentative-distance pruning and settled flags
 * Language: C++
 * Status: Accepted
 * Submitted At: N/A
 * Runtime: 96 ms (beats 26.84%)
 * Memory: 47.00 MB (beats 11.11%)
 * Submission Link:
 * N/A
 * Recorded On: 2026-10-21
 * Record Source: User-provided accepted-submission screenshot
 *
 * Problem Description:
 * There are n network nodes labeled from 1 to n. Each entry [u, v, w]
 * in times describes a directed edge from u to v with transmission time w.
 * A signal is sent from node k. Return the minimum time until every node
 * receives the signal, or -1 if some node cannot receive it.
 *
 * Constraints:
 * 1. 1 <= k <= n <= 100
 * 2. 1 <= times.length <= 6000
 * 3. times[i].length == 3
 * 4. 1 <= u, v <= n, and u != v
 * 5. 0 <= w <= 100
 * 6. All directed pairs (u, v) are distinct; there are no duplicate edges.
 *
 * Example 1:
 * Input: times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
 * Output: 2
 *
 * Example 2:
 * Input: times = [[1,2,1]], n = 2, k = 1
 * Output: 1
 *
 * Example 3:
 * Input: times = [[1,2,1]], n = 2, k = 2
 * Output: -1
 *
 * Note:
 * Edges are directed, and node labels start at 1.
 * The local main() runs the user-provided regression case first, followed by
 * all three official examples. Input times is not modified; all state is local.
 * Structured bindings in adjacency traversal require C++17 or later.
 *
 * Approach:
 * Build directed adjacency lists and initialize tentative distances to INT_MAX,
 * except dist[k] = 0. Start the min heap with the source and distance 0.
 * The first popped entry for an unsettled node fixes its shortest distance.
 * For each outgoing edge, insert a candidate only if its distance is strictly
 * smaller than dist[target], and update dist[target] at insertion time.
 * A rejected candidate cannot help: a path of no greater cost to the same target
 * has already been queued or processed, and any continuation is available to it too.
 * Updating dist on insertion also filters redundant candidates before settlement.
 * Improved records are inserted separately; old heap entries are not modified.
 * Settled flags discard later duplicates without scanning edges or updating c_dis.
 * If all nodes are settled, return the last finalized distance; otherwise return -1.
 *
 * Complexity:
 * Let V = n and E = times.size(). Initialization and adjacency construction
 * take O(V + E). Each node is settled at most once and each reachable edge
 * is scanned once. Only successful distance improvements create heap entries,
 * giving at most E + 1 insertions and removals and O(E) worst-case heap size.
 * Total worst-case time remains O(V + E log E), treating heap operations as
 * O(1) when E = 1. With no parallel edges, this is also bounded by
 * O((V + E) log V) for V >= 2.
 * Auxiliary space is O(V + E), including adjacency lists, O(V) dist/settled
 * arrays, and an O(E) candidate heap. Pruning can reduce actual heap work and
 * peak heap size, but it does not improve these worst-case bounds.
 */

#include <cstdio>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <functional>
#include <climits>

using namespace std;

struct NodeDis {
    int node;
    int dis;
};

struct NodeDisCmp {
    bool operator()(const NodeDis& a, const NodeDis& b) {
        // A larger candidate distance has lower priority, creating a min heap.
        return a.dis > b.dis;
    }
};

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // O(V) initialization; index 0 is unused because nodes are numbered 1..n.
        vector<bool> reached(n + 1, false);
        // Best discovered distances, including tentative paths not yet finalized.
        vector<int> dist(n + 1, INT_MAX);
        vector<vector<pair<int, int>>> edges(n + 1);
        priority_queue<NodeDis, vector<NodeDis>, NodeDisCmp> pq;
        int r_cnt = 0;

        // Amortized O(E) construction; adjacency lists occupy O(V + E) space.
        for (auto edge: times) {
            edges[edge[0]].push_back({edge[1], edge[2]});
        }

        pq.push({k, 0});
        dist[k] = 0;

        int cur, c_dis;

        // At most E + 1 pops; duplicates skip edge traversal and preserve c_dis.
        while (!pq.empty()) {
            cur = pq.top().node;
            if (reached[cur]) {
                pq.pop();
                continue;
            }

            // The first popped entry for this node fixes its shortest distance.
            c_dis = pq.top().dis;
            pq.pop();

            r_cnt++;
            reached[cur] = true;
            // Each edge is checked once; only a strictly shorter path is queued.
            for (auto& [tar, w]: edges[cur]) {
                if (w + c_dis < dist[tar]) {
                    pq.push({tar, w + c_dis});
                    // Update immediately so later non-improving candidates are filtered.
                    dist[tar] = w + c_dis;
                }
            }
        }

        if (r_cnt < n) return -1;

        // Settled distances are nondecreasing; the last one is the required delay.
        return c_dis;
    }
};

int main() {
    Solution sol;

    // Debug case: times = [[1,2,1],[2,1,3]], n = 2, k = 2
    vector<vector<int>> input0 = {{1,2,1}, {2,1,3}};
    int n0 = 2;
    int k0 = 2;
    // Expected output: 3
    printf("Debug case: %d\n", sol.networkDelayTime(input0, n0, k0));

    vector<vector<int>> input1 = {{2,1,1}, {2,3,1}, {3,4,1}};
    int n1 = 4;
    int k1 = 2;
    // Expected output: 2
    printf("Example 1: %d\n", sol.networkDelayTime(input1, n1, k1));

    vector<vector<int>> input2 = {{1,2,1}};
    int n2 = 2;
    int k2 = 1;
    // Expected output: 1
    printf("Example 2: %d\n", sol.networkDelayTime(input2, n2, k2));

    vector<vector<int>> input3 = {{1,2,1}};
    int n3 = 2;
    int k3 = 2;
    // Expected output: -1
    printf("Example 3: %d\n", sol.networkDelayTime(input3, n3, k3));

    return 0;
}
