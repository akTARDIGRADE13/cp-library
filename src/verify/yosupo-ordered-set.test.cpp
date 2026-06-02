#define PROBLEM "https://judge.yosupo.jp/problem/ordered_set"
#include "../../cp-library/offline_tree"

#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, Q;
    cin >> N >> Q;
    vector<int> a(N), t(Q), x(Q), num;
    num.reserve(N + Q);
    for (int i = 0; i < N; ++i) {
        cin >> a[i];
        num.push_back(a[i]);
    }
    for (int i = 0; i < Q; ++i) {
        cin >> t[i] >> x[i];
        num.push_back(x[i]);
    }
    ranges::sort(num);
    num.erase(ranges::unique(num).begin(), num.end());
    akTARDIGRADE13::OfflineTree<int> tree(num);

    for (int i = 0; i < N; ++i) {
        tree.insert(a[i]);
    }

    for (int i = 0; i < Q; ++i) {
        if (t[i] == 0) {
            tree.insert(x[i]);
        } else if (t[i] == 1) {
            tree.erase(x[i]);
        } else if (t[i] == 2) {
            auto ans = tree.kth(x[i] - 1);
            cout << (ans ? *ans : -1) << '\n';
        } else if (t[i] == 3) {
            cout << tree.count_le(x[i]) << '\n';
        } else if (t[i] == 4) {
            auto ans = tree.prev_le(x[i]);
            cout << (ans ? *ans : -1) << '\n';
        } else {
            auto ans = tree.lower_bound(x[i]);
            cout << (ans ? *ans : -1) << '\n';
        }
    }
    return 0;
}
