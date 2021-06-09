//
// Created by kirilloid on 19.04.2021.
//

#include <bits/stdc++.h>

using namespace std;

#define INF 10000

struct edge {
    int u, v, c, f = 0;
    int i, j;
    edge(int u, int v, int c, int i, int j) : u(u), v(v), c(c), i(i), j(j) {}
};
int s, t;
vector<edge> edges;
vector<int> d;
vector<vector<int>> gr(INF);
vector<int> p;
vector<bool> visited;

bool bfs() {
    d.assign(INF, INF);
    queue<int> Q;
    d[s] = 0;
    Q.push(s);
    while(!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (int id : gr[u]) {
            edge uv = edges[id];
            if (uv.f < uv.c && d[uv.v] == INF) {
                d[uv.v] = d[u] + 1;
                Q.push(uv.v);
            }
        }
    }
    return d[t] != INF;
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

void bfs1() {
    visited[s] = true;
    queue<int> Q;
    Q.push(s);
    while(!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (int id : gr[u]) {
            edge uv = edges[id];
            if (uv.f < uv.c && !visited[uv.v]) {
                visited[uv.v] = true;
                Q.push(uv.v);
            }
        }
    }
}

int main() {
    int m, n;
    cin >> m >> n;
    map<pair<int, int>, int> in;
    map<pair<int, int>, int> out;
    vector<vector<char>> table(m, vector<char>(n));
    vector<pair<int, int>> const go = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            cin >> table[i][j];
    int count = 0;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            in[{i, j}] = count++;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            out[{i, j}] = count++;

    auto correct = [m, n](int x, int y) {
            return 0 <= x && x < m && 0 <= y && y < n;
    };
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int c = INF;
            if (table[i][j] == '.') {
                c = 1;
            }
            if (table[i][j] == '#') {
                c = 0;
            }
            if (table[i][j] == '-') {
                /* ignored */
            }
            if (table[i][j] == 'A')
                s = out[{i, j}];
            if (table[i][j] == 'B')
                t = in[{i, j}];
            gr[in[{i, j}]].push_back(static_cast<int>(edges.size()));
            edges.emplace_back(in[{i, j}], out[{i, j}], c, i, j);
            gr[out[{i, j}]].push_back(static_cast<int>(edges.size()));
            edges.emplace_back(out[{i, j}], in[{i, j}], 0, i, j);
            for(auto[t1, t2] : go) {
                int x = i + t1;
                int y = j + t2;
                if (correct(x, y)) {
                    gr[out[{i, j}]].push_back(static_cast<int>(edges.size()));
                    edges.emplace_back(out[{i, j}], in[{x, y}], INF, i, j);
                    gr[in[{x, y}]].push_back(static_cast<int>(edges.size()));
                    edges.emplace_back(in[{x, y}], out[{i, j}], 0, i, j);
                }
            }
        }
    }
    visited.assign(INF, false);
    int maxFlow = 0;
    while (bfs()) {
        p.assign(INF, 0);
        int fl = dfs(s, INF);
        while (fl) {
            maxFlow += fl;
            fl = dfs(s, INF);
        }
    }
    bfs1();
    if (maxFlow >= INF) {
        cout << -1;
        return 0;
    }
    cout << maxFlow << endl;
    for (auto now : edges) {
        if (now.c == 1 && now.f == 1 && visited[now.u] && !visited[now.v])
            table[now.i][now.j] = '+';
    }
    for (const auto& row : table) {
        for (auto col : row)
            cout << col;
        cout << endl;
    }
}