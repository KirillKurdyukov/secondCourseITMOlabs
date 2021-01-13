//
// Created by kirilloid on 06.12.2020.
//

#include <bits/stdc++.h>

using namespace std;

void Z_algo(string & s) {
    vector <int> z(s.size(), 0);
    int n = s.size();
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (r >= i)
            z[i] = min(z[i - l], r - i + 1);
        while (z[i] + i < n && s[z[i]] == s[z[i] + i])
            z[i]++;
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    string ans;
    for (int i = 0; i < n; i++) {
        if (z[i] + i == n) {
            ans = s.substr(0, i);
            if (ans == s.substr(n - i, ans.size())) {
                cout << ans.size();
                return;
            }
            break;
        }
    }

    cout << s.size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    Z_algo(s);
    return 0;
}