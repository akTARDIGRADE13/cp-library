#pragma once

namespace akTARDIGRADE13::angular_sort {

namespace detail {

template <typename Point>
constexpr bool is_lower(const Point& a) {
    return (a.y < 0) || (a.y == 0 && a.x > 0);
}

template <typename Point, typename BigInt>
constexpr BigInt cross(const Point& a, const Point& b) {
    return (BigInt)a.x * (BigInt)b.y - (BigInt)a.y * (BigInt)b.x;
}

template <typename Point, typename BigInt>
constexpr BigInt norm2(const Point& a) {
    return (BigInt)a.x * (BigInt)a.x + (BigInt)a.y * (BigInt)a.y;
}

} // namespace detail

/**
 * @brief Polar Angle Sort (atan2-compatible)
 *
 * @details
 * 点（ベクトル）を原点からの偏角に基づいて並べるための比較器。
 * 並び順は各点 p=(x,y) に対する atan2(y,x) の昇順と同一と考えてよい。
 *
 * ただし実装では atan2 や浮動小数点演算を用いず、
 * 半平面判定と外積により整数演算のみで同じ角度順を実現する。
 *
 * 境界および特別な点の扱い：
 * - 負の x 軸 (x<0, y=0) は角 π として扱う
 * - 原点 (0,0) は atan2(0,0)=0 と定義する（角 0 相当）
 * - 偏角が等しい点同士（同一直線・同方向、原点を含む）は
 *   原点からの距離（二乗ノルム）の昇順でタイブレークする
 *
 * @tparam Point メンバ変数 x, y を持つ点型（整数型を想定）。
 * @tparam BigInt 外積・二乗距離の計算に用いる型（デフォルトは long long）。
 *
 * @note
 * BigInt が小さい場合、座標の大きさによっては外積・二乗距離がオーバーフローし得る。
 *
 * @complexity 比較 1 回あたり O(1)
 */
template <typename Point, typename BigInt = long long>
struct cmp {
    /**
     * @brief a が b より先（偏角が小さい、または同角で距離が短い）なら true。
     *
     * @param a 点 a。
     * @param b 点 b。
     * @return a が b より先なら true。
     *
     * @complexity O(1)
     */
    constexpr bool operator()(const Point& a, const Point& b) const {
        const bool la = detail::is_lower(a);
        const bool lb = detail::is_lower(b);
        if (la != lb) return la;

        const auto cr = detail::cross<Point, BigInt>(a, b);
        if (cr != 0) return cr > 0;

        const auto na = detail::norm2<Point, BigInt>(a);
        const auto nb = detail::norm2<Point, BigInt>(b);
        return na < nb;
    }
};

} // namespace akTARDIGRADE13::angular_sort
