//
// Created by kirilloid on 17.04.2021.
//

#include <bits/stdc++.h>

using namespace std;

#define SIZE 100001
int N, M;
int s, t;
struct edge {
    int u, v;
    int c;
    int f = 0;
    edge(int u, int v, int c) : u(u), v(v), c(c) {}
};

vector<vector<int>> gr(SIZE);
#define fast ios::sync_with_stdio(false);cin.tie(0);
vector <edge> edges;
vector<int> d;
vector<int> p;

bool bfs() {
    d.assign(SIZE, SIZE);
    d[s] = 0;
    queue<int> Q;
    Q.push(s);
    while(!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (int id : gr[u]) {
            edge uv = edges[id];
            if (uv.f < uv.c && d[uv.v] == SIZE) {
                d[uv.v] = d[u] + 1;
                Q.push(uv.v);
            }
        }
    }
    return d[t] != SIZE;
}

int dfs(int u, int minC) {
    if (u == t || minC == 0)
        return minC;
    for (;  p[u] < gr[u].size(); p[u]++) {
        edge & uv = edges[gr[u][p[u]]];
        if (d[uv.v] == d[u] + 1) {
            int delta = dfs(uv.v, min(minC, uv.c - uv.f));
            if (delta) {
                uv.f += delta;
                edges[gr[u][p[u]] ^ 1].f -= delta;
                return delta;
            }
        }
    }
    return 0;
}

void dfs1(int u, vector<int> &cur) {
    if (u == t) {
        cur.push_back(u);
        return;
    }
    for (int v : gr[u]) {
        if (edges[v].f == 1) {
            edges[v].f = 0;
            cur.push_back(u);
            dfs1(edges[v].v, cur);
            return;
        }
        else continue;
    }
}

int main() {
    fast
    cin >> N >> M >> s >> t;
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        gr[u].push_back(2 * i);
        edges.emplace_back(u, v, 1);
        gr[v].push_back(2 * i + 1);
        edges.emplace_back(v, u, 0);
    }

    int maxFlow = 0;
    while (bfs()) {
        p.assign(SIZE, 0);
        int fl = dfs(s, SIZE);
        while (fl) {
            maxFlow += fl;
            fl = dfs(s, SIZE);
        }
    }

    if (maxFlow >= 2)
        cout << "YES\n";
    else {
        cout << "NO\n";
        return 0;
    }

    vector<vector<int>> ans(2);
    dfs1(s, ans[0]);
    dfs1(s, ans[1]);

    for (const auto& now : ans) {
        for (int c : now)
            cout << c << " ";
        cout << endl;
    }
}