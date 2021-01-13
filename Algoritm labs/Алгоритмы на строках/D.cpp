//
// Created by kirilloid on 06.12.2020.
//

#include <bits/stdc++.h>

using namespace std;

vector<int> Z_algo(string & s) {
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
    return z;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string p, t;
    cin >> p >> t;
    string s = p + '$' + t;
    vector<int> z = Z_algo(s);
    vector<int> ans;
    for (int i = p.size(); i < z.size(); i++) {
        if (z[i] == p.size()) {
            ans.push_back(i - p.size());
        }
    }
    cout << ans.size() << endl;
    for (auto now : ans)
        cout << now << " ";
}