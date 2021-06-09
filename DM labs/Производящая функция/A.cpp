//
// Created by kirilloid on 20.03.2021.
//

#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define MD 998244353

int const M = 1000;

ll binPow(ll a, int n) {
    ll res = 1;
    while (n)
        if (n & 1) {
            res *= a;
            res %= MD;
            --n;
        } else {
            a *= a;
            a %= MD;
            n /= 2;
        }
    return res;
}

struct polynomial {
    vector<ll> mn;

    void norm() {
        while (!mn.back() && mn.size() > 1)
            mn.pop_back();
    }

    polynomial(vector<ll> mn) : mn(std::move(mn)) {
        norm();
    }

    ll operator[](int index) const {
        if (index < mn.size())
            return mn[index];
        return 0;
    }
};

polynomial operator+(polynomial const &a, polynomial const &b) {
    vector<ll> c(max(a.mn.size(), b.mn.size()), 0);
    for (int i = 0; i < c.size(); i++) {
        c[i] = (a.mn[i] + b.mn[i]) % MD;
    }
    return c;
}

polynomial operator*(polynomial const &a, polynomial const &b) {
    vector<ll> c(a.mn.size() + b.mn.size(), 0);
    for (int i = 0; i < a.mn.size(); i++) {
        for (int j = 0; j + i < c.size() && j < b.mn.size(); j++) {
            c[j + i] += (a[i] * b[j]) % MD;
            c[j + i] %= MD;
        }
    }
    return c;
}

polynomial operator/(polynomial const &a, polynomial const &b) {
    vector<ll> c(M, 0);
    c[0] = a[0] * binPow(b[0], MD - 2);
    for (int i = 1; i < M; i++) {
        ll cnt = 0;
        for (int j = 0; j < i; j++) {
            cnt += (c[j] * b[i - j]) % MD;
        }
        cnt %= MD;
        c[i] = (a[i] - cnt + MD) % MD;
    }
    return c;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<ll> p(2001, 0), q(2001, 0);
    for (int i = 0; i <= n; i++)
        cin >> p[i];
    for (int i = 0; i <= m; i++)
        cin >> q[i];
    polynomial a(p);
    polynomial b(q);
    polynomial c = a + b;
    polynomial d = a * b;
    polynomial e = a / b;
    cout << c.mn.size() - 1 << endl;
    for (long long i : c.mn)
        cout << i << " ";
    cout << endl;
    cout << d.mn.size() - 1 << endl;
    for (long long i : d.mn)
        cout << i << " ";
    cout << endl;
    for (int i = 0; i < 1000; i++)
        cout << e.mn[i] << " ";
}