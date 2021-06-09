//
// Created by kirilloid on 23.10.2020.
//

#include <bits/stdc++.h>

double countLength (int x1, int y1, int x2, int y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void solve(std::istream & is, std::ostream &os) {
    int R, x, y; // окружность
    int x1, y1, x2, y2; // прямая
    is >> R >> x >> y >> x1 >> y1 >> x2 >> y2;
    double a = countLength(x1, y1, x2, y2);
    double b = countLength(x, y, x2, y2);
    double c = countLength(x1, y1, x, y);
    double p = (a + b + c) / 2;
    double S = sqrt(p * (p - a) * (p - b) * (p - c));
    if (2 * S / a > R)
        os << "NO";
    else
        os << "YES";
}
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    solve(std::cin, std::cout);
}

