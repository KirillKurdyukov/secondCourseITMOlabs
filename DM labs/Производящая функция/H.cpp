//
// Created by kirilloid on 01.04.2021.
//

#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define MD 998244353

int const M = 5001;

template<class T>
T binPow(T a, long long n) {
    T res = 1;
    while (n)
        if (n & 1) {
            res = res * a;
            --n;
        } else {
            a = a * a;
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

ostream& operator<<(ostream& os, num const& t) {
    return os << t.number;
}

template<class T>
struct polynomial {
    vector<T> mn;


    void norm() {
        while (mn.size() > M)
            mn.pop_back();
    }

    polynomial(vector<T> mn) : mn(std::move(mn)) {
        norm();
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
    int k, n;
    cin >> k >> n;
    polynomial<num> p({0, 1});
    polynomial<num> q(1);
    for (int i = 3; i <= k; i++) {
        polynomial<num> new_p = q;
        new_p.mn.insert(new_p.mn.begin(), 0);
        new_p.norm();
        polynomial<num> new_q = polynomial(num(-1)) * p +  q;
        q = new_q;
        p = new_p;
    }
    polynomial<num> ans = p / q;
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << endl;
    }

}
