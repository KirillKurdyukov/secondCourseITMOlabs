//
// Created by kirilloid on 20.12.2020.
//

#include <bits/stdc++.h>

using namespace std;

#define SIZE 400001
int cnt[SIZE];
int p[SIZE];
int pn[SIZE];
int c[SIZE];
int cn[SIZE];

int main() {
    string s;
    cin >> s;
//    s = s + "#";
    for (char i : s)
        cnt[i]++;
    for (int i = 1; i < SIZE; i++)
        cnt[i] += cnt[i - 1];
    for (int i = 0; i < s.size(); i++)
        p[--cnt[s[i]]] = i;
    c[p[0]] = 0;
    int classes = 1;
    for (int i = 1; i < s.size(); i++) {
        if (s[p[i]] != s[p[i - 1]]) classes++;
        c[p[i]] = classes - 1;
    }

    int n = s.size();
    for (int h = 0; (1 << h) <= 2 * n; ++h) {
        for (int i = 0; i < n; ++i) {
            pn[i] = p[i] - (1 << h);
            if (pn[i] < 0) {
                pn[i] += 2 * n;
                pn[i] %= n;
            }
        }
        for (int & i : cnt)
            i = 0;
        for (int i = 0; i < n; ++i)
            ++cnt[c[pn[i]]];
        for (int i = 1; i < classes; ++i)
            cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; --i)
            p[--cnt[c[pn[i]]]] = pn[i];
        cn[p[0]] = 0;
        classes = 1;
        for (int i = 1; i < n; ++i) {
            int mid1 = (p[i] + (1 << h)) % n, mid2 = (p[i - 1] + (1 << h)) % n;
            if (c[p[i]] != c[p[i - 1]] || c[mid1] != c[mid2])
                ++classes;
            cn[p[i]] = classes - 1;
        }
        for (int i = 0; i < s.size(); i++)
            c[i] = cn[i];
    }
    vector<int> ans;
    for (int i = 1; i < s.size(); i++)
        if (c[p[i - 1]] != c[p[i]])
            ans.push_back(p[i - 1]);

    ans.push_back(p[n - 1]);
    int a;
    cin >> a;
    if (a > ans.size()) {
        cout << "IMPOSSIBLE";
        return 0;
    }

    for (int i = ans[a - 1]; i < ans[a - 1] + s.size(); i++)
        cout << s[i % s.size()];
}