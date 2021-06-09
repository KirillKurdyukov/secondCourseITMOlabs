//
// Created by kirilloid on 19.04.2021.
//


#include <bits/stdc++.h>

using namespace std;

#define SIZE 100001

int N, M;
int s, t;
struct edge {
    int u, v;
    long long c;
    long long f = 0;
    edge(int u, int v, long long c) : u(u), v(v), c(c) {}
};

vector<vector<int>> gr(SIZE);
#define fast ios::sync_with_stdio(false);cin.tie(0);
vector <edge> edges;
vector<int> d;
vector<int> p;
vector<bool> visited;

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

long long dfs(int u, long long minC) {
    if (u == t || minC == 0)
        return minC;
    for (;  p[u] < gr[u].size(); p[u]++) {
        edge & uv = edges[gr[u][p[u]]];
        if (d[uv.v] == d[u] + 1) {
            long long delta = dfs(uv.v, min(minC, uv.c - uv.f));
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
bool operator<(edge const & e1, edge const & e2)  {
    return tie(e1.u, e1.v) < tie(e2.u, e2.v);
}

int main() {
    fast
    cin >> N >> M;
    s = 1;
    t = N;
    map<edge, int> map1;
    for (int i = 0; i < M; i++) {
        int u, v;
        long long c;
        cin >> u >> v >> c;
        gr[u].push_back(2 * i);
        edges.emplace_back(u, v, c);
        map1[edges.back()] = i;
        gr[v].push_back(2 * i + 1);
        edges.emplace_back(v, u, c);
        map1[edges.back()] = i;
    }

    long long maxFlow = 0;
    while (bfs()) {
        p.assign(SIZE, 0);
        long long fl = dfs(s, SIZE);
        while (fl) {
            maxFlow += fl;
            fl = dfs(s, SIZE);
        }
    }

    visited.assign(SIZE, false);
    bfs1();
    vector<int> ans;
    for (auto now : edges) {
        if (visited[now.u] && !visited[now.v])
            ans.push_back(map1[now]);
    }

    cout << ans.size() << " " << maxFlow << endl;
    for (auto  now : ans)
        cout << now + 1 << " ";
}