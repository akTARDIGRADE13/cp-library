#define PROBLEM "https://judge.yosupo.jp/problem/ordered_set"
#include "../cp-library/fenwicktree"

#include <bits/stdc++.h>
using namespace std;

template <class T>
struct Tree {
    const vector<T> xs;
    akTARDIGRADE13::fenwick_tree<int> ft;
    const int n;

    Tree() : n(0) {}
    explicit Tree(const vector<T>& _xs) : xs(_xs), n(xs.size()), ft(xs.size()) {}

    int idx_of(const T& x) const { return distance(xs.begin(), ranges::lower_bound(xs, x)); }

    bool contains(const T& x) const {
        int i = idx_of(x);
        if (i >= n || xs[i] != x) return false;
        return ft.sum(i, i + 1) != 0;
    }

    bool insert(const T& x) {
        int i = idx_of(x);
        if (i >= n || xs[i] != x) return false;
        if (ft.sum(i, i + 1) != 0) return false;
        ft.add(i, 1);
        return true;
    }

    bool erase(const T& x) {
        int i = idx_of(x);
        if (i >= n || xs[i] != x) return false;
        if (ft.sum(i, i + 1) == 0) return false;
        ft.add(i, -1);
        return true;
    }

    int size() const { return ft.sum(0, n); }

    // # of elements < x
    int count_lt(const T& x) const {
        int r = distance(xs.begin(), ranges::lower_bound(xs, x));
        return ft.sum(0, r);
    }

    // # of elements <= x
    int count_le(const T& x) const {
        int r = distance(xs.begin(), ranges::upper_bound(xs, x));
        return ft.sum(0, r);
    }

    // k-th smallest (0-indexed). none if out of range.
    optional<T> kth(int k) const {
        int tot = ft.sum(0, n);
        if (k < 0 || k >= tot) return nullopt;
        size_t len = ft.lower_bound(k + 1);
        int idx = (int)len - 1;
        return xs[idx];
    }

    // min element >= x
    optional<T> next_ge(const T& x) const {
        int pos = distance(xs.begin(), ranges::lower_bound(xs, x));
        int k = ft.sum(0, pos);
        return kth(k);
    }

    // max element <= x
    optional<T> prev_le(const T& x) const {
        int cnt = count_le(x);
        if (cnt == 0) return nullopt;
        return kth(cnt - 1);
    }
};

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
    Tree<int> tree(num);

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
            auto ans = tree.next_ge(x[i]);
            cout << (ans ? *ans : -1) << '\n';
        }
    }
    return 0;
}
