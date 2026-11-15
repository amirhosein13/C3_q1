# Jigsaw Puzzle

**This is an interactive problem.**

| Time limit | Memory limit | Input / Output |
|:--:|:--:|:--:|
| 2 seconds | 256 MB | standard input / standard output (interactive) |

You have a box of jigsaw puzzle pieces numbered $1, 2, \ldots, n$.
The pieces can be assembled into one row, and in that row the $i$-th piece from the left is numbered $a_i$.
This is the only correct arrangement, but you have lost the reference picture, so you do not know the permutation $a$.

Luckily, you are an expert at jigsaw puzzles. When you arrange the $n$ pieces into one row, for every pair of adjacent
pieces you can tell whether they *fit together*. Two pieces fit together if they are adjacent in the correct arrangement
**and** their left-to-right order is the same as there.

You want to determine $a$ with a few *placements*. A placement goes as follows:

1. Choose a permutation $b_1, b_2, \ldots, b_n$ and put the pieces in a row in this order.
2. You obtain a binary string $c = c_1 c_2 \ldots c_{n-1}$, where $c_i = 1$ if and only if there exists
   $1 \le j \le n-1$ with $b_i = a_j$ and $b_{i+1} = a_{j+1}$; otherwise $c_i = 0$.

Determine $a$ using at most $q$ placements and report it. Reporting the answer does not count as a placement.
In the full problem $q = n - 1$ (see the subtasks).

## Interaction protocol

First, read one line with an integer $T$ — the number of test cases.

For each test case, read one line with two integers $n$ and $q$ — the number of pieces and the maximum number of
placements you may use in this test case. Then you may perform operations:

* **Placement:** print a line consisting of the character `?` followed by $b_1, b_2, \ldots, b_n$ (separated by spaces), where $b$ is a permutation of $1, \ldots, n$, and flush the output.
  Then read one line with a binary string $c$ of length $n-1$.
* **Report:** print a line consisting of the character `!` followed by $a_1, a_2, \ldots, a_n$ (separated by spaces) and flush the output. The current test case ends immediately;
  continue with the next test case or terminate if it was the last one.

If you make an invalid operation (malformed line, not a permutation, more than $q$ placements, …) or report a wrong
permutation, the interactor prints `-1` (instead of a binary string or the next test case) and stops.
Your program must then terminate immediately, otherwise the verdict is undefined.

The interactor is **not adaptive**: the permutation $a$ of every test case is fixed before the interaction starts.

Do not forget to flush after every line: `fflush(stdout)` or `cout.flush()` in C++ (`cout << endl` also flushes).

## Constraints

* $1 \le T \le 1000$
* $2 \le n \le 200$
* the sum of $n^2$ over all test cases of one input does not exceed $10^6$
* $q \in \{\, n-1,\ n,\ 2n \,\}$ as described in the subtasks

## Subtasks

| # | Score | Additional constraints |
|:-:|:-----:|:-----------------------|
| 1 | 10 | $n \le 3$, $q = n - 1$ |
| 2 | 15 | $q = 2n$ |
| 3 | 20 | $q = n$ |
| 4 | 25 | $n$ is odd, $q = n - 1$ |
| 5 | 30 | $q = n - 1$ (no additional constraints) |

Within a subtask, all test cases of all test files satisfy the constraints of that subtask.
You get the points of a subtask only if every test file of the subtask is solved correctly.

## Example

The hidden permutations are $a = (1, 4, 2, 3)$ for the first test case and $a = (3, 1, 4, 2, 5)$ for the second.

| Interactor prints | Your program prints |
|:--|:--|
| `2` | |
| `4 3` | |
| | `? 1 2 3 4` |
| `010` | |
| | `? 4 3 2 1` |
| `000` | |
| | `? 1 4 2 3` |
| `111` | |
| | `! 1 4 2 3` |
| `5 4` | |
| | `? 1 3 5 4 2` |
| `0001` | |
| | `? 3 2 1 4 5` |
| `0010` | |
| | `? 1 2 3 4 5` |
| `0000` | |
| | `? 5 3 1 4 2` |
| `0111` | |
| | `! 3 1 4 2 5` |

**Note.** In the first test case, placement $b = (1, 2, 3, 4)$ gives $c = 010$: only pieces 2 and 3 fit together.
Placement $b = (4, 3, 2, 1)$ gives $c = 000$. Placement $b = (1, 4, 2, 3)$ gives $c = 111$, so it is exactly the correct
arrangement, which is then reported. The placements in the example only illustrate the protocol; they are not
necessarily a good strategy.

## Local testing

The attachment contains `sample.in` (the hidden data of the example in the judge's format: $T$, then for each test case
a line `n q` and a line with $a$) and `local_interactor.cpp`. Compile both programs and connect them, e.g.

```
g++ -O2 -o sol your_solution.cpp
g++ -O2 -o interactor local_interactor.cpp
mkfifo f1 f2
./sol < f2 > f1 &
./interactor sample.in > f2 < f1
```
