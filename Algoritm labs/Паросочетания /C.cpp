//
// Created by kirilloid on 26.02.2021.
//

#include <bits/stdc++.h>

using namespace std;

#define SIZE 151
vector<bool> visited;
vector<bool> used;
vector<vector<int>> gr(SIZE);
vector<int> p(SIZE, -1);

bool dfs(int v) {
    if (used[v]) return false;
    used[v] = true;
    for (int u : gr[v]) {
        if (p[u] == -1 || dfs(p[u])) {
            p[u] = v;
            return true;
        }
    }
    return false;
}

void dfs1(int v) {
    if (used[v]) return;
    used[v] = true;
    for (int u : gr[v]) {
        visited[u] = true;
        if (p[u] != -1) {
            dfs1(p[u]);
        }
    }
}

void solve() {
    int m, n;
    cin >> m >> n;
    for (int i = 1; i <= m; i++) {
        vector<bool> mark(n + 1, false);
        int t;
        while(true) {
            cin >> t;
            if (t == 0)
                break;
            mark[t] = true;
        }
        for (int j = 1; j <= n; j++)
            if (!mark[j])
                gr[i].push_back(j);
    }

    for (int i = 1; i <= m; i++) {
        used.assign(SIZE, false);
        dfs(i);
    }

    used.assign(SIZE, false);
    visited.assign(SIZE, false);
    vector <bool> open(SIZE, true);
    for (int i = 1; i <= n; i++) {
        if (p[i] != -1)
            open[p[i]] = false;
    }
    for (int i = 1; i <= m; i++)
        if (open[i] && !used[i])
            dfs1(i);

    vector<int> men;
    vector<int> women;

    for (int i = 1; i <= m; i++) {
        if (used[i])
            men.push_back(i);
    }
    for (int i = 1; i <= n; i++)
        if (!visited[i])
            women.push_back(i);
    cout << men.size() + women.size() << endl;
    cout << men.size() << " " << women.size() << endl;
    for (auto now : men)
        cout << now << " ";
    cout << endl;
    for (auto now : women)
        cout << now << ' ';
    cout << endl << endl;
    p.assign(SIZE, -1);
    for (auto & now : gr)
        now.clear();
    used.assign(SIZE, false);
    visited.assign(SIZE, false);
}

int main() {
    int k;
    cin >> k;
    while (k--) {
        solve();
    }
}