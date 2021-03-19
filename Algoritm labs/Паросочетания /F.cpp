//
// Created by kirilloid on 28.02.2021.
//

#include <bits/stdc++.h>

using namespace std;

vector<int> p;
vector<vector<int>> gr;
vector<bool> used_L;
vector<bool> used_R;

bool dfs(int v) {
    if (used_L[v]) return false;
    used_L[v] = true;
    for (int u : gr[v]) {
        if (p[u] == -1 || dfs(p[u])) {
            p[u] = v;
            return true;
        }
    }
    return false;
}

void dfs1(int v) {
    if (used_L[v]) return;
    used_L[v] = true;
    for (int u : gr[v]) {
        used_R[u] = true;
        if (p[u] != -1) {
            dfs1(p[u]);
        }
    }
}

struct segment {
    int x1, y1, x2, y2;

    segment(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}
};

int main() {
    int n;
    cin >> n;
    vector<segment> L; // y1 == y2
    vector<segment> R; // x1 == x2
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        if (x1 > x2) {
            swap(x1, x2);
            swap(y1, y2);
        }

        if (y1 > y2) {
            swap(x1, x2);
            swap(y1, y2);
        }

        if (y1 == y2) {
            L.emplace_back(x1, y1, x2, y2);
        } else {
            R.emplace_back(x1, y1, x2, y2);
        }
    }
    p.assign(R.size(), -1);
    gr.assign(L.size(), vector<int>());
    for (int i = 0; i < L.size(); i++) {
        for (int j = 0; j < R.size(); j++) {
            if (L[i].y1 >= R[j].y1 && R[j].y2 >= L[i].y1
                && L[i].x1 <= R[j].x1 && L[i].x2 >= R[j].x1)
                gr[i].push_back(j);
        }
    }

    for (int i = 0; i < L.size(); i++) {
        used_L.assign(L.size(), false);
        dfs(i);
    }

    used_L.assign(L.size(), false);
    used_R.assign(R.size(), false);
    vector<bool> open(L.size(), true);

    for (int i = 0; i < R.size(); i++) {
        if (p[i] != -1)
            open[p[i]] = false;
    }

    for (int i = 0; i < L.size(); i++) {
        if (open[i])
            dfs1(i);
    }

    int ans = 0;

    for (int i = 0; i < L.size(); i++) {
        if (used_L[i])
            ans++;
    }

    for (int i = 0; i < R.size(); i++)
        if (!used_R[i])
            ans++;

    cout << ans << endl;
}