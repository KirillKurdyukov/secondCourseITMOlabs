//
// Created by kirilloid on 16.12.2020.
//

#include <bits/stdc++.h>

using namespace std;

int p[100000];
int get(int v) {
    if (p[v] != v) {
        p[v] = get(p[v]);
    }
    return p[v];
}

int main() {
    freopen("schedule.in", "r", stdin);
    freopen("schedule.out", "w", stdout);
    for (int i = 0; i < 100000; i++)
        p[i] = i;
    int n;
    cin >> n;
    deque<pair<int, int>> tasks;
    long long fine = 0;
    for (int i = 0; i < n; i++) {
        int d, w;
        cin >> d >> w;
        if (d < n)
            tasks.emplace_back(w, d);
    }
    sort(tasks.begin(), tasks.end());
    reverse(tasks.begin(), tasks.end());
    while (!tasks.empty()) {
        pair <int, int> cur = tasks.front();
        tasks.pop_front();
        if (get(cur.second)) {
            int t = get(cur.second);
            p[t] = t - 1;
        } else {
            fine += cur.first;
        }
    }
    cout << fine;
}