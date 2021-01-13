//
// Created by kirilloid on 06.12.2020.
//

#include <bits/stdc++.h>

using namespace std;

int main() {
    string s;
    cin >> s;
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        if(memcmp(&s[a - 1], &s[c - 1], d - c + 1) == 0 && (a - b) == (c - d))
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
}
