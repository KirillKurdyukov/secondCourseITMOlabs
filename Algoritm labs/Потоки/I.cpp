//
// Created by kirilloid on 23.04.2021.
//

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main() {
    ll r1, s1, p1, r2, s2, p2;
    cin >> r1 >> s1 >> p1 >> r2 >> s2 >> p2;
    cout << max(0LL, max(r1 - r2 - p2, max(p1 - p2 - s2, s1 - s2 - r2)));
}