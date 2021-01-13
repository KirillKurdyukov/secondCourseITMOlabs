//
// Created by kirilloid on 01.12.2020.
//

#include <bits/stdc++.h>

using namespace std;

#define MAXN 10000
vector<vector<int>> gr(MAXN);
int dist[MAXN];
int paint[MAXN];
bool used[MAXN];
vector<bitset<MAXN>> useColor(MAXN);

int first_color(int v) {
    return useColor[v]._Find_first();
}

void dfs(int v) {
    paint[v] = first_color(v);
    used[v] = true;

    for (int u : gr[v]) {
        useColor[u][paint[v]] = false;
    }

    for (int u : gr[v]) {
        if (!used[u])
            dfs(u);
    }

}

int main() {
    for (int i = 0; i < MAXN; i++)
        useColor[i].flip();
    int n, m;
    cin >> n >> m;
    int max_dist = 0;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        gr[u].push_back(v);
        gr[v].push_back(u);
        dist[u]++;
        dist[v]++;
        max_dist = max(max_dist, max(dist[u], dist[v]));
    }
    cout << max_dist + (max_dist + 1) % 2 << endl;
    dfs(1);
    for (int i = 1; i <= n; i++)
        cout << paint[i] + 1 << endl;
}