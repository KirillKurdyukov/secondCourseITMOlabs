//
// Created by kirilloid on 14.11.2020.
//

#include <bits/stdc++.h>

using namespace std;

#define MAXN 100001

vector<vector<int>> gr(MAXN);

bool used[MAXN];
vector<int> top;
vector<int> grandiVal(MAXN, 0);

void topsort(int u) {
    used[u] = true;
    for (int v : gr[u]) {
        if (!used[v])
            topsort(v);
    }
    top.push_back(u);
}

void setGrandi(int v, int n) {
    vector<bool> mex(n + 1);
    for (int i : gr[v])
        mex[grandiVal[i]] = true;
    while (mex[grandiVal[v]])
        grandiVal[v]++;
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        gr[u].push_back(v);
    }
    for (int i = 1; i <= n; i++)
        topsort(i);
    for (int u : top)
        setGrandi(u, n);
    for (int i = 1; i <= n; i++)
        cout << grandiVal[i] << endl;
}