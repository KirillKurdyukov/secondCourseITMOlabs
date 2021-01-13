//
// Created by kirilloid on 01.12.2020.
//


#include <bits/stdc++.h>

using namespace std;

int N;
int cnt = 0;
bool request(int i, int j) {
    if (cnt == 100000) {
        for (int k = 0; k < N + 1; k++)
            cout << 0 << " ";
        exit(0);
    }
    cout << 1 << " " << i << " " << j << endl;
    string s;
    cnt++;
    cin >> s;
    if (s == "YES")
        return true;
    else
        return false;
}

void Sort(int l, int m, int r, int* mas){
    int b[r - l + 1];
    int k = 0;
    int i = l;
    int j = m + 1;
    while ( k < r - l + 1 ) {
        if (j == r + 1 || (i < m + 1 && request(mas[i], mas[j]))) {
            b[k++] = mas[i++];
        } else {
            b[k++] = mas[j++];
        }
    }
    for (int s = 0; s < k; s++) {
        mas[l] = b[s];
        l++;
    }
}
void MergeSort(int l, int r, int* mas) {
    if (l < r) {
        int m = (l + r) / 2;
        MergeSort(l, m, mas);
        MergeSort(m + 1, r, mas);
        Sort(l, m, r, mas);
    }
}

int main() {
    int N;
    cin >> N;
    int mas[N];
    for (int i = 0; i < N; i++)
        mas[i] = i + 1;
    MergeSort(0, N - 1, mas);
    cout << 0 << " ";
    for (int i = 0; i < N; i++)
        cout << mas[i] << " ";
}