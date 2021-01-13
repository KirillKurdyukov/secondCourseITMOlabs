//
// Created by kirilloid on 19.12.2020.
//

#include <bits/stdc++.h>

using namespace std;

#define SIZE 400001
#define alp 400001
int cnt[alp];
int p[SIZE];
int pn[SIZE];
int c[22][SIZE];

int lcp(int i, int j) {
    int ans = 0;
    for (int k = 19; k >= 0; --k)
        if (c[k][i] == c[k][j] && c[k][j] != 0) {
            ans += (1 << k);
            i += (1 << k);
            j += (1 << k);
        }
    return ans;
}

int main() {
    string s;
    cin >> s;
    s = s + "#";
    for (char i : s)
        cnt[i]++;
    for (int i = 1; i < alp; i++)
        cnt[i] += cnt[i - 1];
    for (int i = 0; i < s.size(); i++)
        p[abs(--cnt[s[i]])] = i;
    c[0][p[0]] = 1;
    int classes = 2;
    for (int i = 1; i < s.size(); i++) {
        if (s[p[i]] != s[p[i - 1]]) classes++;
        c[0][p[i]] = classes - 1;
    }

    int n = s.size();
    for (int h = 0; (1 << h) < n; ++h) {
//        cout << h << endl;
//        for (int i = 0; i < s.size(); i++) {
//            for (int j = p[i]; j < s.size() + p[i]; j++)
//                cout << s[j % s.size()];
//            cout << " " << c[h][p[i]];
//            cout << endl;
//        }
        for (int i = 0; i < n; ++i) {
            pn[i] = p[i] - (1 << h);
            if (pn[i] < 0) {
                pn[i] += 2 * n;
                pn[i] %= n;
            }
        }
        memset(cnt, 0, classes * sizeof(int));
        for (int i = 0; i < n; ++i)
            ++cnt[c[h][pn[i]]];
        for (int i = 1; i < classes; ++i)
            cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; --i)
            p[abs(--cnt[c[h][pn[i]]])] = pn[i];
        c[h + 1][p[0]] = 1;
        classes = 2;
        for (int i = 1; i < n; ++i) {
            int mid1 = (p[i] + (1 << h)) % n, mid2 = (p[i - 1] + (1 << h)) % n;
            if (c[h][p[i]] != c[h][p[i - 1]] || c[h][mid1] != c[h][mid2])
                ++classes;
            c[h + 1][p[i]] = classes - 1;
        }
    }

    for (int i = 1; i < s.size(); i++) {
        cout << p[i] + 1 << " ";
    }

    cout << endl;
//    cout << c[1][1] << " " << c[1][2] << endl;
    for (int i = 2; i < s.size(); i++) {
        cout << lcp(p[i - 1], p[i]) << " ";
    }
}