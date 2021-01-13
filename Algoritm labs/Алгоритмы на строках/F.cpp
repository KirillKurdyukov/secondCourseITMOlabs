//
// Created by kirilloid on 06.12.2020.
//

#include <bits/stdc++.h>

using namespace std;

#define BASE 37LL
#define MAXN 10005
#define ll unsigned long long

vector<ll> power(MAXN);
vector <vector<ll>> hashes;
string lastString;

void pre_calk() {
    power[0] = 1;
    for (int i = 1; i < MAXN; i++)
        power[i] = power[i - 1] * BASE;
}

set<ll> getSetHashes(int len, int i) {
    set<ll> currentSet;
    for (int j = 1; j < hashes[i].size() - len; j ++) {
        currentSet.insert(hashes[i][j + len] * power[hashes.size() - j] - hashes[i][j]);
    }
    return currentSet;
}

int main() {
    pre_calk();
    int n;
    cin >> n;
    hashes.resize(n);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        hashes[i].push_back(0);
        hashes[i].push_back(s[0]);
        for (int j = 1; j < s.size(); j++) {
            hashes[i].push_back((hashes[i][j - 1] + s[j]) * BASE);
        }
        lastString = s;
    }

    int l = 0;
    int r = MAXN;
    while (r - l > 1) {
        int m = (r - l) / 2;
        set<ll> s = getSetHashes(m , 0);
        for (int i = 1; i < hashes.size(); i++) {
            set<ll> cur = getSetHashes(m, i);
            set<ll> ans;
            ans = set_intersection(s.begin(), s.end(), cur.begin(), cur.end(), back_inserter(ans.begin()));

        }
    }
}