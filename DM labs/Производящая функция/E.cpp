//
// Created by kirilloid on 16.04.2021.
//

#include <bits/stdc++.h>

using namespace std;

int const M = 12;

template<class T>
T binPow(T a, int n) {
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

template<class T>
struct polynomial {
    vector<T> mn;

    polynomial(vector<T> mn) : mn(std::move(mn)) {
        while (this->mn.size() > M)
            this->mn.pop_back();
        while(this->mn.size() > 1 && this->mn.back() == 0)
            this->mn.pop_back();
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
template<class T>
ostream & operator<<(ostream &os, polynomial<T> const & a) {
    for (int i = 0; i < a.mn.size(); i++)
        os << a[i] << " ";
    return os;
}

template<class T>
polynomial<T> operator !(polynomial<T> const &a) {
    vector<T> c(M, 0LL);
    for (int i = 1; i < M; i++) {
        c[i - 1] = a[i] * i;
    }
    return c;
}

int main() {
    long long r;
    int d;
    cin >> r >> d;
    vector<int> p(d + 1);
    polynomial<long long> cringe = polynomial<long long>({1L, -r});
    polynomial<long long> R = polynomial<long long>(r);
    for (int i = 0; i < d + 1; i++)
        cin >> p[i];
    vector<long long> fac(M, 1);
    for (int i = 1; i < M; i++)
        fac[i] = fac[i - 1] * i;
    vector<pair<polynomial<long long>, polynomial<long long>>> pq;
    pq.emplace_back(polynomial<long long>(1L), cringe);
    for (int k = 1; k < M; k++) {
        polynomial<long long> curP = !pq[k - 1].first * cringe
                + pq[k - 1].first * R * polynomial<long long>(k);
        polynomial<long long> res(0);
        for (int j = 0; j < k; j++)
            res = res + R * polynomial<long long>(fac[k] / (fac[j] * fac[k - j]))
                    * binPow(cringe, k - j) * pq[j].first;
        pq.emplace_back((curP + polynomial<long long> (-1) * res) / R, binPow(cringe, k + 1));
    }
    polynomial<long long> P(0);
    polynomial<long long> Q = binPow(cringe, d + 1);
    for (int i = 0; i < d + 1; i++) {
        P = P + polynomial<long long>(p[i]) * binPow(cringe, d - i) * pq[i].first;
    }
    cout << P.mn.size() - 1<< endl;
    cout << P;
    cout << endl;
    cout << Q.mn.size() - 1 << endl;
    cout << Q;
}
/*
2
0
1

3
3
2 3 9 1
*/