#!/bin/bash
# Builds jigsaw/cms_upload/ from the TPS task (run from anywhere, after `tps gen`).
set -euo pipefail
T="$(cd "$(dirname "$0")/.." && pwd)"
O="$T/cms_upload"
W="$(mktemp -d)"
mkdir -p "$O/attachments" "$W/tests"
# 1) tests: TPS name "S-NN" -> "0S-NN"; .out = the hidden permutations (the manager ignores it)
for f in "$T"/tests/*.in; do
  b="$(basename "$f" .in)"; s="${b%%-*}"; t="${b#*-}"; nb="$(printf '%02d-%s' "$s" "$t")"
  cp "$f" "$W/tests/$nb.in"
  awk 'NR>1 && NR%2==1' "$f" > "$W/tests/$nb.out"
done
rm -f "$O/tests.zip"; (cd "$W/tests" && zip -q -X "$O/tests.zip" *.in *.out)
# 2) manager: static binary + source
g++ -O2 -static -std=gnu++17 -o "$O/manager" "$T/grader/manager.cpp"
cp "$T/grader/manager.cpp" "$O/manager.cpp"
# 3) statement
pandoc "$T/statement/index.md" -s --metadata title="Jigsaw Puzzle" -c "$T/tools/statement.css" --self-contained -o "$W/statement.html" 2>/dev/null \
  || pandoc "$T/statement/index.md" -s --metadata title="Jigsaw Puzzle" -c "$T/tools/statement.css" --embed-resources --standalone -o "$W/statement.html"
sed -i 's|<header id="title-block-header">.*</header>||; /<header id="title-block-header">/,/<\/header>/d' "$W/statement.html"
node "$T/tools/make_pdf.js" "$W/statement.html" "$O/statement.pdf"
cp "$O/statement.pdf" "$T/statement/statement.pdf"
# 4) attachments
cp "$T/public/examples/sample.in" "$O/attachments/sample.in"
cp "$T/public/local_interactor.cpp" "$O/attachments/local_interactor.cpp"
rm -rf "$W"
python3 "$T/tools/verify_regex.py" "$O/tests.zip" "$O/score_type.txt"
