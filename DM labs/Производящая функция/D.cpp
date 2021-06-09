//
// Created by kirilloid on 12.04.2021.
//

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int const M = 20;

struct fraction {
    ll p, q;
    fraction(ll p, ll q)  {
        ll t = gcd(p, q);
        p /= t;
        q /= t;
        this->p = p;
        this->q = q;
    }

    fraction(ll a) : fraction(a, 1) {}

    fraction() : fraction(0, 1) {}

    fraction operator+(const fraction &a) const {
        ll NOK = a.q * (q / gcd((long long)a.q, (long long)q));
        return fraction(a.p * (NOK / a.q) + (NOK / q) * p, NOK);
    }

    fraction operator-(const fraction &a) const {
        return fraction(p, q) + fraction(-a.p, a.q);
    }

    fraction operator*(const fraction &a) const {
        long long t = gcd((long long)p, (long long)a.q);
        long long g = p / t;
        long long h = a.q / t;
        long long t1 = gcd((long long)a.p, (long long)q);
        long long g1 = a.p / t1;
        long long h1 = q / t1;
        return fraction(g * g1, h * h1);
    }

    fraction operator/(const fraction &a) const {
        return fraction(p , q) * fraction(a.q, a.p);
    }

};

ostream& operator<<(ostream & os, const fraction &a) {
    return os << a.p << "/" << a.q;
}
template<class T>
struct polynomial {
    vector<T> mn;

    polynomial(vector<T> mn) : mn(std::move(mn)) {
        while (mn.size() > M)
            mn.pop_back();
    }

    polynomial(T val) : mn(1, val) {
    }

    T operator[](int index) const {
        if (index < mn.size())
            return mn[index];
        return 0;
    }
};

template<class T>
polynomial<T> operator+(polynomial<T> const &a, polynomial<T> const &b) {
    vector<T> c(max(a.mn.size(), b.mn.size()), 0LL);
    for (int i = 0; i < c.size(); i++) {
        c[i] = (a[i] + b[i]);
    }
    return c;
}

template<class T>
polynomial<T> operator*(polynomial<T> const &a, polynomial<T> const &b) {
    vector<T> c(M, 0LL);
    for (int i = 0; i < a.mn.size(); i++)
        for (int j = 0; j + i < M; j++)
            c[j + i] = c[j + i] + a[i] * b[j];
    return c;
}

template<class T>
polynomial<T> operator/(polynomial<T> const &a, polynomial<T> const &b) {
    vector<T> c(M, 0LL);
    c[0] = a[0] / b[0];
    for (int i = 1; i < M; i++) {
        T cnt = 0;
        for (int j = 0; j < i; j++) {
            cnt = cnt + c[j] * b[i - j];
        }
        c[i] = a[i] - cnt;
        c[i] = c[i] / b[0];
    }
    return c;
}


int main() {
    int r, k;
    cin >> r >> k;
    vector<fraction> p;
    for (int i = 0; i < k + 1; i++) {
        int t;
        cin >> t;
        p.emplace_back(t, 1);
    }
    polynomial<fraction> a(p);
    vector<long long> fac(2 * M, 1);
    for (int i = 1; i < fac.size(); i++) {
        fac[i] = fac[i - 1] * i;
    }
    polynomial<fraction> res(0);
    vector<fraction> uu(M);
    for (int i = 0; i < k + 1; i++) {
        polynomial<fraction> c(1);
        for(long long j = k; j > 0; j--)
            c = c * polynomial<fraction>(std::vector<fraction>{j-i, 1});
        c = c * polynomial<fraction>(fraction(1 , fac[k]));
        for (int j = 0; j < i; j++)
            c = c / polynomial<fraction>(fraction(r));
        res = res + c *  polynomial<fraction>(p[i]);
    }
    for (int i = 0; i < k + 1; i++)
        cout << res.mn[i] << " ";
}
/*
3 2
-1 4 -1
 */