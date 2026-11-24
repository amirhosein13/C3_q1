#!/bin/bash
# Builds editorial/editorial.pdf (Persian) from editorial/editorial-fa.md + solution/model.cpp
set -euo pipefail
T="$(cd "$(dirname "$0")/.." && pwd)"; W="$(mktemp -d)"
python3 "$T/tools/editorial_figures.py" "$T/editorial/img"
python3 - "$T" "$W/ed.md" <<'PY'
import sys
t, out = sys.argv[1], sys.argv[2]
md = open(f"{t}/editorial/editorial-fa.md").read()
code = open(f"{t}/solution/model.cpp").read()
open(out, "w").write(md.replace("CODE_PLACEHOLDER", "```cpp\n" + code + "```"))
PY
cp -r "$T/editorial/img" "$W/img"
(cd "$T/tools" && pandoc "$W/ed.md" -s --metadata title="پازل — راه‌حل تشریحی" --metadata lang=fa --metadata dir=rtl \
   --resource-path="$W:$T/tools" -c editorial.css --embed-resources --standalone --no-highlight --mathml -o "$W/ed.html")
sed -i '/<header id="title-block-header">/,/<\/header>/d' "$W/ed.html"
node "$T/tools/make_pdf.js" "$W/ed.html" "$T/editorial/editorial.pdf"
rm -rf "$W"; echo "editorial/editorial.pdf"
