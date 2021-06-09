//
// Created by kirilloid on 14.11.2020.
//

#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    int cnt = 0;
    while (true) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j < i; j++) {
                cout << j << " " << i << endl;
                string s;
                cin >> s;
                if (s == "WIN")
                    return 0;
            }
        }
    }
}