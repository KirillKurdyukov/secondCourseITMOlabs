//
// Created by kirilloid on 10.10.2020.
//

#include <bits/stdc++.h>

using namespace std;

#define MAXN 20001
#define MAXM 200001

vector<vector<pair<int, int> > > gr(MAXN);
int maxColor = 0;
bool used[MAXN];
bool visited[MAXN];
int components[MAXM];
int timer, in[MAXN], up[MAXN];

void dfs(int v, int e = -1) {
    used[v] = true;
    in[v] = up[v] = timer++;
    for (auto w : gr[v]) {
        if (w.second == e)
            continue;
        if (used[w.first])
            up[v] = min(up[v], in[w.first]);
        else {
            dfs(w.first, w.second);
            up[v] = min(up[v], up[w.first]);
        }
    }
}

void paint(int v, int color, int e) {
    visited[v] = true;
    for (auto a : gr[v]) {
        int u = a.first;
        int ne = a.second;
        if (ne == e)
            continue;
        if (!visited[u]) {
            if (up[u] >= in[v]) {
                components[ne] = ++maxColor;
                paint(u, maxColor, ne);
            } else {
                components[ne] = color;
                paint(u, color, ne);
            }
        } else if (in[u] < in[v])
            components[ne] = color;
    }
}
int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        gr[a].push_back({b, i + 1});
        gr[b].push_back({a, i + 1});
    }
    for (int i = 1; i <= n; i++) {
        timer = 1;
        if (!used[i])
            dfs(i);
    }
    for (int i = 1; i <= n; i++) {
        if(!visited[i]) {
            paint(i, maxColor, -1);
        }
    }
    cout << maxColor << endl;
    for (int i = 1; i <= m; i++)
        cout << components[i] << " ";
    return  0;
}