//
// Created by kirilloid on 31.03.2021.
//

#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define MD 998244353

int const M = 7;

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
polynomial<long long> one(1);
polynomial<long long> minus_one(-1);

template<class T>
polynomial<T> forSet(polynomial<T> & a) {
    polynomial<T> ans = one;
    for (int i = 1; i <= M; i++) {
        polynomial<T> cur = binPow(polynomial<long long>({0, 1ll}), i);
        ans = ans * (one / binPow((one + minus_one * cur), a[i]));
    }
    return ans;
}

template<class T>
polynomial<T> parse(istream & is) {
    char trash;
    char c;
    is >> c;
    switch (c) {
        case 'P': {
            is >> trash;
            polynomial<T> a = parse<T>(is);
            is >> trash;
            polynomial<T> b = parse<T>(is);
            is >> trash;
            return a * b;
        }
        case 'L': {
            is >> trash;
            polynomial<T> b = parse<T>(is);
            b.mn[0] = 0;
            is >> trash;
            return one / (one + minus_one * b);
        }
        case 'B': {
            return polynomial<long long>({0, 1ll});
        }
        case 'S' : {
            is >> trash;
            polynomial<T> d = parse<long long>(is);
            is >> trash;
            return forSet(d);
        }
        default:
            throw "sosi";
    }
}

int main() {
    polynomial<long long> a = parse<long long>(cin);
    for (int i = 0; i < 7; i++)
        cout << a[i] << " ";
}