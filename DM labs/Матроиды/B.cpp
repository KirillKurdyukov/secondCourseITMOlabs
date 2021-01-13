//
// Created by kirilloid on 16.12.2020.
//

#include <bits/stdc++.h>

using namespace std;

#define MAXN 200001
#define ll long long
int p[MAXN];
int r[MAXN];
set <pair<ll, pair<int, int>>> E;
map <pair<ll, pair<int, int>>, int> trans;
map <pair<ll, pair<int, int>>, bool> used;

int get(int v) {
    if (p[v] != v) {
        p[v] = get(p[v]);
    }
    return p[v];
}

void assoc(int v, int u) {
    int x = get(v);
    int y = get(u);
    if (x == y)
        return;
    if (r[x] == r[y]) {
        r[x]++;
    }
    if (r[x] < r[y])
        p[x] = y;
    else
        p[y] = x;
}

int main() {
    freopen("destroy.in", "r", stdin);
    freopen("destroy.out", "w", stdout);
    ll n, m, s;
    cin >> n >> m >> s;
    for (int i = 0; i < n; i++)
        p[i + 1] = i + 1;
    for (int i = 0; i < m; i++) {
        ll a, b, v;
        cin >> a >> b >> v;
        E.insert({v, {a, b}});
        trans[{v, {a, b}}] = i + 1;
    }

    for (auto i = E.rbegin(); i != E.rend(); i++) {
        if (get((*i).second.first) !=  get((*i).second.second)) {
            assoc((*i).second.first, (*i).second.second);
            used[*i] = false;
        } else {
            used[*i] = true;
        }
    }

    set<int> ans;
    ll cur_sum = 0;
    for (auto now : E) {
        if(cur_sum + now.first <= s && used[now]) {
            cur_sum+=now.first;
            ans.insert(trans[now]);
        }
    }

    cout << ans.size() << endl;
    for (auto now : ans)
        cout << now << " ";
}