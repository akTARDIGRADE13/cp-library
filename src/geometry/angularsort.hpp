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

template <typename Point, typename BigInt = long long>
struct cmp {
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
