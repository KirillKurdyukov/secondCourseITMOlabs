//
// Created by kirilloid on 06.11.2020.
//

#include <bits/stdc++.h>

using namespace std;

#define MAXN 101

int gr[MAXN][MAXN];

vector<vector <int> > d(MAXN, vector<int>(MAXN, 100000));

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            cin >> gr[i][j];
            d[i][j] = gr[i][j];
        }
    for (int i = 1; i <= n; i++)
        for (int u = 1; u <= n; u++)
            for (int v = 1; v <= n; v++)
                d[u][v] = min(d[u][v], d[u][i] + d[i][v]);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << d[i][j] << " ";
        }
        cout << endl;
    }
}