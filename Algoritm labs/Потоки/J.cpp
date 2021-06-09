//
// Created by kirilloid on 26.04.2021.
//

#include <bits/stdc++.h>

using namespace std;

#define SIZE 600
#define size static_cast<int>(edges.size())
using ll = long long;
const ll INF = 1e18 + 100;
vector<vector<int>> gr(SIZE);
vector<ll> d;
vector<ll> p;
vector<ll> from;
int s = 0, t;

struct edge {
    ll u, v, c, w, f = 0;

    edge(ll u, ll v, ll c, ll w) : u(u), v(v), c(c), w(w) {}
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

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<ll>> D(n + 1, vector<ll>(n + 1, INF));
    for (int i = 0; i <= n; i++) {
        D[i][i] = 0;
    }
    for (int i = 1; i <= n; i++)
        cin >> D[i][i];
    for (int i = 0; i < m; i++) {
        ll u, v, c;
        cin >> u >> v >> c;
        D[u][v] = c;
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
            }
        }
    }

    for (int u = 1; u <= n; u++)
        for (int v = n + 1; v <= 2 * n; v++) {
            ll c = D[u][v - n];
            gr[u].push_back(size);
            edges.emplace_back(u, v, 1, c);
            gr[v].emplace_back(size);
            edges.emplace_back(v, u, 0, -c);
    }
    t = 2 * n + 1;
    for (int i = 1; i <= n; i++) {
        gr[0].push_back(size);
        edges.emplace_back(0, i, 1, 0);
        gr[i].push_back(size);
        edges.emplace_back(i, 0, 0, 0);
    }

    for (int i = n + 1; i <= 2 * n; i++) {
        gr[i].push_back(size);
        edges.emplace_back(i, t, 1, 0);
        gr[t].push_back(size);
        edges.emplace_back(t, i, 0, 0);
    }
//    for (auto now : edges)
//        cout << now.u << ' ' << now.v << " " << now.c << " " << now.w << endl;
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
    cout << ans;
}