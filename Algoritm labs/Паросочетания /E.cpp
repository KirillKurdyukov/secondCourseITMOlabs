//
// Created by kirilloid on 26.02.2021.
//

#include <bits/stdc++.h>

using namespace std;

vector<bool> used;
vector<vector<int>> gr;
vector<int> p;

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
    int n, m, a, b;
    cin >> n >> m >> a >> b;
    if (a < 2 * b) {
        char table[n + 1][m + 1];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> table[i][j];
            }
        }
        map<pair<int, int>, int> assoc;
        int L = 1, R = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (table[i][j] == '*') {
                    if ((i + j) % 2)
                        assoc[{i, j}] = R++;
                    else
                        assoc[{i, j}] = L++;
                }
            }
        }
        gr.resize(L);
        p.assign(R, -1);
        used.assign(L, false);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m - 1; j++) {
                if (table[i][j] == table[i][j + 1] && table[i][j] == '*') {
                    if ((i + j) % 2 == 0)
                        gr[assoc[{i, j}]].push_back(assoc[{i, j + 1}]);
                    else
                        gr[assoc[{i, j + 1}]].push_back(assoc[{i, j}]);
                }
            }
        }
        for (int j = 0; j < m; j++) {
            for(int i = 0; i < n - 1; i++) {
                if (table[i][j] == table[i + 1][j] && table[i][j] == '*') {
                    if ((i + j) % 2 == 0)
                        gr[assoc[{i, j}]].push_back(assoc[{i + 1, j}]);
                    else
                        gr[assoc[{i + 1, j}]].push_back(assoc[{i, j}]);
                }
            }
        }
        for (int i = 1; i < L; i++) {
            used.assign(L, false);
            dfs(i);
        }
        int ans = 0;
        used.assign(L, false);
        for (int i = 1; i < R; i++) {
            if (p[i] != -1) {
                ans += a;
                used[p[i]] = true;
            }
            if (p[i] == -1) {
                ans += b;
            }
        }
        for (int i = 1; i < L; i++)
            if (!used[i])
                ans += b;
        cout << ans;
    } else {
        int count = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                char t;
                cin >> t;
                if (t == '*')
                    count++;
            }
        }
        cout << count * b;
    }
}