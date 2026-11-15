// Manager (interactor) for "Jigsaw Puzzle" -- CMS task type Communication, 1 process, std_io.
//
// Invocation (CMS and TPS):  ./manager <fifo_user_to_manager> <fifo_manager_to_user> [extra args ignored]
//   stdin  : the test input file (hidden data)
//   stdout : the score, a real number in [0, 1]
//   stderr : first line = verdict message shown to the contestant, second line = details
//
// Test input format:
//   T
//   n q          (q = maximum number of placements allowed for this test case)
//   a_1 ... a_n  (the hidden permutation)
//   ... (T times)
//
// Protocol seen by the contestant: "T", then for every test case "n q"; contestant prints
// "? b_1 .. b_n" (answered by a binary string of length n-1) or "! a_1 .. a_n".
// On any error the manager sends "-1" and stops (score 0).
#include <bits/stdc++.h>
#include <csignal>
using namespace std;

static FILE *fin, *fout;
static long long totalPlacements = 0;

[[noreturn]] static void finish(double score, const string &verdict, const string &msg) {
    printf("%.1f\n", score);
    fprintf(stderr, "%s\n%s\n", verdict.c_str(), msg.c_str());
    fflush(stdout);
    fflush(stderr);
    exit(0);
}
[[noreturn]] static void wrong(const string &msg) {
    // tell the contestant to stop (statement: on reading -1 the program must exit immediately)
    fputs("-1\n", fout);
    fflush(fout);
    finish(0.0, "Output isn't correct", msg);
}

static bool readPerm(int n, vector<int> &b, vector<int> &seen, int stamp, string &err) {
    for (int i = 0; i < n; i++) {
        long long x;
        if (fscanf(fin, "%lld", &x) != 1) { err = "could not read integer"; return false; }
        if (x < 1 || x > n) { err = "number out of range [1, n]"; return false; }
        if (seen[x] == stamp) { err = "numbers are not a permutation"; return false; }
        seen[x] = stamp;
        b[i] = (int)x;
    }
    return true;
}

int main(int argc, char **argv) {
    signal(SIGPIPE, SIG_IGN);
    if (argc < 3) {
        fprintf(stderr, "usage: manager <user_to_manager> <manager_to_user>\n");
        return 1;
    }
    // Open the writing end first: the sandbox opens the contestant's stdin before its stdout.
    fout = fopen(argv[2], "w");
    fin = fopen(argv[1], "r");
    if (!fin || !fout) { printf("0.0\n"); fprintf(stderr, "Judge failure\nmanager could not open FIFOs\n"); return 1; }

    int T;
    if (scanf("%d", &T) != 1) { printf("0.0\n"); fprintf(stderr, "Judge failure\nbad input file\n"); return 1; }
    fprintf(fout, "%d\n", T);
    fflush(fout);

    vector<int> seen(205, 0);
    int stamp = 0;
    for (int tc = 1; tc <= T; tc++) {
        int n, q;
        if (scanf("%d %d", &n, &q) != 2) { printf("0.0\n"); fprintf(stderr, "Judge failure\nbad input file\n"); return 1; }
        vector<int> a(n), succ(n + 1, 0), b(n);
        for (int i = 0; i < n; i++)
            if (scanf("%d", &a[i]) != 1) { printf("0.0\n"); fprintf(stderr, "Judge failure\nbad input file\n"); return 1; }
        for (int i = 0; i + 1 < n; i++) succ[a[i]] = a[i + 1];

        fprintf(fout, "%d %d\n", n, q);
        fflush(fout);

        int used = 0;
        string c(max(n - 1, 0), '0');
        while (true) {
            char op;
            if (fscanf(fin, " %c", &op) != 1)
                wrong("test case " + to_string(tc) + ": unexpected end of output (expected '?' or '!')");
            string err;
            if (op == '?') {
                if (!readPerm(n, b, seen, ++stamp, err))
                    wrong("test case " + to_string(tc) + ": invalid placement: " + err);
                used++;
                totalPlacements++;
                if (used > q)
                    wrong("test case " + to_string(tc) + ": too many placements (limit " + to_string(q) + ")");
                for (int i = 0; i + 1 < n; i++) c[i] = (succ[b[i]] == b[i + 1]) ? '1' : '0';
                fputs(c.c_str(), fout);
                fputc('\n', fout);
                fflush(fout);
            } else if (op == '!') {
                if (!readPerm(n, b, seen, ++stamp, err))
                    wrong("test case " + to_string(tc) + ": invalid answer: " + err);
                if (b != a) wrong("test case " + to_string(tc) + ": wrong permutation reported");
                break;
            } else {
                wrong("test case " + to_string(tc) + string(": unknown operation '") + op + "'");
            }
        }
    }
    finish(1.0, "Output is correct",
           "all " + to_string(T) + " test cases solved, " + to_string(totalPlacements) + " placements in total");
}
