//
// Created by kirilloid on 22.05.2021.
//

#include <bits/stdc++.h>

using namespace std;

typedef __int128 ll;

struct result {
    ll d;
    ll x;
    ll y;
};

result gcd(ll a, ll b) {
    if (b == 0) {
        return {a, 1, 0};
    }
    auto[d, x, y] = gcd(b, a % b);
    return {d, y, x - y * (a / b)};
}

ll binPow(ll a, ll N, ll MD) {
    ll res = 1;
    while (N)
        if (N & 1) {
            res *= a;
            res %= MD;
            --N;
        } else {
            a *= a;
            a %= MD;
            N /= 2;
        }
    return res;
}

ll get_reverse(ll a, ll mod) {
    auto[g, x, _] = gcd(a, mod);
    x /= g;
    if (x < 0) {
        x += mod;
    }
    return x;
}

pair<ll, ll> get_factorization(ll n) {
    for (int i = 2; i <= n; i++) {
        if (n % i == 0) {
            return {i, n / i};
        }
    }
}

int main() {
    long long n, e, c;
    cin >> n >> e >> c;
    auto[p, q] = get_factorization(n);

    auto mod = (p - 1) * (q - 1);
    auto d = get_reverse(e, mod);

    cout << (long long) binPow(c, d, n);

    return 0;
}
