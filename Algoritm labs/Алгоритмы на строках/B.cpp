//
// Created by kirilloid on 06.12.2020.
//

#include <bits/stdc++.h>

using namespace std;

void prefix_function(string & s) {
    vector<int> pi(s.length(), 0);
    for (int i = 1; i < s.length(); i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j]) ++j;
        pi[i] = j;
    }
    for (int i : pi)
        cout << i << " ";
}

int main() {
    string s;
    cin >> s;
    prefix_function(s);
}