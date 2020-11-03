//
// Created by kirilloid on 20.10.2020.
//

#include <bits/stdc++.h>

using namespace std;

#define MAXN 1001
#define ll long long
#define Graph vector<vector<edge>>
#define Edges vector<edge>

struct edge {
    int from;
    int to;
    int val;

    edge(int f, int t, int v) : from(f), to(t), val(v) {}
};

bool used[MAXN];
vector<int> s;
int currentColor = 1;
int color[MAXN];
int timer, in[MAXN], up[MAXN];

int dfs(int v, Graph &graph) {
    used[v] = true;
    int cnt = 1;
    for (auto u : graph[v]) {
        if (!used[u.to])
            cnt += dfs(u.to, graph);
    }
    return cnt;
}

Graph newGraph(int n, Edges &edges) {
    Graph graph(n + 1);
    for (auto e : edges) {
        graph[e.from].push_back({e.from, e.to, e.val});
    }
    return graph;
}

void dfsTarjan(int v, Graph &gr) {
    s.push_back(v);
    used[v] = true;
    up[v] = in[v] = timer++;
    for (edge u : gr[v]) {
        if (!used[u.to]) {
            dfsTarjan(u.to, gr);
            up[v] = min(up[v], up[u.to]);
        } else if (!color[u.to]) {
            up[v] = min(up[v], in[u.to]);
        }
    }
    if (up[v] == in[v]) {
        int last = -1;
        while (!s.empty() && last != v) {
            last = s.back();
            color[s.back()] = currentColor;
            s.pop_back();
        }
        currentColor++;
    }
}

void condensation(int n, Graph &graph) {
    for (int i = 1; i <= n; i++) {
        used[i] = false;
        color[i] = 0;
    }
    currentColor = 1;
    for (int i = 1; i <= n; i++) {
        timer = 1;
        if (!used[i])
            dfsTarjan(i, graph);
    }
}

ll findMST(Edges &edges, int n, int root = 1) {
    ll res = 0;
    vector<int> minEdge(n + 1, INT_MAX);
    for (auto e : edges) {
        minEdge[e.to] = min(e.val, minEdge[e.to]);
    }
    for (int v = 1; v <= n; v++) {
        if (v != root)
            res += minEdge[v];
    }
    vector<edge> zeroEdges;
    for (auto e : edges)
        if (e.val == minEdge[e.to]) {
            zeroEdges.push_back(e);
        }
    Graph zeroGraph = newGraph(n, zeroEdges);
    for (int i = 1; i <= n; i++)
        used[i] = false;
    if (dfs(root, zeroGraph) == n)
        return res;
    condensation(n, zeroGraph);
    vector<edge> newEdges;
    for (auto e : edges)
        if (color[e.to] != color[e.from])
            newEdges.emplace_back(color[e.from], color[e.to], e.val - minEdge[e.to]);
    return  res + findMST(newEdges, currentColor - 1, color[root]);
}

int main() {
    int n, m;
    cin >> n >> m;
    Graph gr(n + 1);
    vector<edge> edges;
    for (int i = 0; i < m; i++) {
        int a, b;
        int c;
        cin >> a >> b >> c;
        gr[a].push_back({a, b, c});
        edges.emplace_back(a, b, c);
    }
    if (dfs(1, gr) != n) {
        cout << "NO";
        return 0;
    }
    cout << "YES\n";
    cout << findMST(edges, n);
    return 0;
}

