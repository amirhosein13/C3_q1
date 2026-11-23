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
# 3) statements: statement.pdf = Persian (primary, CMS language code "fa"), statement-en.pdf = English ("en")
mkpdf() { # mkpdf <md> <css> <title> <lang> <dir> <out.pdf>
  (cd "$T/tools" && pandoc "$1" -s --metadata title="$3" --metadata lang="$4" --metadata dir="$5" -c "$2" \
     --embed-resources --standalone -o "$W/st.html")
  sed -i '/<header id="title-block-header">/,/<\/header>/d' "$W/st.html"
  node "$T/tools/make_pdf.js" "$W/st.html" "$6"
}
mkpdf "$T/statement/index-fa.md" statement-fa.css "پازل" fa rtl "$O/statement.pdf"
mkpdf "$T/statement/index.md" statement.css "Jigsaw Puzzle" en ltr "$O/statement-en.pdf"
cp "$O/statement.pdf" "$T/statement/statement.pdf"
cp "$O/statement-en.pdf" "$T/statement/statement-en.pdf"
# 4) attachments
cp "$T/public/examples/sample.in" "$O/attachments/sample.in"
cp "$T/public/local_interactor.cpp" "$O/attachments/local_interactor.cpp"
rm -rf "$W"
python3 "$T/tools/verify_regex.py" "$O/tests.zip" "$O/score_type.txt"
