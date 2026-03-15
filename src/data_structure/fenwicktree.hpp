#pragma once

#include <cassert>
#include <cstddef>
#include <vector>

namespace akTARDIGRADE13 {

template <class T>
struct fenwick_tree {

public:
    fenwick_tree() : _n(0) {}

    explicit fenwick_tree(int n) : _n(n), data(n) {}

    void add(int p, T x) {
        assert(0 <= p && p < _n);
        p++;
        while (p <= _n) {
            data[p - 1] += x;
            p += p & -p;
        }
    }

    T sum(int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        return sum(r) - sum(l);
    }

    std::size_t lower_bound(T w) const {
        if (w <= T{}) return 0;
        std::size_t idx = 0;
        T cur = T{};
        int step = 1;
        while (step < _n) step <<= 1;
        while (step) {
            int nxt = idx + step;
            if (nxt <= _n) {
                T val = cur + data[nxt - 1];
                if (val < w) {
                    idx = nxt;
                    cur = val;
                }
            }
            step >>= 1;
        }
        return idx + 1;
    }

    std::size_t upper_bound(T w) const {
        if (w <= T{}) return 0;
        std::size_t idx = 0;
        T cur = T{};
        int step = 1;
        while (step < _n) step <<= 1;
        while (step) {
            int nxt = idx + step;
            if (nxt <= _n) {
                T val = cur + data[nxt - 1];
                if (val <= w) {
                    idx = nxt;
                    cur = val;
                }
            }
            step >>= 1;
        }
        return idx + 1;
    }

private:
    int _n;
    std::vector<T> data;

    T sum(int r) const {
        T s = 0;
        while (r > 0) {
            s += data[r - 1];
            r -= r & -r;
        }
        return s;
    }
};

} // namespace akTARDIGRADE13
