//
// Created by kirilloid on 11.10.2020.
//

#include <bits/stdc++.h>

using namespace std;

#define MAXN 10001

vector <pair<int, int>> vertexes(MAXN);

vector <int>  dist(MAXN, INT_MAX);

bool in_A[MAXN];

pair <int, int> get_min() {
    int min = INT_MAX;
    int index = 0;
    for (int i = 1; i < MAXN; i++) {
        if (dist[i] < min) {
            min = dist[i];
            index = i;
        }
    }
    dist[index] = INT_MAX;
    return {min, index};
}

int main() {
    int n;
    cin >> n;
    double weight = 0;
    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        vertexes[i] = {x, y};
    }
    for (int i = 2; i <= n; i++) {
        dist[i] = (vertexes[1].first - vertexes[i].first) * (vertexes[1].first - vertexes[i].first) +
                  (vertexes[1].second - vertexes[i].second) * (vertexes[1].second - vertexes[i].second);
    }
    in_A[1] = true;
    for (int i = 0; i < n - 1; i++) {
        pair <double, int> uv = get_min();
        weight += sqrt(uv.first);
        in_A[uv.second] = true;
        for (int j = 1; j <= n; j++) {
            if (!in_A[j] && (vertexes[j].first - vertexes[uv.second].first) * (vertexes[j].first - vertexes[uv.second].first) +
                            (vertexes[j].second - vertexes[uv.second].second) * (vertexes[j].second - vertexes[uv.second].second) < dist[j])
                dist[j] = (vertexes[j].first - vertexes[uv.second].first) * (vertexes[j].first - vertexes[uv.second].first) +
                          (vertexes[j].second - vertexes[uv.second].second) * (vertexes[j].second - vertexes[uv.second].second);
        }
    }
    cout << weight;
}