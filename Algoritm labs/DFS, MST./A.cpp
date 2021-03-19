//
// Created by kirilloid on 09.10.2020.
//

#include <bits/stdc++.h>

using namespace std;

#define MAXN 100001

vector<int> top;
bool used[MAXN];
int mark[MAXN];
vector<vector<int> > gr(MAXN);

void topsort(int v) {
    used[v] = true;
    for (int i : gr[v]) {
        if (!used[i])
            topsort(i);
    }
    top.push_back(v);
}

bool dfs(int v) {
    mark[v] = 1;
    for (int i : gr[v]) {
        if (!mark[i] && dfs(i))
            return true;
        if (mark[i] == 1)
            return true;
    }
    mark[v] = 2;
    return false;
}
int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        gr[a].push_back(b);
    }
    for (int i = 1; i <= n; i++) {
        if (!used[i])
            topsort(i);
        if (dfs(i)) {
            cout << - 1;
            return 0;
        }

    }
    reverse(top.begin(), top.end());
    for (auto now : top) {
        cout << now << " ";
    }
    return 0;
}