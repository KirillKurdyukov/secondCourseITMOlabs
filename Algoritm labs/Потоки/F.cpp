//
// Created by kirilloid on 20.04.2021.
//

#include <bits/stdc++.h>

using namespace std;

#define SIZE 10000

vector<vector<int>> gr(SIZE);

int s = 0, t;
vector<int> p;
vector<int> d;

struct edge {
    int u, v, c, f = 0;
    int i, j;

    edge(int u, int v, int c, int i, int j) : u(u), v(v), c(c), i(i), j(j) {}
};

vector<edge> edges;

bool bfs() {
    d.assign(SIZE, SIZE);
    queue<int> Q;
    d[s] = 0;
    Q.push(s);
    while (!Q.empty()) {
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
    for (; p[u] < gr[u].size(); p[u]++) {
        edge &uv = edges[gr[u][p[u]]];
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


int main() {
    int n;
    cin >> n;
    vector<int> points(n);
    int cnt = n + 1;
    map<pair<int, int>, int> match;
    char table[n][n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            cin >> table[i][j];
            if (i < j && table[i][j] == '.')
                match[{i, j}] = cnt++;
        }

    for (int i = 0; i < n; i++)
        cin >> points[i];
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (i == j)
                continue;
            int c = 3;
            if (table[i][j] == 'W') {
                points[i] -= 3;
                continue;
            }
            if (table[i][j] == 'w') {
                points[i] -= 2;
                points[j] -= 1;
                continue;
            }
            if (table[i][j] == 'L') {
                points[j] -= 3;
                continue;
            }
            if (table[i][j] == 'l') {
                points[i] -= 1;
                points[j] -= 2;
                continue;
            }
            gr[match[{i, j}]].push_back(static_cast<int>(edges.size()));
            edges.emplace_back(match[{i, j}], i + 1, c, i, j);
            gr[i + 1].push_back(static_cast<int>(edges.size()));
            edges.emplace_back(i + 1, match[{i, j}], 0, SIZE, SIZE);
            gr[match[{i, j}]].push_back(static_cast<int>(edges.size()));
            edges.emplace_back(match[{i, j}], j + 1, c, i, j);
            gr[j + 1].push_back(static_cast<int>(edges.size()));
            edges.emplace_back(j + 1, match[{i, j}], 0, SIZE, SIZE);
        }

    }
    for (int i = n + 1; i < cnt; i++) {
        gr[s].push_back(static_cast<int>(edges.size()));
        edges.emplace_back(s, i, 3, SIZE, SIZE);
        gr[i].push_back(static_cast<int>(edges.size()));
        edges.emplace_back(i, s, 0, SIZE, SIZE);
    }
    t = SIZE - 1;
    for (int i = 1; i <= n; i++) {
        gr[i].push_back(static_cast<int>(edges.size()));
        edges.emplace_back(i, t, points[i - 1], SIZE, SIZE);
        gr[t].push_back(static_cast<int>(edges.size()));
        edges.emplace_back(t, i, 0, SIZE, SIZE);
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
    for (auto now : edges) {
        if (now.i != SIZE && now.j != SIZE) {
            int i = now.i;
            int j = now.j;
//            cout << now.u << " " << now.v << " " << i << " " << j << " " << now.f << endl;
            if (table[i][j] == '.')
                switch (now.f) {
                    case 0:
                        table[i][j] = 'L';
                        table[j][i] = 'W';
                        break;
                    case 1:
                        table[i][j] = 'l';
                        table[j][i] = 'w';
                        break;
                    case 2:
                        table[i][j] = 'w';
                        table[j][i] = 'l';
                        break;
                    case 3:
                        table[i][j] = 'W';
                        table[j][i] = 'L';
                        break;
                }
        }
    }

    for (auto const &now : table) {
        for (auto c : now)
            cout << c;
        cout << endl;
    }
}
