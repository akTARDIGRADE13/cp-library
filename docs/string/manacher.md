---
title: Manacher's algorithm
documentation_of: //src/string/manacher.hpp
---

列に含まれる回文を高速に扱うためのアルゴリズム。

文字位置と文字間をあわせた $2n+1$ 個の中心それぞれについて，
回文の情報を $O(n)$ で求める。

---

## 型

- `T`：`==` で比較可能な型

---

## 関数

```

template <class T>
std::vector<int> manacher(const std::vector<T>& s)

```

列 `s` に対する Manacher の結果を返す。

返り値 `ret` の長さは

$$
2|s|+1
$$

である。

添字 `i` は次を表す。

- `i = 2k+1` ：`s[k]` を中心とする
- `i = 2k` ：`s[k-1]` と `s[k]` の間を中心とする

`ret[i]` はその中心における回文の大きさを表す。

区間 $[l, r)$ が回文であることと

$$
\mathrm{ret}[l+r] \ge r-l+1
$$

は同値である。

**制約**

$$
0 \le |s|
$$

**計算量**

$$
O(|s|)
$$

---

```

std::vector<int> manacher(const std::string& s)

```

文字列 `s` に対する Manacher の結果を返す。

返り値・意味・計算量は `vector<T>` 版と同様。

**制約**

$$
0 \le |s|
$$

**計算量**

$$
O(|s|)
$$

---

## 備考

奇数長回文と偶数長回文を統一的に扱える。

---
