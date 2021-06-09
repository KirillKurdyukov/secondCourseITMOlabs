//
// Created by kirilloid on 22.04.2021.
//

#include <bits/stdc++.h>

using namespace std;

int s = 1, t;

#define SIZE 1001
using ll = long long;

struct edge {
    ll u, v, c, f = 0, w;

    edge(int u, int v, int c, int w) : u(u), v(v), c(c), w(w) {}
};

vector<ll> d;
vector<edge> edges;
vector<int> from;
vector<ll> p;
vector<vector<int>> gr(SIZE);

void dijkstra() {
    d.assign(SIZE, LONG_MAX);
    d[s] = 0;
    set<pair<long long, int> > A;
    from.assign(SIZE, -1);
    A.insert({0, s});
    while (!A.empty()) {
        int u = A.begin()->second;
        A.erase(A.begin());
        for (auto id : gr[u]) {
            edge e = edges[id];
            ll wh = e.w + p[u] - p[e.v];
            if (e.f < e.c && d[u] + wh < d[e.v]) {
                A.erase({d[e.v], e.v});
                d[e.v] = d[u] + wh;
                from[e.v] = id;
                A.insert({d[e.v], e.v});
            }
        }
    }
}

ll dfs(ll id, ll flow, ll & ans) {
    if (id == -1)
        return flow;
    auto &uv = edges[id];
    ans += uv.w;
    ll delta = dfs(from[uv.u], min(flow, uv.c - uv.f), ans);
    uv.f += delta;
    edges[id ^ 1].f -= delta;
    return delta;
}

#define fast ios::sync_with_stdio(false);cin.tie(0);

int main() {
    fast
    int n;
    cin >> n;
    s = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int w;
            cin >> w;
            gr[i].push_back(static_cast<int>(edges.size()));
            edges.emplace_back(i, n + j, 1, w);
            gr[n + j].push_back(static_cast<int>(edges.size()));
            edges.emplace_back(n + j, i, 0, -w);
        }
    }
    for (int i = 1; i <= n; i++) {
        gr[s].push_back(static_cast<int>(edges.size()));
        edges.emplace_back(s, i, 1, 0);
        gr[i].push_back(static_cast<int>(edges.size()));
        edges.emplace_back(i, s, 0, 0);
    }
    t = 2 * n + 1;
    for (int i = n + 1; i <= 2 * n; i++) {
        gr[i].push_back(static_cast<int>(edges.size()));
        edges.emplace_back(i, t, 1, 0);
        gr[t].push_back(static_cast<int>(edges.size()));
        edges.emplace_back(t, i, 0, 0);
    }
    p.assign(SIZE, 0);
    dijkstra();
    p = d;
    ll ans = 0;
    while (d[t] != LONG_MAX) {
        dfs(from[t], 1, ans);
        dijkstra();
        for (int i = 0; i < SIZE; i++)
            p[i] += d[i];
    }
    cout << ans << endl;
    for (auto now : edges)
        if (now.f == 1 && now.u != s && now.v != t) {
            cout << now.u << " " << now.v - n << endl;
        }
}