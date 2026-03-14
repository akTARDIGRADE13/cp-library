#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_palindromes"
#include "../../cp-library/manacher"

#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    auto ret = akTARDIGRADE13::manacher(s);
    int sz = ret.size();
    for (int i = 1; i < sz - 1; ++i) cout << ret[i] << ' ';
    cout << endl;
    return 0;
}
