//
// Created by kirilloid on 01.12.2020.
//

#include <bits/stdc++.h>

using namespace std;

bool gr[11][11];

vector<int> cnt(11, 0);

int n, m;

void findCount(int i, vector<vector<int>> baskets) {
    if (i == n + 1) {
        cnt[baskets.size()]++;
        return;
    }

    for (auto & basket : baskets) {
        bool flag = true;
        for (int u : basket) {
            if (gr[u][i])
                flag = false;
        }
        if (flag) {
            basket.push_back(i);
            findCount(i  + 1, baskets);
            basket.pop_back();
        }
    }
    baskets.push_back({i});
    findCount(i  + 1, baskets);
}

struct polynomial {
    vector<int> mn;

    polynomial(vector<int> mn) : mn(mn) {}
};

polynomial operator+(polynomial const &a, polynomial const &b) {
    vector<int> new_mx(min(a.mn.size(), b.mn.size()), 0);
    for (int i = 0; i < min(a.mn.size(), b.mn.size()); i++) {
        new_mx[i] = a.mn[i] + b.mn[i];
    }
    for (int j = min(a.mn.size(), b.mn.size()); j < max(a.mn.size(), b.mn.size()); j++) {
        if (a.mn.size() > b.mn.size())
            new_mx.push_back(a.mn[j]);
        else
            new_mx.push_back(b.mn[j]);
    }
    return new_mx;
}

polynomial operator*(polynomial const &a, polynomial const &b) {
    vector<int> new_mx(a.mn.size() + b.mn.size() - 1, 0);
    for (int i = 0; i < a.mn.size(); i++) {
        vector <int> temp(i + b.mn.size(), 0);
        for (int j = 0; j < b.mn.size(); j++) {
            temp[j + i] = a.mn[i] * b.mn[j];
        }
        new_mx = (temp + new_mx).mn;
    }
    return new_mx;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        gr[u][v] = true;
        gr[v][u] = true;
    }

    vector<int> ans(n + 1, 0);
    polynomial a(ans);
    findCount(1, vector<vector<int>> ());

    for (int i = 1; i <= n; i++) {
        polynomial temp({cnt[i]});
        for (int j = 0;  j < i; j++) {
            temp = temp * polynomial({-j , 1});
        }
        a = a + temp;
    }

//    while (!a.mn[n])
//        n--;
    cout << n << endl;
    for (int i = n; i >= 0; i--)
        cout << a.mn[i] << " ";
}