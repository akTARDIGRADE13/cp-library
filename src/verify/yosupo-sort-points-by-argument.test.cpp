#define PROBLEM "https://judge.yosupo.jp/problem/sort_points_by_argument"
#include "../../cp-library/angularsort"

#include <bits/stdc++.h>
using namespace std;
using namespace akTARDIGRADE13;

struct Point {
    int x;
    int y;
    int idx;
};

using cmp = angular_sort::cmp<Point>;

int main() {
    int N;
    cin >> N;
    vector<Point> p(N);
    for (int i = 0; i < N; ++i) {
        int x, y;
        cin >> x >> y;
        p[i] = {x, y, i};
    }
    ranges::sort(p, cmp{});
    for (auto& i : p) {
        cout << i.x << ' ' << i.y << '\n';
    }
    return 0;
}
