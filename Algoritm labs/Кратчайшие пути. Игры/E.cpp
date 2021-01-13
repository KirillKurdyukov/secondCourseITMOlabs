//
// Created by kirilloid on 10.11.2020.
//

#include <bits/stdc++.h>

using namespace std;

struct edge {
    int u, v;
    long long val;

    edge(int u, int v, long long val) : u(u), v(v), val(val) {}

};

vector <edge> G;
vector<vector<int>> gr;

const long long INF = 2LL * 1e18;

bool used[2001];

void dfs(int v) {
    used[v] = true;
    for (auto u : gr[v])
        if (!used[u])
            dfs(u);
}

int main() {
    int n, m, s;
    cin >> n >> m >> s;
    gr.resize(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v;
        long long val;
        cin >> u >> v >> val;
        gr[u].push_back(v);
        G.emplace_back(u, v, val);
    }

    vector <long long> d(n + 1, INF);
    d[s] = 0;
    for (int j = 0; j < n - 1; ++j) {
        for (auto & e : G)
            if (d[e.u] < INF)
                if (d[e.v] > d[e.u] + e.val) {
                    d[e.v] = max(-INF, d[e.u] + e.val);
                }
    }

    for (auto & e : G)
        if (d[e.u] < INF)
            if (d[e.v] > d[e.u] + e.val) {
                dfs(e.v);
            }

    for (int v = 1; v <= n; v++) {
        if (used[v])
            cout << "-" << endl;
        else if (d[v] == INF)
            cout << "*" << endl;
        else
            cout << d[v] << endl;
    }
}