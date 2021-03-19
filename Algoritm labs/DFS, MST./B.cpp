//
// Created by kirilloid on 09.10.2020.
//

#include <bits/stdc++.h>

using namespace std;

#define MAXN 20001

vector<vector<int> > gr(MAXN);
map<pair<int, int>, int> E;
set<int> numBridges;
bool used[MAXN];
int timer, in[MAXN], up[MAXN];

void dfs(int v, int p = -1) {
    used[v] = true;
    in[v] = up[v] = timer++;
    for (auto w : gr[v]) {
        if (w == p)
            continue;
        if (!used[w]) {
            dfs(w, v);
            up[v] = min(up[v], up[w]);
        } else
            up[v] = min(up[v], in[w]);
    }
    if (up[v] == in[v]) {
        if (E.find({p, v}) != E.end())
            numBridges.insert(E[{p, v}]);
        if (E.find({v, p}) != E.end()) numBridges.insert(E[{v, p}]);
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        gr[a].push_back(b);
        E[{a, b}] = i + 1;
        gr[b].push_back(a);
    }
    for (int i = 1; i <= n; i++) {
        timer = 1;
        if (!used[i])
            dfs(i);
    }
    cout << numBridges.size() << endl;
    for (int now : numBridges)
        cout << now << endl;
    return 0;
}