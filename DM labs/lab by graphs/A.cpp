//
// Created by kirilloid on 01.12.2020.
//

#include <bits/stdc++.h>

using namespace std;

#define MAXN 4001

bool gr[MAXN][MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 1; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < s.size(); j++) {
            if (s[j] == '0')
                gr[i + 1][j + 1] = gr[j + 1][i + 1] = false;
            else
                gr[i + 1][j + 1] = gr[j + 1][i + 1] = true;
        }
    }

    deque<int> d;
    for (int i = 1; i <= n; i++)
        d.push_back(i);

    for (int i = 0; i < n * (n - 1); i++) {
        if (!gr[d[0]][d[1]]) {
            int j = 2;
            while (!gr[d[0]][d[j]] ||
                    !gr[d[1]][d[j + 1]])
                j++;
            swap(d[1], d[j]);
        }
        d.push_back(d.front());
        d.pop_front();
    }

    for (auto now : d) {
        cout << now <<  " ";
    }
//    for (int i = 1; i <= n; i++) {
//        for (int j = 1; j <= n; j++) {
//            if (gr[i][j])
//                cout << '1' << " ";
//            else
//                cout << '0' << " ";
//        }
//        cout << endl;
//    }


}