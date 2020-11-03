//
// Created by kirilloid on 10.10.2020.
//

#include <bits/stdc++.h>

using namespace std;

#define MAXN 10001

vector<vector<int >> gr(MAXN);
bool used[MAXN];
vector<int> s;
int currentColor = 1;
int color[MAXN];
int timer, in[MAXN], up[MAXN];
bool inStack[MAXN];

void dfs(int v) {
    s.push_back(v);
    inStack[v] = true;
    used[v] = true;
    up[v] = in[v] = timer++;
    for (int u : gr[v]) {
        if (!used[u]) {
            dfs(u);
            up[v] = min(up[v], up[u]);
        } else if (inStack[u]) {
            up[v] = min(up[v], in[u]);
        }
    }
    if (up[v] == in[v]) {
        int last = -1;
        while(!s.empty() && last != v) {
            last = s.back();
            inStack[s.back()] = false;
            color[s.back()] = currentColor;
            s.pop_back();
        }
        currentColor++;
    }
}
int main() {
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        gr[a].push_back(b);
    }
    for (int i = 1; i <= n; i++) {
        timer = 1;
        if (!used[i])
            dfs(i);
    }
    set<pair<int, int>> edges;
    for (int now = 1; now <= n; now++) {
        for (int v : gr[now]) {
            if (color[v] != color[now])
                edges.insert({color[now], color[v]});
        }
    }
    cout << edges.size();
}