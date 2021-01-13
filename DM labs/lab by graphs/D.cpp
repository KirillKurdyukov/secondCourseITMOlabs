//
// Created by kirilloid on 01.12.2020.
//

#include <bits/stdc++.h>

using namespace std;

#define MAXN 1001

bool gr[MAXN][MAXN];

bool check_gam(vector<int> &d, int start) {
    for (int i = start + 1; i < d.size(); i++)
        if (!gr[d[i - 1]][d[i]])
            return false;
    return true;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 1; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < s.size(); j++) {
            if (s[j] == '0')
                gr[j + 1][i + 1] = true;
            else
                gr[i + 1][j + 1] = true;
        }
    }

    vector<int> d;
    for (int i = 1; i <= n; i++)
        d.push_back(i);
    int start = 0;
    auto g = mt19937(std::random_device()());
    while (true) {
        for (int i = 0; i <= n * (n - 1); i++) {
            if (!gr[d[start]][d[start + 1]]) {
                int j = 2 + start;
                while (j < d.size() - 1 && !gr[d[start]][d[j]])
                    j++;
                swap(d[start + 1], d[j]);
            }
            d.push_back(d[start]);
            start++;
        }
        if (check_gam(d, start))
            break;
        else {
            d.resize(n);
            for (int i = 1; i <= n; i++)
                d[i - 1] = i;
            start = 0;
            shuffle(d.begin(), d.end(), g);
        }
    }
    for (int i = start; i < d.size(); i++) {
        cout << d[i] << " ";
    }

}