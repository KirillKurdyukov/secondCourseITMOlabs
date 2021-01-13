//
// Created by kirilloid on 08.11.2020.
//

#include <bits/stdc++.h>

using namespace std;

struct edge {
    int u, v, val;

    edge(int u, int v, int val) : u(u), v(v), val(val) {};
};

vector<edge> e;

void solve(int n) {
    for (int i = 0; i < n; i++) {
        vector<long long> d(n, INT_MAX);
        d[i] = 0;
        vector<int> p(n, -1);
        int x;
        for (int j = 0; j < n; ++j) {
            x = -1;
            for (auto & ed : e)
                if (d[ed.u] < INT_MAX)
                    if (d[ed.v] > d[ed.u] + ed.val) {
                        d[ed.v] = max((long long) INT_MIN, d[ed.u] + ed.val);
                        p[ed.v] = ed.u;
                        x = ed.v;
                    }
        }
        if (x != -1) {
            int y = x;
            for (int j = 0; j < n; ++j)
                y = p[y];

            vector<int> path;
            for (int cur = y;; cur = p[cur]) {
                if (cur == y && path.size() > 1) break;
                path.push_back(cur);
            }
            reverse(path.begin(), path.end());

            cout << "YES\n";
            cout << path.size() << endl;
            for (int j : path)
                cout << j + 1 << ' ';
            return;
        }
    }
    cout << "NO";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int val;
            cin >> val;
            if (val != 100000)
                e.emplace_back(i, j, val);
        }
    }
    solve(n);
}