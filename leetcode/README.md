# LeetCode Solutions

Initial records were captured on **2026-10-10** from the signed-in LeetCode CN submission-detail pages. The LC 3 and LC 739 records were added on **2026-10-11** from user-provided accepted-submission screenshots; their submission times and links are unavailable and recorded as `N/A` in the source comments. The LC 146 array and STL records were added on **2026-10-12** from user-provided accepted-submission screenshots; their submission times and links are likewise recorded as `N/A`. The LC 98 record was added on **2026-10-13** from a user-provided accepted-submission screenshot; its submission time and link are recorded as `N/A`. The LC 215 two-way, three-way, and counting records were added on **2026-10-14** from user-provided accepted-submission screenshots; their submission times and links are recorded as `N/A`. Accepted rows follow submission order, oldest first, to show the progression of approaches and optimizations. Only completed, accepted implementations are listed. Submission timestamps remain in source comments (Asia/Shanghai). Initial accepted-source baseline: `f02e005cfcba17418e708199c27e9cf7af3bf3d5`.

## Implementation index

Each accepted row is matched to the local solution code, excluding comments, includes, and local `main()` test code. All four performance values in a row come from the same submission-detail page or accepted-submission screenshot, not the rounded submission list. Each source file also contains a matching English `Submission Record` in its problem-header comment. In the Runtime and Memory cells, the first line is the measured value and the second line is the analyzed complexity. For islands, `m` and `n` are the grid dimensions and `L` is the number of land cells. For one-dimensional array and string problems, `n` is the input length. Space complexity describes auxiliary storage excluding input copies; LC 3 takes its string by value, so an lvalue call also creates an O(n) input copy, as noted in its source comment. LC 739 uses up to O(n) stack entries, excluding its O(n) returned answer array. For `739-array.cpp` and `739-array-day.cpp`, `C = 100005` is the fixed global stack capacity: each buffer reserves O(C) auxiliary storage even when only O(n) entries are used. The former stores two integers per entry; the latter stores only the day index. For `146.cpp`, `U = 10001` is the direct-address table length and `C = 3001` is the reserved list-slot count. Each cache object reserves O(U + C) storage and takes O(U + C) construction time to zero-initialize its arrays. Each `get` and `put` takes O(1) worst-case time; q operations including construction take O(U + C + q). The arrays are per-instance members, not shared globals. For `146-stl.cpp`, `c` is the configured capacity. The unordered map and list use O(c) auxiliary space. Each get/put takes average/amortized O(1) time, with O(c) worst-case time; moving an existing list node with splice is O(1) and preserves its iterator. Empty-container construction takes O(1) time. For `98.cpp`, `n` is the tree node count and `h` is the tree height. Recursive DFS takes O(n) worst-case time and O(h) auxiliary stack space, which is O(log n) for balanced trees and O(n) for skewed trees. For `215.cpp`, each partition is in place, but the fixed first-element pivot and one-sided handling of equal values can produce O(n²) worst-case time and O(n) recursion stack space. Balanced shrinking intervals give O(n) time and O(log n) stack space; this version has no randomized expected-time guarantee. For `215-three-way.cpp`, equal values are grouped and excluded together, making all-equal inputs O(n) time with O(1) recursive depth. Its pivot is still fixed, so distinct-value extreme partitions can still cause O(n²) time and O(n) stack space; balanced shrinking intervals give O(n) time and O(log n) stack space. For `215-counting.cpp`, `U = 20002` is the counting-buffer length (20001 valid value buckets plus one unused zero slot). Initialization and the descending scan take O(U) time, counting takes O(n), and auxiliary space is O(U), for O(n + U) total time. The bounded value range makes U constant with respect to n; each call creates fresh counters and leaves the input unchanged.

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

## Recording rules

- Record the latest accepted submission that matches the repository version, not the best runtime or memory selected from unrelated submissions.
- Keep the implementation filename, approach, language, status, runtime, memory, both beat percentages, and observation date in the index. Keep submission timestamps and links in each source file's `Submission Record`, not in the index table.
- Sort accepted rows by submission time, earliest first, rather than problem number or performance.
- Keep source comments and this index consistent. Comments describe the current implementation; retain earlier submission rows and source commits as history.
- For later additions, append a row to the index table. If a solution changes and is resubmitted, append another row and update its source comment with the matching result.
- Add an implementation only after it is complete and a matching submission is accepted. Keep unfinished frameworks out of the index. For unavailable metrics on accepted submissions, use `N/A`; never invent values or substitute zero.
- Beat percentages are LeetCode's displayed comparisons for the same problem and language; higher is better. They are not an absolute rank or contest rating and can change after the submission date.
- These are individual judge-run snapshots, not stable benchmark results. A displayed runtime of `0 ms` does not mean zero execution time. Compare language, algorithmic complexity, and judge variation before interpreting small differences.
- This index covers LeetCode solutions. Codeforces has a separate judging system and is not mixed into these percentages.

## Table template

Append a row to the index table, and fill it from the matching submission-detail page:

```markdown
| Problem | Implementation | Language | Status | Runtime (ms) | Runtime beats | Memory (MB) | Memory beats |
| --- | --- | --- | --- | ---: | ---: | ---: | ---: |
|  |  |  |  | value<br>O() |  | value<br>O() |  |
```
