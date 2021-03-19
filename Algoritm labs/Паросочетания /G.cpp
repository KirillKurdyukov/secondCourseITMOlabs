//
// Created by kirilloid on 05.03.2021.
//

#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> gr;
vector<bool> used;
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
    int m, k, n, t, q;
    cin >> m >> k >> n >> t;
    set<pair<int, int>> badPair;
    for (int i = 0; i < t; i++) {
        int a, b;
        cin >> a >> b;
        badPair.insert({a, b});
    }
    cin >> q;
    set<int> noSingle;
    for (int i = 0; i < q; i++) {
        int no;
        cin >> no;
        noSingle.insert(no);
    }

    gr.assign(m + 1 + k - n, vector<int>());
    p.assign(k + 1 + m - n, -1);

    for (int i = 1; i <= m; i++) {
        for (int j = m + 1; j <= m + k; j++) {
            if (badPair.find({i, j}) == badPair.end())
                gr[i].push_back(j - m);
        }
        if (noSingle.find(i) == noSingle.end()) {
            for (int a = m + k + 1; a <= 2 * m  + k - n; a++)
                gr[i].push_back(a - m);
        }
    }

    for (int i = m + 1; i <= m + k; i++) {
        if (noSingle.find(i) == noSingle.end()) {
            for (int j = m + 1; j <= m + k - n; j++)
                gr[j].push_back(i - m);
        }
    }
    for (int i = 1; i <= m + k - n; i++) {
        used.assign(m + k - n + 1, false);
        dfs(i);
    }
    vector<pair<int, int>> ans;
    for (int i = 1; i <= k + m - n; i++)
        if (p[i] == -1) {
            cout << "NO";
            return 0;
        } else {
            if (p[i] <= m && i <= k)
                ans.emplace_back(p[i], i + m);
        }
    cout << "YES" << endl;
    for (auto now : ans)
        cout << now.first << ' ' << now.second << endl;
}
