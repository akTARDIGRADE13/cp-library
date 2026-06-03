#pragma once

#include <cstddef>
#include <limits>
#include <optional>
#include <utility>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

namespace akTARDIGRADE13 {

template <class T, bool Multi = false>
struct OnlineTree;

template <class T>
struct OnlineTree<T, false> {
    using tree_type =
        __gnu_pbds::tree<T, __gnu_pbds::null_type, std::less<T>, __gnu_pbds::rb_tree_tag,
                         __gnu_pbds::tree_order_statistics_node_update>;

    tree_type st;

    OnlineTree() : st() {}

    int count(const T& x) const { return st.find(x) != st.end() ? 1 : 0; }

    bool contains(const T& x) const { return st.find(x) != st.end(); }

    bool insert(const T& x) { return st.insert(x).second; }

    bool erase(const T& x) {
        auto it = st.find(x);
        if (it == st.end()) return false;
        st.erase(it);
        return true;
    }

    int erase_all(const T& x) { return erase(x) ? 1 : 0; }

    int size() const { return static_cast<int>(st.size()); }

    bool empty() const { return st.empty(); }

    int order_of_key(const T& x) const { return static_cast<int>(st.order_of_key(x)); }

    int count_lt(const T& x) const { return order_of_key(x); }

    int count_le(const T& x) const { return order_of_key(x) + count(x); }

    std::optional<T> find_by_order(int k) const {
        if (k < 0 || k >= size()) return std::nullopt;

        auto it = st.find_by_order(static_cast<std::size_t>(k));
        if (it == st.end()) return std::nullopt;

        return *it;
    }

    std::optional<T> kth(int k) const { return find_by_order(k); }

    std::optional<T> lower_bound(const T& x) const {
        auto it = st.lower_bound(x);
        if (it == st.end()) return std::nullopt;
        return *it;
    }

    std::optional<T> upper_bound(const T& x) const {
        auto it = st.upper_bound(x);
        if (it == st.end()) return std::nullopt;
        return *it;
    }

    std::optional<T> prev_le(const T& x) const {
        auto it = st.upper_bound(x);
        if (it == st.begin()) return std::nullopt;
        --it;
        return *it;
    }

    std::optional<T> prev_lt(const T& x) const {
        auto it = st.lower_bound(x);
        if (it == st.begin()) return std::nullopt;
        --it;
        return *it;
    }
};

template <class T>
struct OnlineTree<T, true> {
    using id_type = long long;
    using node_type = std::pair<T, id_type>;

    static constexpr id_type min_id = std::numeric_limits<id_type>::min();
    static constexpr id_type max_id = std::numeric_limits<id_type>::max();

    using tree_type =
        __gnu_pbds::tree<node_type, __gnu_pbds::null_type, std::less<node_type>,
                         __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

    tree_type st;
    id_type next_id;

    OnlineTree() : st(), next_id(0) {}

    int count(const T& x) const { return count_le(x) - count_lt(x); }

    bool contains(const T& x) const { return count(x) != 0; }

    bool insert(const T& x) {
        st.insert({x, next_id++});
        return true;
    }

    bool erase(const T& x) {
        auto it = st.lower_bound({x, min_id});
        if (it == st.end() || it->first != x) return false;

        st.erase(it);
        return true;
    }

    int erase_all(const T& x) {
        int erased = 0;

        auto it = st.lower_bound({x, min_id});
        while (it != st.end() && it->first == x) {
            auto nxt = it;
            ++nxt;
            st.erase(it);
            it = nxt;
            ++erased;
        }

        return erased;
    }

    int size() const { return static_cast<int>(st.size()); }

    bool empty() const { return st.empty(); }

    int order_of_key(const T& x) const { return static_cast<int>(st.order_of_key({x, min_id})); }

    int count_lt(const T& x) const { return order_of_key(x); }

    int count_le(const T& x) const { return static_cast<int>(st.order_of_key({x, max_id})); }

    std::optional<T> find_by_order(int k) const {
        if (k < 0 || k >= size()) return std::nullopt;

        auto it = st.find_by_order(static_cast<std::size_t>(k));
        if (it == st.end()) return std::nullopt;

        return it->first;
    }

    std::optional<T> kth(int k) const { return find_by_order(k); }

    std::optional<T> lower_bound(const T& x) const {
        auto it = st.lower_bound({x, min_id});
        if (it == st.end()) return std::nullopt;
        return it->first;
    }

    std::optional<T> upper_bound(const T& x) const {
        auto it = st.upper_bound({x, max_id});
        if (it == st.end()) return std::nullopt;
        return it->first;
    }

    std::optional<T> prev_le(const T& x) const {
        auto it = st.upper_bound({x, max_id});
        if (it == st.begin()) return std::nullopt;
        --it;
        return it->first;
    }

    std::optional<T> prev_lt(const T& x) const {
        auto it = st.lower_bound({x, min_id});
        if (it == st.begin()) return std::nullopt;
        --it;
        return it->first;
    }
};

template <class T>
using OnlineSet = OnlineTree<T, false>;

template <class T>
using OnlineMultiSet = OnlineTree<T, true>;

} // namespace akTARDIGRADE13
