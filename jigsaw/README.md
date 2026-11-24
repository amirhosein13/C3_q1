# Jigsaw Puzzle (interactive) — TPS task

Source: 2026 ICPC Asia Wuhan Regional, problem L. Prepared as an IOI-style task with subtasks for CMS.

* Task type: **Communication** (interactive, 1 process, contestant uses stdin/stdout), manager in `grader/manager.cpp`.
* Limits: **2 s**, **256 MiB**; `1 ≤ T ≤ 1000` (tightened from 10^4 to bound FIFO round trips), `2 ≤ n ≤ 200`,
  `Σ n² ≤ 10^6`, at most `q` placements (`q = n-1` in the full problem).
* Editorial (Persian, with hints): `editorial/editorial-fa.md` → `editorial/editorial.pdf` (`tools/build_editorial.sh`).
* Statement: Persian `statement/index-fa.md` → `statement/statement.pdf` (primary), English `statement/index.md` → `statement/statement-en.pdf`; solution idea: `SOLUTION.md`.
* Persian PDF uses the Vazirmatn font (`tools/fonts`, SIL OFL).
* CMS package (admin-panel upload only): `cms_upload/`, guide in Persian: `CMS_UPLOAD_GUIDE.md`.

| # | Score | Constraints | Idea |
|:-:|:-:|:--|:--|
| 1 | 10 | n ≤ 3, q = n−1 | case analysis / brute force |
| 2 | 15 | q = 2n | adaptive greedy on chains |
| 3 | 20 | q = n | test every ordered pair (Hamiltonian-path decomposition) |
| 4 | 25 | n odd, q = n−1 | Walecki cycles cut at ∞, deduce ∞'s successor |
| 5 | 30 | q = n−1 | + one extra vertex placed first and one adaptive final placement |

## Solutions (`solutions.json`, verified with `tps invoke`)

| solution | samples | 1 | 2 | 3 | 4 | 5 | score |
|:--|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| model.cpp | AC | AC | AC | AC | AC | AC | 100 |
| odd.cpp | WA | WA | AC | AC | AC | WA | 60 |
| cover.cpp | WA | WA | AC | AC | WA | WA | 35 |
| wa_guess.cpp | AC | WA | WA | WA | AC | WA | 25 |
| greedy.cpp | AC | WA | AC | WA | WA | WA | 15 |
| brute.cpp | AC | AC | WA | WA | WA | WA | 10 |
| tle_n4.cpp | AC | AC | TLE | TLE | TLE | TLE | 10 |
| wa_offbyone.cpp | WA | WA | WA | WA | WA | WA | 0 |
| wa_infirst.cpp | WA | WA | WA | WA | WA | WA | 0 |

(WA here also covers "too many placements".)

## Commands
* `tps gen` – generate tests; `tps invoke solution/<sol>.cpp` – judge a solution.
* `tools/verify_all.sh` – gen + invoke every solution, fails on any verdict mismatch.
* `tools/stress.sh [rounds]` – all permutations n ≤ 9 + random files through the real manager; brute on n ≤ 6.
* `tools/build_cms_package.sh` – rebuilds `cms_upload/` (tests.zip, static manager, statement.pdf, attachments)
  and runs `tools/verify_regex.py`.

Note: `scripts/templates/exec.cpp.sh` is customized so that TPS connects the solution's stdin/stdout to the FIFOs
(like CMS `std_io`).
