//
// Created by kirilloid on 09.03.2021.
//

#include <bits/stdc++.h>

using namespace std;

vector<bool> used;
#define SIZE 5001
int edgesNum[SIZE][SIZE];
bool dfs(int v, vector<vector<int>> &gr, vector<int> &p) {
    if (used[v]) return false;
    used[v] = true;
    for (int u : gr[v]) {
        if (p[u] == -1 || dfs(p[u], gr, p)) {
            p[u] = v;
            return true;
        }
    }
    return false;
}

int main() {
    int n, m, e;
    cin >> n >> m >> e;
    vector<vector<int>> grL(SIZE);
    vector<vector<int>> grR(SIZE);
    vector<int> pForL(SIZE, -1);
    vector<int> pForR(SIZE, -1);
    vector<int> weighL(SIZE);
    for (int i = 0; i < n; i++)
        cin >> weighL[i];
    vector<int> weighR(SIZE);
    for (int i = 0; i < m; i++)
        cin >> weighR[i];
    vector<pair<int, int>> vL(SIZE);
    vector<pair<int, int>> vR(SIZE);
    for (int i = 0; i < n; i++)
        vL[i] = {weighL[i], i};
    for (int i = 0; i < m; i++)
        vR[i] = {weighR[i], i};
    sort(vL.rbegin(), vL.rend());
    sort(vR.rbegin(), vR.rend());
    for (int i = 0; i < e; i++) {
        int a, b;
        cin >> a >> b;
        grL[--a].push_back(--b);
        grR[b].push_back(a);
        edgesNum[a][b] = i;
    }
    for (int i = 0; i < n; i++) {
        used.assign(SIZE, false);
        dfs(vL[i].second, grL, pForL);
    }
    for (int i = 0; i < m; i++) {
        used.assign(SIZE, false);
        dfs(vR[i].second, grR, pForR);
    }
    vector<bool> lInPar(SIZE, false);
    vector<bool> rInPar(SIZE, false);
    for (int i = 0; i < m; i++)
        if (pForL[i] != -1)
            lInPar[pForL[i]] = true;
    for (int i = 0; i < n; i++)
        if (pForR[i] != -1)
            rInPar[pForR[i]] = true;
    vector<vector<int>> finalGr(SIZE);
    for (int i = 0; i < n; i++)
        for (int v : grL[i])
            if (lInPar[i] && rInPar[v])
                finalGr[i].push_back(v);
    vector<int> p(SIZE, -1);
    vector<pair<int, int>> newGr(SIZE);
    for (int i = 0; i < n; i++)
        if (lInPar[i])
            newGr[i] = {weighL[i], i};
    sort(newGr.rbegin(), newGr.rend());
    for (auto &i : newGr) {
        used.assign(n, false);
        dfs(i.second, finalGr, p);
    }
    int ans = 0;
    vector<int> kirill;
    for (int i = 0; i < m; i++) {
        if (p[i] != -1) {
            ans += (weighL[p[i]] + weighR[i]);
            kirill.push_back(edgesNum[p[i]][i]);
        }
    }
    cout << ans << endl;
    cout << kirill.size() << endl;
    for (int i : kirill)
        cout << i + 1 << ' ';
}