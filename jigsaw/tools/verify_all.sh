#!/bin/bash
# Generates the tests and invokes every solution of solutions.json; TPS prints "match with expected" per subtask.
set -uo pipefail
cd "$(dirname "$0")/.."
tps gen || exit 1
fail=0
for s in $(python3 -c 'import json;print(" ".join(json.load(open("solutions.json"))))'); do
  echo "=== $s"
  out=$(tps invoke "solution/$s" 2>&1)
  echo "$out" | grep -E "^(samples|small|q2n|qn|odd|full) |/100"
  echo "$out" | grep -E "^(samples|small|q2n|qn|odd|full) " | grep -qv "match with expected" && { echo "!!! MISMATCH for $s"; fail=1; }
done
exit $fail
