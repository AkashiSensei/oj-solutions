# LeetCode Solutions

Recorded on **2026-10-10** from the signed-in LeetCode CN submission-detail pages.
Accepted rows follow submission order, oldest first, to show the progression
of approaches and optimizations. Only completed, accepted implementations are listed.
Submission timestamps remain in source comments (Asia/Shanghai).
Accepted-source baseline: `f02e005cfcba17418e708199c27e9cf7af3bf3d5`.

## Implementation index

Each accepted row is matched to the local solution code, excluding comments,
includes, and local `main()` test code. All four performance values in a row
come from the same submission-detail page, not the rounded submission list.
Each source file also contains a matching English `Submission Record` in its
problem-header comment.

| Problem | Implementation | Language | Status | Runtime (ms) | Runtime beats | Memory (MB) | Memory beats | Submission |
| --- | --- | --- | --- | ---: | ---: | ---: | ---: | --- |
| 42. Trapping Rain Water | [42.c](42.c) — Suffix maxima + running prefix maximum | C | Accepted | 0 | 100.00% | 10.38 | 28.65% | [752510213](https://leetcode.cn/problems/trapping-rain-water/submissions/752510213/) |
| 42. Trapping Rain Water | [42-opt.c](42-opt.c) — Two pointers comparing running maxima | C | Accepted | 0 | 100.00% | 10.25 | 73.59% | [752514017](https://leetcode.cn/problems/trapping-rain-water/submissions/752514017/) |
| 42. Trapping Rain Water | [42.cpp](42.cpp) — Two pointers comparing boundary heights | C++ | Accepted | 0 | 100.00% | 25.52 | 65.47% | [752574872](https://leetcode.cn/problems/trapping-rain-water/submissions/752574872/) |
| 42. Trapping Rain Water | [42.go](42.go) — Two pointers comparing boundary heights | Go | Accepted | 0 | 100.00% | 7.89 | 15.19% | [752590689](https://leetcode.cn/problems/trapping-rain-water/submissions/752590689/) |
| 198. House Robber | [198.cpp](198.cpp) — Dynamic programming with rolling states | C++ | Accepted | 0 | 100.00% | 9.78 | 99.39% | [753639575](https://leetcode.cn/problems/house-robber/submissions/753639575/) |
| 200. Number of Islands | [200-bfs.cpp](200-bfs.cpp) — BFS with a set of unvisited land | C++ | Accepted | 77 | 5.05% | 28.64 | 5.01% | [753821806](https://leetcode.cn/problems/number-of-islands/submissions/753821806/) |
| 200. Number of Islands | [200-dfs.cpp](200-dfs.cpp) — Iterative DFS with in-place marking | C++ | Accepted | 23 | 90.85% | 17.01 | 28.20% | [753825122](https://leetcode.cn/problems/number-of-islands/submissions/753825122/) |

## Recording rules

- Record the latest accepted submission that matches the repository version, not
  the best runtime or memory selected from unrelated submissions.
- Keep the implementation filename, approach, language, status, submission ID/link,
  runtime, memory, both beat percentages, and observation date. Keep submission
  timestamps in each source file's `Submission Record`, not in the index table.
- Sort accepted rows by submission time, earliest first, rather than problem
  number or performance.
- Keep source comments and this index consistent. Comments describe the current
  implementation; retain earlier submission rows and source commits as history.
- For later additions, record the observation date and source commit in a new dated
  section using the same table columns. If a solution changes and is resubmitted,
  append a new row there and update its source comment with the matching result.
- Add an implementation only after it is complete and a matching submission is
  accepted. Keep unfinished frameworks out of the index. For unavailable metrics
  on accepted submissions, use `N/A`; never invent values or substitute zero.
- Beat percentages are LeetCode's displayed comparisons for the same problem and
  language; higher is better. They are not an absolute rank or contest rating and
  can change after the submission date.
- These are individual judge-run snapshots, not stable benchmark results. A
  displayed runtime of `0 ms` does not mean zero execution time. Compare language,
  algorithmic complexity, and judge variation before interpreting small differences.
- This index covers LeetCode solutions. Codeforces has a separate judging system
  and is not mixed into these percentages.

## Table template

Copy this table into a new dated section, record the source commit, and fill it
from the matching submission-detail page:

```markdown
| Problem | Implementation | Language | Status | Runtime (ms) | Runtime beats | Memory (MB) | Memory beats | Submission |
| --- | --- | --- | --- | ---: | ---: | ---: | ---: | --- |
|  |  |  |  |  |  |  |  |  |
```
