//
// Created by kirilloid on 26.02.2021.
//

#include <bits/stdc++.h>

using namespace std;

#define SIZE 251
vector<bool> used( SIZE);
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

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int t;
        while (true) {
            cin >> t;
            if (t == 0)
                break;
            gr[i].push_back(t);
        }
    }

    for (int i = 1; i <= n; i++) {
        used.assign(SIZE, false);
        dfs(i);
    }

    int size = 0;
    vector<pair<int, int>> ans;
    for (int i = 1; i <= m; i++) {
        if (p[i] != -1) {
            size++;
            ans.emplace_back(p[i], i);
        }
    }

    cout << size << endl;
    for (auto now : ans) {
        cout << now.first << " " << now.second << '\n';
    }
}