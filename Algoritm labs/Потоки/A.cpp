//
// Created by kirilloid on 10.04.2021.
//

#include <bits/stdc++.h>

using namespace std;

#define SIZE 101
int N, M;
using ll = long long;

struct edge {
    int u, v;
    ll c;
    ll f = 0;
    edge(int u, int v, ll c) : u(u), v(v), c(c) {}
};

vector<vector<int>> gr(SIZE);
vector<bool> visited;
#define fast ios::sync_with_stdio(false);cin.tie(0);
vector <edge> edges;

ll dfs(int u, ll flow) {
    if (u == N)
        return flow;
    if (visited[u])
        return 0;
    visited[u] = true;
    for (int v : gr[u]) {
        auto & uv = edges[v];
        if (uv.f < uv.c) {
            ll delta = dfs(uv.v, min(flow, uv.c - uv.f));
            if (delta > 0) {
                uv.f += delta;
                edges[v ^ 1].f -= delta;
                return delta;
            }
        }
    }
    return 0;
}

int main() {
    fast
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        gr[u].push_back(2 * i);
        edges.emplace_back(u, v, c);
        gr[v].push_back(2 * i + 1);
        edges.emplace_back(v, u, с);
    }

    ll ans = 0;
    while (true) {
        visited.assign(SIZE, false);
        ll delta = dfs(1, LONG_MAX);
        if (delta == 0) {
            cout << ans << endl;
            for (int i = 0; i < M; i++)
                cout << edges[2 * i].f << endl;
            return 0;
        } else
            ans += delta;
    }
}