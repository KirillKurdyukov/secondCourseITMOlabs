//
// Created by kirilloid on 10.10.2020.
//

#include <bits/stdc++.h>

using namespace std;

#define MAXN 20001
vector<vector<pair<int, int> > > gr(MAXN);
int color = 0;
bool used[MAXN];
int components[MAXN];
int timer, in[MAXN], up[MAXN];
vector<int> helpStack;

void dfs(int v, int e = -1) {
    used[v] = true;
    in[v] = up[v] = timer++;
    helpStack.push_back(v);
    for (auto u : gr[v]) {
        if (u.second == e)
            continue;
        if (used[u.first]) {
            up[v] = min(up[v], in[u.first]);
        } else {
            dfs(u.first, u.second);
            up[v] = min(up[v], up[u.first]);
        }
    }
    if (up[v] == in[v]) {
        color++;
        int last = -1;
        while (!helpStack.empty() && last != v) {
            components[helpStack.back()] = color;
            last = helpStack.back();
            helpStack.pop_back();
        }
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
    cout << color << endl;
    for (int i = 1; i <= n; i++)
        cout << components[i] << " ";
    return 0;
}