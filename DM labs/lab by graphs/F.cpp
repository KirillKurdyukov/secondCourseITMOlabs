//
// Created by kirilloid on 01.12.2020.
//

#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    deque <int> code_prufer(n - 2);
    set<int> help;
    vector<bool> used(n + 1, false);
    vector<int> in_prufer(n + 1, 0);
    for (int i = 0; i < n - 2; i++) {
        cin >> code_prufer[i];
        in_prufer[code_prufer[i]]++;
    }

    for (int i = 1; i <= n; i++)
        if (!in_prufer[i])
            help.insert(i);

    for (int i = 0; i < n - 2; i++) {
        cout << code_prufer.front() << " " << *help.begin() << endl;
        used[*help.begin()] = true;
        help.erase(help.begin());
        in_prufer[code_prufer.front()]--;
        if (!in_prufer[code_prufer.front()])
             help.insert(code_prufer.front());
        code_prufer.pop_front();
    }

    for (int i = 1; i <= n; i++) {
        if (!used[i] && *help.begin() != i) {
            cout << *help.begin() << " " << i;
            return 0;
        }
    }
}