//
// Created by kirilloid on 18.12.2020.
//

#include <bits/stdc++.h>

std::set<int> set;
int d[1024];
int n;

bool findInSet(int m) {
    for (int s = m; s; s = (s - 1) & m) {
        if (set.find(s) == set.end())
            return false;
    }
    return true;
}

bool checkReplacement(int a, int b) {
    if (d[a] == d[b])
        return true;
    if (d[a] > d[b])
        std::swap(a, b);

    for (int i = 0; i < n; i++)
        if ((a >> i) % 2 < (b >> i) % 2)
            if (set.find(a + (1 << i)) != set.end())
                return true;
    return false;
}

bool checkChange() {
    for (auto i : set) {
        for (auto j : set) {
            if (!checkReplacement(i, j)) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    freopen("check.in", "r", stdin);
    freopen("check.out", "w", stdout);
    int m;
    std::cin >> n >> m;
    for (int i = 1; i < 1024; i++) {
        d[i] = d[(i >> 1)] + i % 2;
    }
    bool flag = false;
    for (int i = 0; i < m; i++) {
        int size;
        std::cin >> size;
        if (!size)
            flag = true;
        int element = 0;
        for (int j = 0; j < size; j++) {
            int t;
            std::cin >> t;
            element += (1 << (t - 1));
        }
        set.insert(element);
    }

    if (!flag) {
        std::cout << "NO";
        return 0;
    }

    if (!std::all_of(set.begin(), set.end(), findInSet)) {
        std::cout << "NO";
        return 0;
    }

    if (!checkChange()) {
        std::cout << "NO";
    } else
        std::cout << "YES";

}