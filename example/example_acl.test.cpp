#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"
#include <bits/stdc++.h>
#include <atcoder/dsu>
using namespace std;
using namespace atcoder;

int main() {
    int n, q;
    cin >> n >> q;
    dsu uf(n);
    while (q--) {
        int t, u, v;
        cin >> t >> u >> v;
        if (t) {
            cout << uf.same(u, v) << '\n';
        } else {
            uf.merge(u, v);
        }
    }
    return 0;
}
