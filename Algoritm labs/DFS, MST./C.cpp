//
// Created by kirilloid on 10.10.2020.
//

#include <bits/stdc++.h>

using namespace std;

#define MAXN 20001
vector<vector<int> > gr(MAXN);
bool used[MAXN];
int timer, in[MAXN], up[MAXN];
set <int> numVertex;

void dfs(int v, int p = -1) {
    used[v] = true;
    in[v] = up[v] = timer++;
    int count = 0;
    for (int w : gr[v]) {
        if (w == p)
            continue;
        if (used[w])
            up[v] = min(up[v], in[w]);
        else {
            count++;
            dfs(w, v);
            up[v] = min(up[v], up[w]);
            if (p != -1 && up[w] >= in[v])
                numVertex.insert(v);
        }
    }
    if (count > 1 && p == -1) {
        numVertex.insert(v);
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        gr[a].push_back(b);
        gr[b].push_back(a);
    }
    for (int i = 1; i <= n; i++) {
        timer = 1;
        if (!used[i])
            dfs(i);
    }
    cout << numVertex.size() << endl;
    for (int now : numVertex)
        cout << now << " ";
    return 0;
}