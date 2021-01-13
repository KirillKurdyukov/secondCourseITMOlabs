//
// Created by kirilloid on 06.11.2020.
//

#include <bits/stdc++.h>

using namespace std;

#define MAXN 30001

vector < vector <pair <int, int> > > gr(MAXN);

vector<long long> d(MAXN, (long long) 2 * INT_MAX);

int main() {
    int n, m;
    cin >> n >> m;
    d[1] = 0;
    for (int i = 0; i < m; i++) {
        int u, v, val;
        cin >> u >> v >> val;
        gr[u].push_back({v, val});
        gr[v].push_back({u, val});
    }

    set <pair<long long, int> > A;

    A.insert({0, 1});

    while (!A.empty()) {
       int u = A.begin()->second;
       A.erase(A.begin());
       for (auto v : gr[u]) {
           if (d[u] + v.second < d[v.first]) {
               A.erase({d[v.first], v.first});
               d[v.first] = d[u] + v.second;
               A.insert({d[v.first], v.first});
           }
       }
    }

    for (int i = 1; i <= n; i++)
        cout << d[i] << " ";
}