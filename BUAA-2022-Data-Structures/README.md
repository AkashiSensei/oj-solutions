# BUAA 2022 Data Structures Coursework

Historical C coursework imported on 2026-10-14 from the original data-structures assignment directory. The year follows the March 2022 timestamps of the source files.

## Directory structure

```text
BUAA-2022-Data-Structures/
├── 1-1.c ... 1-5.c
├── 2-1.c ... 2-5.c
├── 3-1.c, 3-2.c, 3-3.c, 3.4.c, 3-5.c
├── 4-1.c ... 4-5.c
├── 5-1.c ... 5-4.c
├── 6-1.c ... 6-3.c
├── 7-1.c ... 7-3.c
├── major-project.c
├── minor-project.c
└── README.md
```

The archive contains 32 C source files. Original exercise filenames, including `3.4.c`, are retained; `大作业.c` and `小作业.c` are renamed to `major-project.c` and `minor-project.c`, respectively. The redundant nested `代码作业/` wrapper is omitted. The two closely related project versions remain separate.

## Source index

The descriptions below and the brief English file headers are inferred from the existing implementations rather than verified original problem statements. Existing inline comments are preserved. These historical working files have not been newly validated as correct, complete, accepted, or compatible with current compilers.

| Source | Purpose |
| --- | --- |
| [1-1.c](1-1.c) | String range expansion |
| [1-2.c](1-2.c) | Arithmetic expression evaluation |
| [1-3.c](1-3.c) | Scientific notation |
| [1-4.c](1-4.c) | Integer subtraction |
| [1-5.c](1-5.c) | Permutation generation |
| [2-1.c](2-1.c) | Four-in-a-row detection |
| [2-2.c](2-2.c) | File substring replacement |
| [2-3.c](2-3.c) | Keyword substitution cipher |
| [2-4.c](2-4.c) | Phone directory cleanup |
| [2-5.c](2-5.c) | Book catalog management |
| [3-1.c](3-1.c) | Endpoint-matched segment chains |
| [3-2.c](3-2.c) | Josephus elimination |
| [3-3.c](3-3.c) | Polynomial multiplication |
| [3-5.c](3-5.c) | Word frequencies with an array |
| [3.4.c](3.4.c) | Circular-list substitution cipher |
| [4-1.c](4-1.c) | Array stack |
| [4-2.c](4-2.c) | Source bracket matching |
| [4-3.c](4-3.c) | Expression evaluation with two stacks |
| [4-4.c](4-4.c) | Text editing and undo |
| [4-5.c](4-5.c) | Service queue simulation |
| [5-1.c](5-1.c) | BST leaf depths |
| [5-2.c](5-2.c) | Word frequencies with a BST |
| [5-3.c](5-3.c) | Expression tree and postfix evaluation |
| [5-4.c](5-4.c) | Printer routing in a device tree |
| [6-1.c](6-1.c) | Dictionary search comparison |
| [6-2.c](6-2.c) | Record number adjustment |
| [6-3.c](6-3.c) | Sorting methods and counters |
| [7-1.c](7-1.c) | DFS and BFS around vertex deletion |
| [7-2.c](7-2.c) | Enumerating simple graph paths |
| [7-3.c](7-3.c) | Minimum spanning tree |
| [major-project.c](major-project.c) | Frequency-based text summarization |
| [minor-project.c](minor-project.c) | Frequency-based text summarization variant |

## External files

Several exercises read or write files in their working directory. Those data files were not present in this source collection and are not generated during import.

| Sources | Input files | Output files |
| --- | --- | --- |
| `2-2.c` | `filein.txt` | `fileout.txt` |
| `2-3.c` | `encrypt.txt` | `output.txt` |
| `2-5.c` | `books.txt` | `ordered.txt` |
| `3.4.c` | `in.txt` | `in_crpyt.txt` |
| `3-5.c`, `5-2.c` | `article.txt` | Standard output |
| `4-2.c` | `example.c` | Standard output |
| `5-4.c` | `in.txt` | Standard output |
| `6-1.c` | `dictionary3000.txt` | Standard output |
| `6-2.c` | `in.txt` | `out.txt` |
| `major-project.c`, `minor-project.c` | `article.txt`, `stopwords.txt` | `results.txt` and standard output |

## Import scope and preservation

Only the 32 `.c` files are imported. The Windows executable `4-5.exe`, the seven JPEG course screenshots, and `.DS_Store` are excluded. No separate standard-answer or reference-code collection was found among the source files.

Each file receives an ASCII-only descriptive header. Removing that added header leaves a source body verified byte-for-byte against the original OneDrive file. Existing code, inline comments, line endings, and encodings remain unchanged, and the OneDrive originals are untouched. In particular, `major-project.c` and `minor-project.c` retain their original non-UTF-8 Chinese encoding, readable with GB18030-compatible decoding.
