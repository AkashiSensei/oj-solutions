# BUAA 2022 Algorithm Coursework

Historical C/C++ solutions, practice programs, and supporting code from BUAA algorithm coursework, imported on 2026-10-14. The year in this directory name follows the November 2022 timestamps in the original course archive.

## Directory structure

```text
BUAA-2022-Algorithm/
├── C1/
├── C2/
├── C3/
├── C4/
├── C5/
├── C6/
├── E1/
├── E2/
├── E3/
├── E4/
├── E5/
├── final/
├── mock/
├── mock2/
├── practice/
├── prepare/
│   └── sort/
└── README.md
```

`C1` through `C6` and `E1` through `E5` preserve the original exercise-group codes rather than introducing new topic categories. `final/`, `mock/`, and `mock2/` retain the corresponding final and mock groups. `practice/` contains additional exercises such as BFS, DFS, and binary search; `prepare/sort/` contains sorting preparation and random-input generation programs. Alternate implementations and drafts remain next to their original group files.

## Contents

The archive contains 91 source files. Original directory names, filenames, alternate versions, and drafts are preserved. Each source file has a brief English header describing its purpose as inferred from the code; unfinished drafts, placeholders, and helper programs are identified accordingly. These are historical working files; inclusion does not imply that every file is complete, independently compilable, or accepted by the original judge. No new acceptance or performance claims are assigned during import.

| Original group | Source files | Directory |
| --- | ---: | --- |
| `C1` | 3 | [C1/](C1/) |
| `C2` | 5 | [C2/](C2/) |
| `C3` | 4 | [C3/](C3/) |
| `C4` | 9 | [C4/](C4/) |
| `C5` | 8 | [C5/](C5/) |
| `C6` | 8 | [C6/](C6/) |
| `E1` | 6 | [E1/](E1/) |
| `E2` | 5 | [E2/](E2/) |
| `E3` | 3 | [E3/](E3/) |
| `E4` | 14 | [E4/](E4/) |
| `E5` | 4 | [E5/](E5/) |
| `final` | 10 | [final/](final/) |
| `mock` | 3 | [mock/](mock/) |
| `mock2` | 2 | [mock2/](mock2/) |
| `practice` | 5 | [practice/](practice/) |
| `prepare` | 2 | [prepare/](prepare/) |

## Import scope

Only C/C++ source and header files from the selected exercise directories are included. The original OneDrive files remain unchanged.

- Excluded `Standard/`, which contains the standard answers.
- Excluded `E5/fang/`, `E5/E5zzq/`, `E5/E5.zip`, and the top-level `template/` directory, as requested because their provenance is unclear.
- Excluded `C6/CC.cpp`, which contains the `zzq` identifier and was included in the same provenance exclusion.
- Excluded executables, archives, editor configuration, operating-system metadata, test-data text files, and the generated `tempCodeRunnerFile.c` fragment.
- Retained filenames such as `bcopy.c` and `f (2).cpp` as historical variants; they are not classified as standard answers based on their names alone.

The imported source files were initially checked byte-for-byte against the selected originals. After adding the descriptive headers, every original source body was verified to remain byte-for-byte unchanged. These headers summarize the existing code rather than reproduce verified original problem statements; the existing logic and platform assumptions have not been changed.
