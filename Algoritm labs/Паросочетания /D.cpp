//
// Created by kirilloid on 28.02.2021.
//

#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define fast ios::sync_with_stdio(false);cin.tie(0);


struct incident {
    int h, m, x, y;
    incident(int h, int m, int x, int y) : h(h), m(m), x(x), y(y) {}

    [[nodiscard]] int getTime() const {
        return h * 60 + m;
    }
};

vector<vector<int>> gr;
vector<int> p;
vector<bool> used1;
vector<bool> used2;

bool dfs1(int v) {
    if (used1[v]) return false;
    used1[v] = true;
    for (int u : gr[v])
        if (p[u] == -1 || dfs1(p[u])) {
            p[u] = v;
            return true;
        }
    return false;
}

bool dfs2(int i) {
    if (used2[i]) return false;
    used2[i] = true;
    if (p[i] != -1)
        dfs2(p[i]);
    return true;
}

int main() {
    fast
    int n, v;
    cin >> n >> v;
    vector<incident> incidents;
    for (int i = 0; i < n; i++) {
        int h, m, x, y;
        char separator;
        cin >> h >> separator >> m >> x >> y;
        incidents.emplace_back(h, m, x, y);
    }

    sort(incidents.begin(), incidents.end(), [] (incident a, incident b) {return a.getTime() < b.getTime();});

    p.assign(n, -1);
    gr.assign(n, vector<int> ());

    auto dist = [&] (incident a, incident b) {
        double d = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
        return (d / v) * 60;
    };

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (incidents[i].getTime() + dist(incidents[i], incidents[j]) <= incidents[j].getTime())
                gr[i].push_back(j);
        }
    }

    for (int i = 0; i < n; i++) {
        used1.assign(n, false);
        dfs1(i);
    }

    int ans = 0;
    used2.assign(n, false);
    for (int i = n - 1; i >= 0; i--)
        ans+= dfs2(i);
    cout << ans << endl;
}