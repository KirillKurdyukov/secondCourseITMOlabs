//
// Created by kirilloid on 12.10.2020.
//

#include <bits/stdc++.h>

using namespace std;

#define MAXN 3001

vector<vector<int >> gr(MAXN);
bool used[MAXN];
vector<int> s;
int currentColor = 1;
int color[MAXN];
bool inStack[MAXN];
int timer, in[MAXN], up[MAXN];
map<string, int> assoc1;
map<int, string> assoc2;

void dfs(int v) {
    s.push_back(v);
    inStack[v] = true;
    used[v] = true;
    up[v] = in[v] = timer++;
    for (int u : gr[v]) {
        if (!used[u]) {
            dfs(u);
            up[v] = min(up[v], up[u]);
        } else if (inStack[u]) {
            up[v] = min(up[v], in[u]);
        }
    }
    if (up[v] == in[v]) {
        int last = -1;
        while(!s.empty() && last != v) {
            last = s.back();
            inStack[s.back()] = false;
            color[s.back()] = currentColor;
            s.pop_back();
        }
        currentColor++;
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        string basicString;
        cin >> basicString;
        assoc1["+" + basicString] = 2 * i;
        assoc2[2 * i] = "+" + basicString;
        assoc1["-" + basicString] = 2 * i + 1;
        assoc2[2 * i + 1] = "-" + basicString;
    }
    for (int i = 0; i < m; i++) {
        string a, b, x;
        cin >> a >> x >> b;
        gr[assoc1[a]].push_back(assoc1[b]);
        if (a[0] == '-')
            a[0] = '+';
        else
            a[0] = '-';
        if (b[0] == '-')
            b[0] = '+';
        else
            b[0] = '-';
        gr[assoc1[b]].push_back(assoc1[a]);
    }

    for (int i = 0; i < 2 * n; i++) {
        timer = 1;
        if (!used[i])
            dfs(i);
    }

    for (int i = 0; i < 2 * n; i++) {
        if (color[i] == color[i ^ 1]) {
            cout << -1;
            return 0;
        }
    }
    set<string> ans;
    for (int i = 0; i < 2 * n; i+=2) {
        if (color[i] < color[i ^ 1]) {
            ans.insert(assoc2[i].substr(1, assoc2[i].size() - 1));
        }
    }
    cout << ans.size() << endl;
    for (const auto& now : ans)
        cout << now << endl;
}
