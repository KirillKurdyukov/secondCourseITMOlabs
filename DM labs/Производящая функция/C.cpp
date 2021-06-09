//
// Created by kirilloid on 21.03.2021.
//

#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define MD 1000000000000

int main() {
    int k;
    cin >> k;
    vector<ll> a(k), c(k);
    for (int i = 0; i < k; i++)
        cin >> a[i];
    for (int i = 0; i < k; i++)
        cin >> c[i];
    vector<ll> p(k + 1, 0), q(k + 1, 0);
    p[0] = a[0];
    q[0] = 1;
    for (int i = 1; i <= k; i++) {
        q[i] = -c[i - 1];
    }
    for (int i = 1; i < k; i++) {
        ll cur = 0;
        for (int j = 1; j <= i; j++)
            cur += a[i - j] * q[j];
        p[i] = a[i] + cur;
    }
    int d = 0;
    for (int i = k - 1; i >= 0; i--)
        if (p[i]) {
            d = i;
            cout << i << endl;
            break;
        }
    for (int i = 0; i <= d; i++) {
        cout << p[i] << " ";
    }
    cout << endl;
    cout << k << endl;
    for (int i = 0; i <= k; i++)
        cout << q[i] << " ";
}