//
// Created by kirilloid on 16.05.2021.
//

#include <bits/stdc++.h>

using namespace std;

using ll = long long;
ll gcd(ll a, ll b, ll &x, ll &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    ll x1, y1;
    ll d = gcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

void find_any_solution(ll a, ll b, ll c, ll &x0, ll &y0, ll &g) {
    g = gcd(abs(a), abs(b), x0, y0);
    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 *= -1;
    if (b < 0) y0 *= -1;
}

int main() {
    ll a, b, n, m;
    cin >> a >> b >> n >> m;
    ll x, y;
    ll g;
    find_any_solution(n, -m, b - a, x, y, g);
    ll res = (a + x * n);
    while (res < 0) {
        res += m * n;
    }
    while (res > m * n) {
        res -= m * n;
    }
    cout << res;
}