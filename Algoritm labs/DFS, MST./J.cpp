//
// Created by kirilloid on 11.10.2020.
//

#include <bits/stdc++.h>

using namespace std;
#define MAXN 200001
int p[MAXN];
int r[MAXN];
set <pair<int, pair<int, int>>> E;

int get(int v) {
    if (p[v] != v) {
        p[v] = get(p[v]);
    }
    return p[v];
}

void assoc(int v, int u) {
    int x = get(v);
    int y = get(u);
    if (x == y)
        return;
    if (r[x] == r[y]) {
        r[x]++;
    }
    if (r[x] < r[y])
        p[x] = y;
    else
        p[y] = x;
}

int main() {
    int n, m;
    cin >> n >> m;
    long long weight = 0;
    for (int i = 0; i < n; i++)
        p[i + 1] = i + 1;
    for (int i = 0; i < m; i++) {
        int a, b, v;
        cin >> a >> b >> v;
        E.insert({v, {a, b}});
    }
    for (auto now : E) {
        if (get(now.second.first) != get(now.second.second)) {
            weight += now.first;
            assoc(now.second.first, now.second.second);
        }
    }
    cout << weight;
}