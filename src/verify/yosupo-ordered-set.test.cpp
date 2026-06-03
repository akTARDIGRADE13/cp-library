#define PROBLEM "https://judge.yosupo.jp/problem/ordered_set"

#include "../../cp-library/offline_tree"
#include "../../cp-library/tree"

#include <bits/stdc++.h>
using namespace std;

template <class A, class B>
void assert_same_basic(const A& lhs, const B& rhs) {
    assert(lhs.size() == rhs.size());
    assert(lhs.empty() == rhs.empty());

    auto lhs_min = lhs.kth(0);
    auto rhs_min = rhs.kth(0);
    assert(lhs_min == rhs_min);

    auto lhs_max = lhs.kth(lhs.size() - 1);
    auto rhs_max = rhs.kth(rhs.size() - 1);
    assert(lhs_max == rhs_max);
}

template <class A, class B, class T>
void assert_same_for_value(const A& lhs, const B& rhs, const T& x) {
    assert(lhs.count(x) == rhs.count(x));
    assert(lhs.contains(x) == rhs.contains(x));

    assert(lhs.order_of_key(x) == rhs.order_of_key(x));
    assert(lhs.count_lt(x) == rhs.count_lt(x));
    assert(lhs.count_le(x) == rhs.count_le(x));

    assert(lhs.lower_bound(x) == rhs.lower_bound(x));
    assert(lhs.upper_bound(x) == rhs.upper_bound(x));
    assert(lhs.prev_le(x) == rhs.prev_le(x));
    assert(lhs.prev_lt(x) == rhs.prev_lt(x));
}

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

    akTARDIGRADE13::OfflineSet<int> offline_set(num);
    akTARDIGRADE13::OnlineSet<int> online_set;

    akTARDIGRADE13::OfflineMultiSet<int> offline_multiset(num);
    akTARDIGRADE13::OnlineMultiSet<int> online_multiset;

    for (int i = 0; i < N; ++i) {
        bool ok1 = offline_set.insert(a[i]);
        bool ok2 = online_set.insert(a[i]);
        assert(ok1 == ok2);

        bool mok1 = offline_multiset.insert(a[i]);
        bool mok2 = online_multiset.insert(a[i]);
        assert(mok1 == mok2);
    }

    assert_same_basic(offline_set, online_set);
    assert_same_basic(offline_multiset, online_multiset);

    for (int i = 0; i < Q; ++i) {
        if (t[i] == 0) {
            bool ok1 = offline_set.insert(x[i]);
            bool ok2 = online_set.insert(x[i]);
            assert(ok1 == ok2);

            bool mok1 = offline_multiset.insert(x[i]);
            bool mok2 = online_multiset.insert(x[i]);
            assert(mok1 == mok2);

        } else if (t[i] == 1) {
            bool ok1 = offline_set.erase(x[i]);
            bool ok2 = online_set.erase(x[i]);
            assert(ok1 == ok2);

            bool mok1 = offline_multiset.erase(x[i]);
            bool mok2 = online_multiset.erase(x[i]);
            assert(mok1 == mok2);

        } else if (t[i] == 2) {
            auto ans1 = offline_set.kth(x[i] - 1);
            auto ans2 = online_set.kth(x[i] - 1);
            assert(ans1 == ans2);

            auto mans1 = offline_multiset.kth(x[i] - 1);
            auto mans2 = online_multiset.kth(x[i] - 1);
            assert(mans1 == mans2);

            cout << (ans1 ? *ans1 : -1) << '\n';

        } else if (t[i] == 3) {
            int ans1 = offline_set.count_le(x[i]);
            int ans2 = online_set.count_le(x[i]);
            assert(ans1 == ans2);

            int mans1 = offline_multiset.count_le(x[i]);
            int mans2 = online_multiset.count_le(x[i]);
            assert(mans1 == mans2);

            cout << ans1 << '\n';

        } else if (t[i] == 4) {
            auto ans1 = offline_set.prev_le(x[i]);
            auto ans2 = online_set.prev_le(x[i]);
            assert(ans1 == ans2);

            auto mans1 = offline_multiset.prev_le(x[i]);
            auto mans2 = online_multiset.prev_le(x[i]);
            assert(mans1 == mans2);

            cout << (ans1 ? *ans1 : -1) << '\n';

        } else {
            auto ans1 = offline_set.lower_bound(x[i]);
            auto ans2 = online_set.lower_bound(x[i]);
            assert(ans1 == ans2);

            auto mans1 = offline_multiset.lower_bound(x[i]);
            auto mans2 = online_multiset.lower_bound(x[i]);
            assert(mans1 == mans2);

            cout << (ans1 ? *ans1 : -1) << '\n';
        }

        assert_same_basic(offline_set, online_set);
        assert_same_basic(offline_multiset, online_multiset);

        assert_same_for_value(offline_set, online_set, x[i]);
        assert_same_for_value(offline_multiset, online_multiset, x[i]);
    }

    return 0;
}
