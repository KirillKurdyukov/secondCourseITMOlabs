//
// Created by kirilloid on 18.11.2020.
//

#include <bits/stdc++.h>

using namespace std;

#define MAXN 100001

map<pair<int, int>, int> edges;
vector<vector<int>> gr(MAXN);
int grandi[MAXN];
bool used[MAXN];
bool mark[MAXN];

void dfs(int v) {
    used[v] = true;
    for (int u : gr[v]) {
        if (!used[u]) {
            dfs(u);
            grandi[v] ^= (grandi[u] + 1);
        }
    }
}

pair<int, int> ans;

void find(int i, int s) {
    mark[i] = true;
    for (int j : gr[i])
        if (!mark[j])
            if (((grandi[j] + 1) ^ grandi[i] ^ s) == 0) {
               ans = {i, j};
               return;
            } else {
                find(j, ((grandi[j] + 1) ^ grandi[i] ^ s) - 1);
            }
}

int main() {
    int n, s;
    cin >> n >> s;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        gr[u].push_back(v);
        gr[v].push_back(u);
        edges[{min(u, v), max(u, v)}] = i + 1;
    }

    dfs(s);

    if (grandi[s]) {
        cout << 1 << endl;
        find(s, 0);
        cout << edges[{min(ans.first, ans.second), max(ans.first, ans.second)}];
    } else
        cout << 2;

}