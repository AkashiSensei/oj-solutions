# LeetCode Solutions

Accepted LeetCode solutions and submission records. Different implementations of the same problem are kept in separate files; rows follow submission order, oldest first.

## Implementation index

Runtime and memory cells show the measured value followed by the analyzed complexity. Algorithm explanations, complexity symbols, assumptions, and submission details are documented in each linked source file.

| Problem | Implementation | Language | Status | Runtime (ms) | Runtime beats | Memory (MB) | Memory beats |
| --- | --- | --- | --- | ---: | ---: | ---: | ---: |
| 42. Trapping Rain Water | [42.c](42.c) — Suffix maxima + running prefix maximum | C | Accepted | 0<br>O(n) | 100.00% | 10.38<br>O(n) | 28.65% |
| 42. Trapping Rain Water | [42-opt.c](42-opt.c) — Two pointers comparing running maxima | C | Accepted | 0<br>O(n) | 100.00% | 10.25<br>O(1) | 73.59% |
| 42. Trapping Rain Water | [42.cpp](42.cpp) — Two pointers comparing boundary heights | C++ | Accepted | 0<br>O(n) | 100.00% | 25.52<br>O(1) | 65.47% |
| 42. Trapping Rain Water | [42.go](42.go) — Two pointers comparing boundary heights | Go | Accepted | 0<br>O(n) | 100.00% | 7.89<br>O(1) | 15.19% |
| 198. House Robber | [198.cpp](198.cpp) — Dynamic programming with rolling states | C++ | Accepted | 0<br>O(n) | 100.00% | 9.78<br>O(1) | 99.39% |
| 200. Number of Islands | [200-bfs.cpp](200-bfs.cpp) — BFS with a set of unvisited land | C++ | Accepted | 77<br>O(mn + L log L) | 5.05% | 28.64<br>O(L) | 5.01% |
| 200. Number of Islands | [200-dfs.cpp](200-dfs.cpp) — Iterative DFS with in-place marking | C++ | Accepted | 23<br>O(mn) | 90.85% | 17.01<br>O(L) | 28.20% |
| 200. Number of Islands | [200-dsu.cpp](200-dsu.cpp) — Union-find by size on adjacent land | C++ | Accepted | 30<br>O(mn α(mn)) | 48.88% | 18.55<br>O(mn) | 19.61% |
| 200. Number of Islands | [200-dsu-id.cpp](200-dsu-id.cpp) — Union-find by size with packed coordinates | C++ | Accepted | 30<br>O(mn α(mn)) | 48.88% | 17.54<br>O(mn) | 24.50% |
| 3. Longest Substring Without Repeating Characters | [3.cpp](3.cpp) — Sliding window with last-seen character indices | C++ | Accepted | 7<br>O(n) | 90.94% | 18.45<br>O(1) | 67.25% |
| 739. Daily Temperatures | [739.cpp](739.cpp) — Monotonic stack of unresolved days and temperatures | C++ | Accepted | 27<br>O(n) | 55.13% | 109.27<br>O(n) | 6.81% |
| 739. Daily Temperatures | [739-array.cpp](739-array.cpp) — Array-backed monotonic stack of day-temperature records | C++ | Accepted | 15<br>O(n) | 94.54% | 101.37<br>O(C) reserved | 84.67% |
| 739. Daily Temperatures | [739-array-day.cpp](739-array-day.cpp) — Array-backed monotonic stack of day indices | C++ | Accepted | 18<br>O(n) | 88.65% | 101.01<br>O(C) reserved | 84.77% |
| 146. LRU Cache | [146.cpp](146.cpp) — Direct-address table + array-backed doubly-linked list | C++ | Accepted | 7<br>O(1) per get/put | 97.05% | 48.34<br>O(U + C) reserved | 47.97% |
| 146. LRU Cache | [146-stl.cpp](146-stl.cpp) — Unordered map + STL list of keys | C++ | Accepted | 19<br>O(1) average/amortized per get/put | 65.71% | 46.97<br>O(c) | 74.77% |
| 98. Validate Binary Search Tree | [98.cpp](98.cpp) — Recursive DFS with inclusive integer bounds | C++ | Accepted | 0<br>O(n) | 100.00% | 21.55<br>O(h) | 41.33% |
| 215. Kth Largest Element in an Array | [215.cpp](215.cpp) — Recursive quickselect with a fixed first-element pivot | C++ | Accepted | 2917<br>O(n²) worst case | 5.01% | 67.51<br>O(n) worst-case stack | 83.84% |
| 215. Kth Largest Element in an Array | [215-three-way.cpp](215-three-way.cpp) — Recursive three-way quickselect with a fixed first-element pivot | C++ | Accepted | 67<br>O(n²) worst case | 15.91% | 67.70<br>O(n) worst-case stack | 46.33% |
| 215. Kth Largest Element in an Array | [215-counting.cpp](215-counting.cpp) — Frequency counting over a bounded integer range | C++ | Accepted | 3<br>O(n + U) | 95.04% | 71.95<br>O(U) | 14.62% |
| 347. Top K Frequent Elements | [347.cpp](347.cpp) — Bounded-range frequency counting + max heap of distinct values | C++ | Accepted | 4<br>O(n + U + d log(d + 1)) | 37.75% | 19.90<br>O(U + d) | 5.04% |
| 347. Top K Frequent Elements | [347-min-heap.cpp](347-min-heap.cpp) — Hash-table frequency counting + size-k min heap | C++ | Accepted | 0<br>O(n + d log k) average/amortized | 100.00% | 17.75<br>O(d + k) | 46.00% |
| 23. Merge k Sorted Lists | [23.cpp](23.cpp) — Bounded-range counting + newly allocated output list | C++ | Accepted | 15<br>O(k + N + U) | 23.70% | 30.97<br>O(U), excluding output | 5.03% |
| 23. Merge k Sorted Lists | [23-heap.cpp](23-heap.cpp) — Min heap of current list nodes + in-place node relinking | C++ | Accepted | 3<br>O(k + N log k) | 70.49% | 18.03<br>O(k) | 81.38% |
| 207. Course Schedule | [207.cpp](207.cpp) — Kahn topological sort with adjacency lists and an indegree queue | C++ | Accepted | 7<br>O(V + E) | 50.55% | 19.74<br>O(V + E) | 23.01% |
| 743. Network Delay Time | [743.cpp](743.cpp) — Min-heap Dijkstra with settled-node filtering of duplicate candidates | C++ | Accepted | 94<br>O(V + E log E) | 30.95% | 48.87<br>O(V + E) | 5.04% |
| 743. Network Delay Time | [743-dist.cpp](743-dist.cpp) — Min-heap Dijkstra with tentative-distance pruning and settled flags | C++ | Accepted | 96<br>O(V + E log E) | 26.84% | 47.00<br>O(V + E) | 11.11% |
| 743. Network Delay Time | [743-scan.cpp](743-scan.cpp) — Linear-scan Dijkstra with adjacency lists | C++ | Accepted | 98<br>O(V² + E) | 23.75% | 46.82<br>O(V + E) | 14.95% |
| 743. Network Delay Time | [743-scan-ref.cpp](743-scan-ref.cpp) — Linear-scan Dijkstra with reference-based adjacency construction | C++ | Accepted | 76<br>O(V² + E) | 86.47% | 43.31<br>O(V + E) | 58.06% |
| 743. Network Delay Time | [743-heap-ref.cpp](743-heap-ref.cpp) — Min-heap Dijkstra with reference-based adjacency construction | C++ | Accepted | 88<br>O(V + E log E) | 45.83% | 45.45<br>O(V + E) | 17.26% |
| 39. Combination Sum | [39.cpp](39.cpp) — Memoized prefix/target DP storing all combinations | C++ | Accepted | 8<br>O(nT(L + 1) + S) | 14.87% | 19.46<br>O(nT + S) | 8.18% |
| 39. Combination Sum | [39-dfs.cpp](39-dfs.cpp) — DFS backtracking with nondecreasing candidate indices | C++ | Accepted | 3<br>O(N + n^(L+1) + RL), n ≥ 2 | 63.74% | 14.44<br>O(n + L + RL) | 28.77% |
| 56. Merge Intervals | [56.cpp](56.cpp) — Sort by start endpoint + linear merge scan | C++ | Accepted | 3<br>O(n log n) | 92.61% | 23.31<br>O(log n), excluding output | 75.37% |

## Recording rules

- List only completed, accepted implementations; keep practice frameworks out of the table.
- Use the latest accepted submission matching each implementation. Take runtime, memory, and both beat percentages from the same submission-detail page or screenshot; never combine the best values from different runs.
- Record observation dates and available submission timestamps/links in the source header. Use `N/A` for unavailable details. Keep the header and table consistent.
- Append new accepted implementations or resubmitted variants in submission order. Keep detailed algorithm and complexity notes in the source, rather than expanding this index with per-problem prose.
- Beat percentages compare submissions in the same language and can change over time. Judge timings are individual measurements; `0 ms` does not mean zero execution time.

Records come from signed-in LeetCode CN submission-detail pages or user-provided accepted screenshots. Initial records were captured on 2026-10-10; their accepted-source baseline is `f02e005cfcba17418e708199c27e9cf7af3bf3d5`.

## Table template

```markdown
| Problem | Implementation | Language | Status | Runtime (ms) | Runtime beats | Memory (MB) | Memory beats |
| --- | --- | --- | --- | ---: | ---: | ---: | ---: |
|  |  |  |  | value<br>O() |  | value<br>O() |  |
```
