//
// Created by kirilloid on 22.12.2020.
//

#include <bits/stdc++.h>

using namespace std;


int main() {
    freopen("cycles.in", "r", stdin);
    freopen("cycles.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    vector <bool> used((1 << n), false);
    vector<int> weight(n);
    for (int i = 0; i < n; i++)
        cin >> weight[i];
    for (int i = 0; i < m; i++) {
        int size;
        cin >> size;
        unsigned int cycle = 0;
        for (int j  = 0; j < size; j++) {
            int t;
            cin >> t;
            cycle += (1 << (t - 1));
        }
        used[cycle] = true;
        unsigned int negative = (~cycle) % (1 << n);
        for (unsigned s = negative; s; s = (s - 1) & negative) {
            used[s + cycle] = true;
        }
    }

    int ans = 0;
    for (int i = 0; i < (1 << n); i++) {
        int sum = 0;
        if (!used[i])
            for (int j = 0; j < n; j++) {
                if ((i >> j) % 2)
                    sum += weight[j];
            }
        ans = max(ans, sum);
    }

    cout << ans;
}