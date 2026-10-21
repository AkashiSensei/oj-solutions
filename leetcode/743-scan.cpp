/*
 * Problem Link: https://leetcode.cn/problems/network-delay-time/
 * Problem Name: 743. Network Delay Time
 * Difficulty: Medium
 * Problem Tags: directed graph, shortest path
 *
 * Submission Record:
 * Approach: Linear-scan Dijkstra with adjacency lists
 * Language: C++
 * Status: Accepted
 * Submitted At: N/A
 * Runtime: 98 ms (beats 23.75%)
 * Memory: 46.82 MB (beats 14.95%)
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
 * all three official examples.
 * Input times is not modified, and all state is local to each call.
 * Structured bindings in adjacency traversal require C++17 or later.
 * The by-value edge loop copies each three-integer input vector during construction.
 *
 * Approach:
 * Build directed adjacency lists and initialize dist[k] = 0, with all other
 * tentative distances set to INT_MAX. Start by settling the source k.
 * For each settled node, relax its outgoing edges using its finite distance.
 * Scan all node IDs to select the unvisited node with the smallest finite dist.
 * Stop when the scan finds no reachable unvisited node. If fewer than n nodes
 * were settled, return -1; otherwise, dist[cur] is the last finalized distance
 * and therefore the maximum shortest distance needed for all nodes to receive.
 *
 * Complexity:
 * Let V = n and E = times.size(). Initialization costs O(V), and adjacency
 * construction costs amortized O(E). The construction loop copies E input
 * vectors of length three, adding constant-size work and allocations per edge.
 * At most V iterations scan V node IDs each, costing O(V^2). Each node is
 * settled once, so reachable outgoing edges are relaxed at most once each.
 * Total worst-case time is O(V^2 + E).
 * Auxiliary space is O(V + E) for adjacency lists, distances, and visited flags;
 * this version uses neither an adjacency matrix nor a priority queue.
 */

#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // O(V) initialization and storage for distances and visited flags.
        vector<int> dist(n + 1, INT_MAX);
        vector<bool> visit(n + 1, false);
        vector<vector<pair<int, int>>> edges(n + 1);
        int r_cnt = 0;


        // Amortized O(E) construction; auto by value also copies each edge vector.
        for (auto edge: times) {
            edges[edge[0]].push_back({edge[1], edge[2]});
        }

        int cur = k;
        int min_d = 0;
        dist[k] = 0;
        // At most V settlements; full minimum-distance scans cost O(V^2) in total.
        while (true) {
            r_cnt++;
            visit[cur] = true;

            // Each reachable outgoing edge is processed once: O(E) total.
            for (auto& [tar, w]: edges[cur]) {
                if (min_d + w < dist[tar]) {
                    dist[tar] = min_d + w;
                }
            }

            min_d = INT_MAX;
            // O(V): select the next unvisited node with a finite tentative distance.
            for (int i = 1; i <= n; i++) {
                if (dist[i] < min_d && !visit[i]) {
                    cur = i;
                    min_d = dist[i];
                }
            }

            if (min_d == INT_MAX) break;
        }

        if (r_cnt < n) return -1;
        // The last settled node has the largest finalized shortest distance.
        return dist[cur];
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
