#!/bin/bash
# Stress test: model (and brute for n<=6) against the real manager through FIFOs.
#  - every permutation for n = 2..9 (the manager accepts any T, no validator involved)
#  - <rounds> random files with up to 1000 test cases, n in [2, 40]
set -euo pipefail
T="$(cd "$(dirname "$0")/.." && pwd)"; W="$(mktemp -d)"; rounds="${1:-200}"
g++ -O2 -std=gnu++17 -o "$W/manager" "$T/grader/manager.cpp"
g++ -O2 -std=gnu++17 -o "$W/gen" "$T/gen/gen.cpp" -I"$T/gen"
for s in model brute; do g++ -O2 -std=gnu++17 -o "$W/$s" "$T/solution/$s.cpp"; done
run() { # run <exe> <input>
  rm -f "$W/a" "$W/b"; mkfifo "$W/a" "$W/b"
  "$1" < "$W/b" > "$W/a" & "$W/manager" "$W/a" "$W/b" < "$2" > "$W/score" 2> "$W/msg"; wait
  [ "$(cat "$W/score")" = "1.0" ] || { echo "FAILED $1 on $2: $(head -2 "$W/msg")"; cp "$2" "$T/stress_failed.in"; exit 1; }
}
for n in 2 3 4 5 6 7 8 9; do "$W/gen" all n1 $n $n 1000000 1000000000000 any x > "$W/in"; run "$W/model" "$W/in"; echo "n=$n all permutations OK"; done
"$W/gen" all n1 2 6 100000 1000000000 any x > "$W/in"; run "$W/brute" "$W/in"; echo "brute: all permutations n<=6 OK"
for i in $(seq 1 "$rounds"); do "$W/gen" mixed n1 2 40 1000 1000000 any r$i > "$W/in"; run "$W/model" "$W/in"; done
echo "$rounds random files OK"; rm -rf "$W"
