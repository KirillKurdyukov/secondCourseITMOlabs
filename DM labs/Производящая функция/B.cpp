//
// Created by kirilloid on 21.03.2021.
//

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define MD 998244353

int const M = 101;

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

struct num {

    ll number;
    num(ll number) : number(number) {
        while (this->number < 0)
            this->number = MD + this->number;
        this->number %= MD;
    }

    num() {
        number = 0;
    }

    num operator+(const num & a) const {
        return (number + a.number) % MD;
    }

    num operator-(const num & a) const {
        return (number - a.number + MD) % MD;
    }

    num operator*(const num & a) const {
        return (number * a.number) % MD;
    }

    num operator/(const num & a) const {
        return binPow(a.number, MD - 2) * number % MD;
    }

};
struct polynomial {
    vector<num> mn;

    void norm() {
        while (mn.size() > M)
            mn.pop_back();
    }

    polynomial(vector<num> mn) : mn(std::move(mn)) {
        norm();
    }

    num operator[](int index) const {
        if (index < mn.size())
            return mn[index];
        return 0;
    }
};

polynomial operator+(polynomial const &a, polynomial const &b) {
    vector<num> c(max(a.mn.size(), b.mn.size()));
    for (int i = 0; i < c.size(); i++) {
        c[i] = (a[i] + b[i]);
    }
    return c;
}

polynomial operator*(polynomial const &a, polynomial const &b) {
    vector<num> c(a.mn.size() + b.mn.size(), num(0));
    for (int i = 0; i < a.mn.size(); i++)
        for (int j = 0; j < b.mn.size(); j++)
            c[j + i] = c[j + i] + a[i] * b[j];
    return c;
}

polynomial operator/(polynomial const &a, polynomial const &b) {
    vector<num> c(M, num( 0));
    c[0] = a[0] / b[0];
    for (int i = 1; i < M; i++) {
        num cnt = 0;
        for (int j = 0; j < i; j++) {
            cnt = cnt + c[j] * b[i - j];
        }
        c[i] = a[i] - cnt;
        c[i] = c[i] / b[0];
    }
    return c;
}


int main() {
    int n, m;
    cin >> n >> m;
    vector<num> a(n + 1, 0);
    for (int i = 0; i < n + 1; i++) {
        ll t;
        cin >> t;
        a[i] = num(t);
    }
    polynomial p(a);
    vector<num> nk(2 * M + 1, num(0));
    nk[0] = 1;
    for (int i = 1; i <= M * 2; i++) {
        nk[i] = nk[i - 1] * i;
    }
    auto fun = [&nk](ll n) {
        num i = num(n % 2 ? - 1 : 1) * nk[2 * n];
        num k = num(1 - 2 * n) * binPow(4, n);
        num j = nk[n] * nk[n];
        return i / (j * k);
    };
    vector<polynomial> ans(3, polynomial({num(1)}));
    for (int i = 1; i <= M; i++) {
        polynomial g = p;
        for (int j = 0; j < i - 1; j++) {
            g = p * g;
        }
        ans[0] = ans[0] + polynomial({fun(i)}) * g;
    }
    for (int i = 0; i < m; i++)
        cout << ans[0][i].number << " ";
    cout << endl;
    for (int i = 1; i <= M; i++) {
        polynomial g = p;
        for (int j = 0; j < i - 1; j++) {
            g = p * g;
        }
        ans[1] = ans[1] + polynomial({num(1) / nk[i]}) * g;
    }
    for (int i = 0; i < m; i++)
        cout << ans[1][i].number << " ";
    cout << endl;
    ans[2] = polynomial({0});
    for (int i = 1; i <= M; i++) {
        polynomial g = p;
        for (int j = 0; j < i - 1; j++) {
            g = p * g;
        }
        ans[2] = ans[2] + polynomial({((i - 1) % 2 ? num(-1) : num(1)) / i }) * g;
    }
    for (int i = 0; i < m; i++)
        cout << ans[2][i].number << " ";
}