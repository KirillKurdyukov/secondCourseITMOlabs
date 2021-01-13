//
// Created by kirilloid on 01.12.2020.
//

#include <bits/stdc++.h>

using namespace std;

#define MAXN 100001
vector<vector<int>> gr(MAXN);
bool used[MAXN];

int main() {
    int n;
    cin >> n;
    vector<int> d(n + 1, 0);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        gr[v].push_back(u);
        gr[u].push_back(v);
        d[v]++;
        d[u]++;
    }

    set<int> sheets;

    for (int i = 1; i <= n; i++) {
        if (d[i] == 1)
            sheets.insert(i);
    }

    vector<int> prufer_code;
    while (!sheets.empty()) {
        int vertex = *sheets.begin();
        used[vertex] = true;
        int to;
        for (int i : gr[vertex])
            if (!used[i]) {
                to = i;
                break;
            }
        d[to]--;
        prufer_code.push_back(to);
        sheets.erase(vertex);
        if (d[to] == 1)
            sheets.insert(to);
    }

    for (int i = 0; i < prufer_code.size() - 2; i++)
        cout << prufer_code[i] << " ";

}
