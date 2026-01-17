#pragma once

#include <cassert>
#include <cstddef>
#include <vector>

namespace akTARDIGRADE13 {

/**
 * @brief Fenwick Tree（Binary Indexed Tree）
 *
 * 点更新および区間和クエリを高速に処理するためのデータ構造。
 *
 * - 外部から見えるインデックスは **0-indexed**
 * - 内部では **1-indexed** の Fenwick Tree を使用
 * - 半開区間 `[l, r)` を基本とする
 *
 * @tparam T
 * 加算・比較が可能な型。
 *
 * @note
 * `lower_bound` / `upper_bound` を使用する場合、
 * 木に格納される値は **非負**である必要がある。
 */
template <class T>
struct fenwick_tree {

public:
    /**
     * @brief サイズ 0 の Fenwick Tree を構築する。
     *
     * @complexity O(1)
     */
    fenwick_tree() : _n(0) {}

    /**
     * @brief サイズ @p n の Fenwick Tree を構築する（全要素 0 初期化）。
     *
     * @param n 配列サイズ
     *
     * @complexity O(n)
     */
    explicit fenwick_tree(int n) : _n(n), data(n) {}

    /**
     * @brief 位置 @p p に値 @p x を加算する。
     *
     * @param p 加算する位置（0-indexed）
     * @param x 加算する値
     *
     * @pre 0 <= p < n
     *
     * @complexity O(log n)
     */
    void add(int p, T x) {
        assert(0 <= p && p < _n);
        p++;
        while (p <= _n) {
            data[p - 1] += x;
            p += p & -p;
        }
    }

    /**
     * @brief 区間 `[l, r)` の総和を返す。
     *
     * @param l 左端（含む）
     * @param r 右端（含まない）
     *
     * @return 区間 `[l, r)` に含まれる要素の総和
     *
     * @pre 0 <= l <= r <= n
     *
     * @complexity O(log n)
     */
    T sum(int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        return sum(r) - sum(l);
    }

    /**
     * @brief prefix sum が @p w 以上となる最小の index を返す。
     *
     * 正確には、次を満たす最小の @p i を返す：
     *
     * ```
     * sum([0, i)) >= w
     * ```
     *
     * 返り値は **要素の index ではなく prefix の長さ**である点に注意。
     *
     * @param w 目標とする累積和
     *
     * @return
     * - `w <= 0` の場合：`0`
     * - 条件を満たす最小の `i`
     *
     * @note
     * - この関数は格納される値が **非負**であることを仮定する。
     * - 条件を満たす `i` が存在しない場合、`n+1` が返る。
     *
     * @complexity O(log n)
     */
    std::size_t lower_bound(T w) const {
        if (w <= T{}) return 0;
        std::size_t idx = 0;
        T cur = T{};
        int step = 1;
        while (step < _n) step <<= 1;
        while (step) {
            std::size_t nxt = idx + step;
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

    /**
     * @brief prefix sum が @p w を超える最小の index を返す。
     *
     * 正確には、次を満たす最小の @p i を返す：
     *
     * ```
     * sum([0, i)) > w
     * ```
     *
     * 返り値は **要素の index ではなく prefix の長さ**である。
     *
     * @param w 目標とする累積和
     *
     * @return
     * - `w <= 0` の場合：`0`
     * - 条件を満たす最小の `i`
     *
     * @note
     * - この関数は格納される値が **非負**であることを仮定する。
     * - 条件を満たす `i` が存在しない場合、`n+1` が返る。
     *
     * @complexity O(log n)
     */
    std::size_t upper_bound(T w) const {
        if (w <= T{}) return 0;
        std::size_t idx = 0;
        T cur = T{};
        int step = 1;
        while (step < _n) step <<= 1;
        while (step) {
            std::size_t nxt = idx + step;
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
    int _n;              ///< 配列サイズ
    std::vector<T> data; ///< Fenwick Tree の内部配列（1-indexed 相当）

    /**
     * @brief prefix 区間 `[0, r)` の総和を返す。
     *
     * @param r 右端（含まない）
     *
     * @return 区間 `[0, r)` の総和
     *
     * @complexity O(log n)
     */
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
