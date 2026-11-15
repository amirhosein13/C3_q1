// Local interactor for "Jigsaw Puzzle" (for contestants' own testing only).
// Usage: ./interactor data.in      (talks to your program through its stdin/stdout)
// data.in: T, then for each test case a line "n q" and a line with the hidden permutation a.
#include <bits/stdc++.h>
using namespace std;
void fail(const string &m) { cout << -1 << endl; cerr << "WRONG: " << m << endl; exit(0); }
int main(int argc, char **argv) {
    if (argc < 2) { cerr << "usage: interactor data.in" << endl; return 1; }
    ifstream in(argv[1]);
    int T; in >> T; cout << T << endl;
    long long total = 0;
    for (int tc = 1; tc <= T; tc++) {
        int n, q; in >> n >> q;
        vector<int> a(n), s(n + 1, 0);
        for (auto &x : a) in >> x;
        for (int i = 0; i + 1 < n; i++) s[a[i]] = a[i + 1];
        cout << n << " " << q << endl;
        int used = 0;
        while (true) {
            string op; if (!(cin >> op)) fail("unexpected end of output");
            vector<int> b(n), seen(n + 1, 0);
            for (auto &x : b) { if (!(cin >> x) || x < 1 || x > n || seen[x]++) fail("not a permutation"); }
            if (op == "?") {
                if (++used > q) fail("too many placements");
                string c; for (int i = 0; i + 1 < n; i++) c += s[b[i]] == b[i + 1] ? '1' : '0';
                cout << c << endl;
            } else if (op == "!") {
                if (b != a) fail("wrong permutation in test case " + to_string(tc));
                total += used; break;
            } else fail("unknown operation " + op);
        }
    }
    cerr << "OK: all " << T << " test cases solved, " << total << " placements" << endl;
}
