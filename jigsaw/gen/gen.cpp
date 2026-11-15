// Usage: gen <type> <qmode> <nmin> <nmax> <Tmax> <sumN2> <parity> <seedtag> [chunk]
//   type all: enumerates every permutation of every allowed n in [nmin,nmax] (lexicographic, n increasing)
//             and outputs block number <chunk> (0-based) of size Tmax of that list
//   type  : random | max | identity | reverse | all | special | zigzag | blocks | mixed
//   qmode : n1 (q=n-1) | n (q=n) | 2n (q=2n)
//   parity: any | odd | even  (restricts n)
#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
string type, qmode, parity;
int nmin, nmax, Tmax; long long S;
vector<pair<int, vector<int>>> out;

bool okN(int n) { return parity == "any" || (parity == "odd") == (n % 2 == 1); }
int pickN() {
    while (true) { int n = rnd.next(nmin, nmax); if (okN(n)) return n; }
}
int qOf(int n) { return qmode == "n1" ? n - 1 : qmode == "n" ? n : 2 * n; }
vector<int> randPerm(int n) { vector<int> a(n); iota(a.begin(), a.end(), 1); shuffle(a.begin(), a.end()); return a; }

// Walecki zig-zag order of the "odd part" (elements 1..m, m odd; m is special), optionally with n as w.
vector<int> zigzag(int n) {
    int m = n % 2 ? n : n - 1, r = (m - 1) / 2;
    vector<int> b;
    if (r == 0) { b.push_back(1); }
    else {
        int i = rnd.next(0, r - 1);
        vector<int> z{i};
        for (int k = 1; k <= r; k++) { z.push_back((i + k) % (2 * r)); if (k < r) z.push_back((i - k + 2 * r) % (2 * r)); }
        if (rnd.next(2)) reverse(z.begin(), z.end());
        for (int x : z) b.push_back(x + 1);
        b.push_back(m);
    }
    if (n % 2 == 0) b.insert(b.begin(), n);
    int t = rnd.next(4);  // variants: as is, rotated, reversed, w moved
    if (t == 1) rotate(b.begin(), b.begin() + rnd.next(0, n - 1), b.end());
    if (t == 2) reverse(b.begin(), b.end());
    if (t == 3 && n % 2 == 0) { b.erase(b.begin()); b.insert(b.begin() + rnd.next(0, n - 1), n); }
    return b;
}
// Special structure around the special elements m (=n if odd, n-1 if even) and w (=n if even).
vector<int> special(int n) {
    int m = n % 2 ? n : n - 1, w = n % 2 ? 0 : n;
    vector<int> a = randPerm(n);
    auto moveTo = [&](int x, int pos) { a.erase(find(a.begin(), a.end(), x)); a.insert(a.begin() + pos, x); };
    int t = rnd.next(8);
    if (t == 0) moveTo(m, n - 1);
    else if (t == 1) moveTo(m, 0);
    else if (t == 2 && w) moveTo(w, 0);
    else if (t == 3 && w) moveTo(w, n - 1);
    else if (t == 4 && w) { a.erase(find(a.begin(), a.end(), w)); int p = find(a.begin(), a.end(), m) - a.begin(); a.insert(a.begin() + p + 1, w); }
    else if (t == 5 && w) { a.erase(find(a.begin(), a.end(), w)); int p = find(a.begin(), a.end(), m) - a.begin(); a.insert(a.begin() + p, w); }
    else if (t == 6 && w) { moveTo(w, 0); moveTo(m, n - 1); }
    else if (t == 7 && w) { moveTo(m, 0); moveTo(w, n - 1); }
    return a;
}
// a few long increasing / decreasing runs (structured, "almost sorted")
vector<int> blocks(int n) {
    vector<int> a(n); iota(a.begin(), a.end(), 1);
    int k = rnd.next(1, min(n, 6));
    vector<int> cut{0, n};
    for (int i = 1; i < k; i++) cut.push_back(rnd.next(1, n - 1));
    sort(cut.begin(), cut.end()); cut.erase(unique(cut.begin(), cut.end()), cut.end());
    vector<vector<int>> parts;
    for (size_t i = 0; i + 1 < cut.size(); i++) {
        vector<int> p(a.begin() + cut[i], a.begin() + cut[i + 1]);
        if (rnd.next(2)) reverse(p.begin(), p.end());
        parts.push_back(p);
    }
    shuffle(parts.begin(), parts.end());
    vector<int> b; for (auto &p : parts) b.insert(b.end(), p.begin(), p.end());
    return b;
}
vector<int> make(const string &t, int n) {
    if (t == "random" || t == "max") return randPerm(n);
    if (t == "identity") { vector<int> a(n); iota(a.begin(), a.end(), 1); return a; }
    if (t == "reverse") { vector<int> a(n); iota(a.rbegin(), a.rend(), 1); return a; }
    if (t == "special") return special(n);
    if (t == "zigzag") return zigzag(n);
    if (t == "blocks") return blocks(n);
    // mixed
    int c = rnd.next(5);
    return make(c == 0 ? "random" : c == 1 ? "special" : c == 2 ? "zigzag" : c == 3 ? "blocks" : (rnd.next(2) ? "identity" : "reverse"), n);
}
int main(int argc, char **argv) {
    registerGen(argc, argv, 1);
    type = argv[1]; qmode = argv[2]; nmin = atoi(argv[3]); nmax = atoi(argv[4]);
    Tmax = atoi(argv[5]); S = atoll(argv[6]); parity = argv[7];
    long long used = 0;
    if (type == "all") {  // every permutation of every allowed n in [nmin, nmax]
        long long chunk = argc > 9 ? atoll(argv[9]) : 0, idx = 0;
        for (int n = nmin; n <= nmax; n++) if (okN(n)) {
            vector<int> a(n); iota(a.begin(), a.end(), 1);
            do {
                if (idx++ / Tmax != chunk) continue;
                if ((int)out.size() < Tmax && used + 1LL * n * n <= S) { out.push_back({n, a}); used += 1LL * n * n; }
            } while (next_permutation(a.begin(), a.end()));
        }
        ensuref(!out.empty(), "empty chunk");
        shuffle(out.begin(), out.end());
    } else {
        while ((int)out.size() < Tmax) {
            int n = type == "max" ? nmax : pickN();
            if (type == "max" && !okN(n)) n--;
            if (used + 1LL * n * n > S) {
                // try to fill the remaining budget with the largest n that fits
                long long rem = S - used; int f = (int)sqrtl((long double)rem);
                while (f >= nmin && (1LL * f * f > rem || !okN(f))) f--;
                if (f < nmin || f < 2) break;
                n = f;
            }
            out.push_back({n, make(type, n)}); used += 1LL * n * n;
        }
    }
    printf("%d\n", (int)out.size());
    for (auto &[n, a] : out) {
        printf("%d %d\n", n, qOf(n));
        for (int i = 0; i < n; i++) printf("%d%c", a[i], i + 1 < n ? ' ' : '\n');
    }
}
