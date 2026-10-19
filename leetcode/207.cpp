/*
 * Problem Link: https://leetcode.cn/problems/course-schedule/
 * Problem Name: 207. Course Schedule
 * Difficulty: Medium
 * Problem Tags: directed graph, topological sort, queue
 *
 * Submission Record:
 * Approach: Kahn topological sort with adjacency lists and an indegree queue
 * Language: C++
 * Status: Accepted
 * Submitted At: N/A
 * Runtime: 7 ms (beats 50.55%)
 * Memory: 19.74 MB (beats 23.01%)
 * Submission Link:
 * N/A
 * Recorded On: 2026-10-19
 * Record Source: User-provided accepted-submission screenshot
 *
 * Problem Description:
 * There are numCourses courses labeled from 0 to numCourses - 1.
 * Each pair [a, b] in prerequisites means course b must be completed
 * before course a can be taken.
 * Return true if all courses can be completed; otherwise, return false.
 *
 * Constraints:
 * 1. 1 <= numCourses <= 2000
 * 2. 0 <= prerequisites.length <= 5000
 * 3. prerequisites[i].length == 2
 * 4. 0 <= a, b < numCourses
 * 5. All prerequisite pairs are distinct.
 *
 * Example 1:
 * Input: numCourses = 2, prerequisites = [[1,0]]
 * Output: true
 * Explanation: Complete course 0 before taking course 1.
 *
 * Example 2:
 * Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
 * Output: false
 * Explanation: Each course requires the other to be completed first.
 *
 * Note:
 * The local main() runs both official examples directly.
 * The prerequisite input is not modified; graph and queue state are local to each call.
 *
 * Approach:
 * Represent each prerequisite [a, b] as an edge b -> a. Store outgoing course
 * IDs in adjacency lists and count each course's remaining prerequisites.
 * Queue every zero-indegree course, including isolated courses. For each
 * dequeued course, increment the finished count and remove its outgoing
 * dependencies by decrementing the corresponding indegrees.
 * Enqueue a successor exactly when its indegree reaches zero.
 * All courses can be completed if and only if finished equals numCourses;
 * otherwise, a directed cycle prevents the remaining courses from being processed.
 *
 * Complexity:
 * Let V = numCourses and E = prerequisites.size(). Initializing the course
 * records and scanning for zero indegrees takes O(V). Building adjacency lists
 * takes amortized O(E), and each vertex and edge is processed at most once
 * during topological traversal. Total time is O(V + E).
 * Auxiliary space is O(V + E): O(V) course records and queue entries plus
 * O(E) adjacency entries. No recursive call stack is used.
 */

#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

struct CourseNode {
    vector<int> nexts;
    int in;
};

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // O(V) initialization; value-initialization sets every in field to zero.
        vector<CourseNode> ct(numCourses);
        queue<int> cq;
        int finished = 0;

        // Amortized O(E): build edges b -> a and count the incoming dependencies.
        for (auto edge: prerequisites) {
            ct[edge[0]].in++;
            ct[edge[1]].nexts.push_back(edge[0]);
        }

        // O(V): seed the queue with every course that can be taken immediately.
        for (int i = 0; i < numCourses; i++) {
            if (ct[i].in == 0) {
                cq.push(i);
            }
        }

        // O(V + E): each course enters the queue at most once; each edge is visited once.
        while (!cq.empty()) {
            int idx = cq.front();
            finished++;
            cq.pop();
            for (auto next: ct[idx].nexts) {
                ct[next].in--;
                if (ct[next].in == 0) {
                    cq.push(next);
                }
            }
        }

        // Unprocessed courses after the queue empties imply a directed cycle.
        return finished == numCourses;
    }
};

int main() {
    Solution sol;

    int numCourses1 = 2;
    vector<vector<int>> input1 = {{1,0}};
    // Expected output: true
    printf("Example 1: %s\n", sol.canFinish(numCourses1, input1) ? "true" : "false");

    int numCourses2 = 2;
    vector<vector<int>> input2 = {{1,0}, {0,1}};
    // Expected output: false
    printf("Example 2: %s\n", sol.canFinish(numCourses2, input2) ? "true" : "false");

    return 0;
}
