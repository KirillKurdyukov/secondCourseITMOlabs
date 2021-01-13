//
// Created by kirilloid on 22.12.2020.
//

#include <bits/stdc++.h>

using namespace std;

#define SIZE 1001

vector<vector<int>> gr(2 * SIZE);
bool used[2 * SIZE];
vector<int> mt(2 * SIZE, 0);

bool try_kuhn(int v) {
    if (used[v])
        return false;
    used[v] = true;
    for (int to : gr[v]) {
        if (!mt[to] || try_kuhn(mt[to])) {
            mt[to] = v;
            return true;
        }
    }
    return false;
}

int main() {
    freopen("matching.in", "r", stdin);
    freopen("matching.out", "w", stdout);
    int n;
    cin >> n;
    vector<pair<int, int>> vertex;
    for (int i = 0; i < n; ++i) {
        int w;
        cin >> w;
        vertex.emplace_back(w, i + 1);
    }
    sort(vertex.begin(), vertex.end());
    reverse(vertex.begin(), vertex.end());
    for (int i = 1; i <= n; i++) {
        int size;
        cin >> size;
        for (int j = 0; j < size; j++) {
            int v;
            cin >> v;
            gr[i].push_back(v + n);
            gr[v + n].push_back(i);
        }
    }

    for (auto now : vertex) {
        for (bool &i : used)
            i = false;
        try_kuhn(now.second);
    }

    vector<int> ans(SIZE);
    for (int i = 1; i <= n; i++)
        ans[mt[i + n]] = i;
    for (int i = 1; i <= n; i++)
        cout << ans[i] << " ";
}