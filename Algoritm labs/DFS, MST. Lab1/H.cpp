//
// Created by kirilloid on 11.10.2020.
//

#include <bits/stdc++.h>

using namespace std;

#define MAXN 1001
vector<vector<pair<int, int> >> gr(MAXN);
bool used[MAXN];
vector<int> s;
int currentColor = 1;
int timer, in[MAXN], up[MAXN];
bool inStack[MAXN];

void dfs(int v, int cost) {
    s.push_back(v);
    inStack[v] = true;
    used[v] = true;
    up[v] = in[v] = timer++;
    for (auto u : gr[v]) {
        if (!used[u.first] && u.second <= cost) {
            dfs(u.first, cost);
            up[v] = min(up[v], up[u.first]);
        } else if (inStack[u.first] && u.second <= cost) {
            up[v] = min(up[v], in[u.first]);
        }
    }
    if (up[v] == in[v]) {
        int last = -1;
        while (!s.empty() && last != v) {
            last = s.back();
            inStack[s.back()] = false;
            s.pop_back();
        }
        currentColor++;
    }
}

int main() {
    freopen("avia.in", "r", stdin);
    freopen("avia.out", "w", stdout);
    int n;
    cin >> n;
    int l = 0;
    int r = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int val;
            cin >> val;
            if (r < val)
                r = val;
            gr[i].push_back({j, val});
        }
    }
    while (r - l > 1) {
        int m = (l + r) / 2;
        for (int i = 1; i <= n; i++) {
            timer = 1;
            if (!used[i])
                dfs(i, m);
        }
        if (currentColor == 2)
            r = m;
        else
            l = m;
        currentColor = 1;
        for (int i = 1; i <= n; i++) {
            used[i] = false;
        }
    }
    cout << r;
}