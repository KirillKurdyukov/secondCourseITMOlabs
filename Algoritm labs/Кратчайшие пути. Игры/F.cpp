//
// Created by kirilloid on 11.11.2020.
//

#include <bits/stdc++.h>

using namespace std;

#define MAXN 100001
const long long INF = 1e16;
vector < vector <pair <int, int> > > gr(MAXN);

vector < vector <long long> > d(3, vector<long long> (MAXN, INF));
void dijkstra(int i, int j) {

    d[i][j] = 0;
    set <pair<long long, int> > A;

    A.insert({0, j});

    while (!A.empty()) {
        int u = A.begin()->second;
        A.erase(A.begin());
        for (auto v : gr[u]) {
            if (d[i][u] + v.second < d[i][v.first]) {
                A.erase({d[i][v.first], v.first});
                d[i][v.first] = d[i][u] + v.second;
                A.insert({d[i][v.first], v.first});
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, val;
        cin >> u >> v >> val;
        gr[u].push_back({v, val});
        gr[v].push_back({u, val});
    }
    int a[3];
    cin >> a[0] >> a[1] >> a[2];
    for (int j = 0; j < 3; j++)
        dijkstra(j, a[j]);

    long long ans = min(d[0][a[1]] + d[1][a[2]],
                        min(d[1][a[2]] + d[2][a[0]],
                            d[2][a[0]] + d[0][a[1]]));
    ans = min(ans, min(d[2][a[1]] + d[1][a[0]],
                       min(d[1][a[0]] + d[0][a[2]],
                           d[0][a[2]] + d[1][a[0]])));
    if (ans > INF)
        cout << "-1";
    else
        cout << ans;

}