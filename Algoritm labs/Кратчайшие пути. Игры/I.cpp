//
// Created by kirilloid on 13.11.2020.
//

#include <bits/stdc++.h>

using namespace std;

enum Type {
    DRAW, FIRST, SECOND
};

void solve(int n, int m) {
    vector<vector<int>> in(n + 1);
    vector<Type> res(n + 1, DRAW);
    vector<int> d(n + 1, 0);
    vector<int> cnt(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        in[v].push_back(u);
        d[u]++;
    }
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (d[i] == 0) {
            res[i] = SECOND;
            q.push(i);
        }
    while(!q.empty()) {
        int v = q.front();
        q.pop();
        if (res[v] == SECOND) {
            for (int u : in[v]) {
                if (res[u] == DRAW) {
                    res[u] = FIRST;
                    q.push(u);
                }
            }
         } else
             for (int u : in[v]) {
                 cnt[u]++;
                 if (cnt[u] == d[u]) {
                     res[u] = SECOND;
                     q.push(u);
                 }
             }
    }
    for (int i = 1; i <= n; i++)
        switch (res[i]) {
            case DRAW:
                cout << "DRAW" << endl;
                break;
            case FIRST:
                cout << "FIRST" << endl;
                break;
            case SECOND:
                cout << "SECOND" << endl;
                break;
        }
    cout << endl;
}

int main() {
    int n, m;
    while(cin >> n >> m) {
        solve(n, m);
    }

}