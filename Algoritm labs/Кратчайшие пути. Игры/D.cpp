//
// Created by kirilloid on 09.11.2020.
//

#include <bits/stdc++.h>

using namespace std;

struct edge {
    int u, v, val;

    edge(int u, int v, int val) : u(u), v(v), val(val) {};
};

vector<edge> edges;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m, k, s;
    cin >> n >> m >> k >> s;
    vector<vector<int> > d(n + 1, vector<int>(k + 1, INT_MAX));
    for (int i = 0; i < m; i++) {
        int u, v, val;
        cin >> u >> v >> val;
        edges.emplace_back(u, v, val);
    }
    d[s][0] = 0;
    for (int i = 1; i <= k; ++i)
        for (auto &e : edges)
            if (d[e.u][i - 1] != INT_MAX)
                d[e.v][i] = min(d[e.u][i - 1] + e.val, d[e.v][i]);
    for (int i = 1; i <= n; i++) {
        if (d[i][k] == INT_MAX)
            cout << -1 << endl;
        else cout << d[i][k] << endl;
    }
}