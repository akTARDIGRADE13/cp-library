#pragma once

#include <algorithm>
#include <optional>
#include <vector>

#include "../../cp-library/fenwicktree"

namespace akTARDIGRADE13 {

template <class T>
struct OfflineTree {
    std::vector<T> xs;
    akTARDIGRADE13::fenwick_tree<int> ft;
    int n;

    OfflineTree() : xs(), ft(0), n(0) {}

    explicit OfflineTree(std::vector<T> _xs) : xs(std::move(_xs)), ft(0), n(0) {
        std::ranges::sort(xs);
        xs.erase(std::ranges::unique(xs).begin(), xs.end());
        n = static_cast<int>(xs.size());
        ft = akTARDIGRADE13::fenwick_tree<int>(n);
    }

    int idx_of(const T& x) const { return distance(xs.begin(), std::ranges::lower_bound(xs, x)); }

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

    bool empty() const { return size() == 0; }

    int order_of_key(const T& x) const {
        int r = distance(xs.begin(), std::ranges::lower_bound(xs, x));
        return ft.sum(0, r);
    }

    int count_le(const T& x) const {
        int r = distance(xs.begin(), std::ranges::upper_bound(xs, x));
        return ft.sum(0, r);
    }

    int count_lt(const T& x) const { return order_of_key(x); }

    std::optional<T> find_by_order(int k) const {
        int tot = size();
        if (k < 0 || k >= tot) return std::nullopt;
        std::size_t pos = ft.lower_bound(k + 1);
        int idx = static_cast<int>(pos) - 1;
        return xs[idx];
    }

    std::optional<T> kth(int k) const { return find_by_order(k); }

    std::optional<T> lower_bound(const T& x) const {
        int pos = distance(xs.begin(), std::ranges::lower_bound(xs, x));
        int k = ft.sum(0, pos);
        return find_by_order(k);
    }

    std::optional<T> upper_bound(const T& x) const {
        int pos = distance(xs.begin(), std::ranges::upper_bound(xs, x));
        int k = ft.sum(0, pos);
        return find_by_order(k);
    }

    std::optional<T> prev_le(const T& x) const {
        int cnt = count_le(x);
        if (cnt == 0) return std::nullopt;
        return find_by_order(cnt - 1);
    }

    std::optional<T> prev_lt(const T& x) const {
        int cnt = order_of_key(x);
        if (cnt == 0) return std::nullopt;
        return find_by_order(cnt - 1);
    }
};

} // namespace akTARDIGRADE13
