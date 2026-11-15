# Jigsaw Puzzle — solution notes

## Reformulation
The hidden permutation is a directed Hamiltonian path `P` on the pieces. A placement `b` is also a Hamiltonian
path; the answer string reveals exactly which arcs `b_i -> b_{i+1}` belong to `P`. Every placement *tests*
`n-1` ordered pairs. There are `n(n-1)` ordered pairs and only `n-1` placements, i.e. `(n-1)^2` tests — exactly
`n-1` pairs can stay untested, so the placements must be (almost) a perfect decomposition.

## Odd n (subtask 4)
Take a special vertex `∞ = n` and put the other `n-1 = 2r` vertices on a circle `0..2r-1`.
The Walecki zig-zags `Z_i = i, i+1, i-1, i+2, i-2, ..., i+r` (`i = 0..r-1`) partition the undirected complete
graph on the circle into `r` Hamiltonian paths. Ask `Z_i, ∞` and `reverse(Z_i), ∞` for every `i`
(`2r = n-1` placements). Every ordered pair is tested exactly once **except the pairs `∞ -> x`**.
So every arc of `P` is found except possibly the arc leaving `∞`. Then either one chain remains (done) or two
chains remain; the one ending with `∞` must come first (the other order was tested and is absent).
(This is a Hamiltonian-cycle decomposition of the complete digraph cut at `∞`.)

## Even n (full)
`K_n*` has no Hamiltonian-cycle decomposition for `n = 4, 6`, and general constructions (Tillson) are heavy,
so we use one adaptive placement instead. Let `w = n` and run the odd construction on `1..n-1` (`∞ = n-1`),
always putting `w` **first**: `n-2` placements. Now the only untested pairs are: everything into `w`,
`w -> ∞`, and everything out of `∞`. Hence at most 3 arcs of `P` are unknown, the found arcs form at most
4 chains, and enumerating all orders of the chains that use only untested links leaves at most 3 candidates.
Among all orders of the (≤ 4) chains there is always one placement giving pairwise different answers on the
candidates; ask it (placement `n-1`) and report. This was verified exhaustively for every permutation with
`n ≤ 10` and on many random tests up to `n = 200`.

Complexity: `O(n^2)` per test case (output size), so `O(sum n^2)` total.

## Partial ideas
* Subtask 1 (`n ≤ 3`): case analysis, or brute force over all consistent permutations (`brute.cpp`).
* Subtask 2 (`q = 2n`): adaptive greedy — lay out the current chains so that each chain end is followed by a
  start that has not been tested with it yet (`greedy.cpp`, ≤ ~1.3n placements; fails `q = n` already for `n = 4`).
* Subtask 3 (`q = n`): test **every** ordered pair: even `n` – the `n/2` zig-zag Hamiltonian paths of `K_n` in both
  directions; odd `n` – Walecki cycles plus one more placement (`cover.cpp`).
* Subtask 4: the odd construction with the "∞ is never tested" deduction (`odd.cpp`).
