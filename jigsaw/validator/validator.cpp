#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
// Global constraints. Optional argument "--group <subtask>" adds subtask constraints.
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    string g;
    for (int i = 1; i + 1 < argc; i++) if (string(argv[i]) == "--group") g = argv[i + 1];
    int T = inf.readInt(1, 1000, "T"); inf.readEoln();
    long long s = 0;
    for (int tc = 0; tc < T; tc++) {
        int n = inf.readInt(2, 200, "n"); inf.readSpace();
        int q = inf.readInt(1, 400, "q"); inf.readEoln();
        ensuref(q == n - 1 || q == n || q == 2 * n, "q must be n-1, n or 2n");
        vector<int> a = inf.readInts(n, 1, n, "a"); inf.readEoln();
        vector<int> b = a; sort(b.begin(), b.end());
        for (int i = 0; i < n; i++) ensuref(b[i] == i + 1, "a is not a permutation (test case %d)", tc + 1);
        s += 1LL * n * n;
        if (g == "samples" || g == "full") ensuref(q == n - 1, "q must be n-1");
        else if (g == "small") { ensuref(n <= 3, "n<=3"); ensuref(q == n - 1, "q must be n-1"); }
        else if (g == "q2n") ensuref(q == 2 * n, "q must be 2n");
        else if (g == "qn") ensuref(q == n, "q must be n");
        else if (g == "odd") { ensuref(n % 2 == 1, "n must be odd"); ensuref(q == n - 1, "q must be n-1"); }
        else ensuref(g.empty(), "unknown group");
    }
    ensuref(s <= 1000000, "sum of n^2 exceeds 1e6");
    inf.readEof();
}
