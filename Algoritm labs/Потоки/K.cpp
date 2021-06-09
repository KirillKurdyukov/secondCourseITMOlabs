//
// Created by kirilloid on 24.04.2021.
//

#include <bits/stdc++.h>

using namespace std;

#define SIZE 202
using ll = long long;
vector<vector<int>> gr(SIZE);
vector<ll> d;
vector<ll> p;
vector<ll> from;
int s = 1, t;

struct edge {
    ll u, v, c, w, f = 0;
    int path_num;
    edge(ll u, ll v, ll c, ll w, int path_num) : u(u), v(v), c(c), w(w), path_num(path_num){}
};

vector<edge> edges;

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

ll dfs(ll id, ll flow, ll &ans) {
    if (id == -1)
        return flow;
    auto &uv = edges[id];
    ans += uv.w;
    ll delta = dfs(from[uv.u], min(flow, uv.c - uv.f), ans);
    uv.f += delta;
    edges[id ^ 1].f -= delta;
    return delta;
}

void dfs1(ll u, vector<ll> &cur) {
    if (u == t) {
        return;
    }
    for (int v : gr[u]) {
        if (edges[v].f == 1) {
            edges[v].f = 0;
            cur.push_back(edges[v].path_num);
            dfs1(edges[v].v, cur);
            return;
        } else continue;
    }
}


int main() {
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        gr[u].push_back(static_cast<int>(edges.size()));
        edges.emplace_back(u, v, 1, w, i + 1);
        gr[v].push_back(static_cast<int>(edges.size()));
        edges.emplace_back(v, u, 0, -w, i + 1);
        gr[u].push_back(static_cast<int>(edges.size()));
        edges.emplace_back(u, v, 0, -w, i + 1);
        gr[v].push_back(static_cast<int>(edges.size()));
        edges.emplace_back(v, u, 1, w, i + 1);
    }
    t = n;
    p.assign(SIZE, 0);
    dijkstra();
    p = d;
    ll ans = 0;
    for (int i = 0; i < k; i++)
        if (d[t] != LONG_MAX) {
            dfs(from[t], 1, ans);
            dijkstra();
            for (int i = 0; i < SIZE; i++)
                p[i] += d[i];
        } else {
            cout << -1 << endl;
            return 0;
        }
    cout << setprecision(5) << fixed << static_cast<double>(ans) / k << endl;
    vector<vector<ll>> ans_path(k);
    for (int i = 0; i < k; i++)
        dfs1(s, ans_path[i]);
    for (const auto& now : ans_path) {
        cout << now.size() << " ";
        for (auto c : now)
            cout << c << " ";
        cout << endl;
    }
}