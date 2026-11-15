#!/usr/bin/env python3
"""Checks that every GroupMin regex in score_type.txt matches exactly the intended test codenames in tests.zip,
that every .in has a matching .out, and that every test is used by at least one group."""
import json, re, sys, zipfile
zpath, spath = sys.argv[1], sys.argv[2]
names = zipfile.ZipFile(zpath).namelist()
ins = sorted(n[:-3] for n in names if n.endswith('.in'))
outs = sorted(n[:-4] for n in names if n.endswith('.out'))
assert ins == outs, "every X.in needs X.out"
assert all('/' not in n for n in names), "zip must be flat"
params = json.loads(open(spath).read().strip())
# intended membership: subtask k uses its own tests "0k-*"; subtask 5 (full) also includes 00, 01, 04 (samples, small, odd)
intended = {0: {'00'}, 1: {'01'}, 2: {'02'}, 3: {'03'}, 4: {'04'}, 5: {'00', '01', '04', '05'}}
ok, used = True, set()
for k, (score, rx) in enumerate(params):
    got = [c for c in ins if re.match(rx, c)]          # CMS uses re.match on the codename
    want = [c for c in ins if c[:2] in intended[k]]
    used |= set(got)
    status = 'OK' if got == want else 'MISMATCH'
    ok &= got == want
    print(f"group {k}: score {score:>3}  regex {rx:<22} matches {len(got):>2} tests  [{status}]  {got[0]} .. {got[-1]}")
print("total score:", sum(p[0] for p in params), "| tests in zip:", len(ins), "| unused tests:", sorted(set(ins) - used))
ok &= sum(p[0] for p in params) == 100 and not (set(ins) - used)
print("ALL OK" if ok else "PROBLEMS FOUND"); sys.exit(0 if ok else 1)
