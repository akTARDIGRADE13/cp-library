---
title: Offline Tree
documentation_of: //src/data_structure/offline_tree.hpp
---

あらかじめ与えられた値集合に対して座標圧縮を行い，Fenwick Tree を用いて

- 要素の挿入
- 要素の削除
- 存在判定
- `k` 番目に小さい要素の取得
- `x` 未満 / 以下の要素数の取得
- `x` 以上 / より大きい最小要素の取得

を高速に行うことができるデータ構造。

`pbds` の `tree` と同様に順序付き集合として扱えるが，扱う値は **事前に列挙されたものに限られる**。

- 外部の順序は `T` の `<` に従う
- `k` は **0-indexed**
- 同じ値は 2 回以上入らない

---

## 型

- `T`：比較可能な型

  - `std::ranges::sort`
  - `std::ranges::lower_bound`
  - `std::ranges::upper_bound`

  が使用できる必要がある。

---

## コンストラクタ

```

OfflineTree<T>()

```

空の `OfflineTree` を作る。

この状態では扱える値は存在しない。

**計算量**

$$
O(1)
$$

---

```

OfflineTree<T>(std::vector<T> xs)

```

値集合 `xs` をもとに `OfflineTree` を構築する。

内部では `xs` を sort し，重複を削除したものを管理対象とする。  
以後，`insert` / `erase` できるのはこの中に含まれる値のみである。

**計算量**

$$
O(n \log n)
$$

ここで，$n$ は与えた `xs` の長さ。

---

## idx_of

```

int idx_of(const T& x) const

```

内部で管理しているソート済み列における `x` の挿入位置を返す。  
これは `lower_bound(xs, x)` の位置に対応する。

`x` 自体が管理対象に含まれるとは限らない。

**計算量**

$$
O(\log n)
$$

---

## contains

```

bool contains(const T& x) const

```

`x` が現在集合に含まれていれば `true`，そうでなければ `false` を返す。

`x` が管理対象に含まれていない場合も `false` を返す。

**計算量**

$$
O(\log n)
$$

---

## insert

```

bool insert(const T& x)

```

`x` を集合に追加する。

- `x` が管理対象に含まれない場合は何もしない
- すでに `x` が集合に含まれている場合は何もしない

追加に成功したとき `true`，失敗したとき `false` を返す。

**計算量**

$$
O(\log n)
$$

---

## erase

```

bool erase(const T& x)

```

`x` を集合から削除する。

- `x` が管理対象に含まれない場合は何もしない
- `x` が集合に含まれていない場合は何もしない

削除に成功したとき `true`，失敗したとき `false` を返す。

**計算量**

$$
O(\log n)
$$

---

## size

```

int size() const

```

現在集合に含まれている要素数を返す。

**計算量**

$$
O(\log n)
$$

---

## empty

```

bool empty() const

```

集合が空なら `true`，そうでなければ `false` を返す。

**計算量**

$$
O(\log n)
$$

---

## order_of_key

```

int order_of_key(const T& x) const

```

`x` 未満の要素数を返す。

$$
\#\{ y \in S \mid y < x \}
$$

`pbds` の `tree::order_of_key` に対応する。

**計算量**

$$
O(\log n)
$$

---

## count_lt

```

int count_lt(const T& x) const

```

`x` 未満の要素数を返す。  
`order_of_key(x)` の別名。

$$
\#\{ y \in S \mid y < x \}
$$

**計算量**

$$
O(\log n)
$$

---

## count_le

```

int count_le(const T& x) const

```

`x` 以下の要素数を返す。

$$
\#\{ y \in S \mid y \le x \}
$$

**計算量**

$$
O(\log n)
$$

---

## find_by_order

```

std::optional<T> find_by_order(int k) const

```

`k` 番目に小さい要素を返す。  
ただし `k` は **0-indexed**。

- `k = 0` は最小要素
- `k = size() - 1` は最大要素

範囲外なら `std::nullopt` を返す。

`pbds` の `tree::find_by_order` に対応する。

**制約**

有効な要素を得たいなら

$$
0 \le k < |S|
$$

**計算量**

$$
O(\log n)
$$

---

## kth

```

std::optional<T> kth(int k) const

```

`k` 番目に小さい要素を返す。  
`find_by_order(k)` の別名。

範囲外なら `std::nullopt` を返す。

**計算量**

$$
O(\log n)
$$

---

## lower_bound

```

std::optional<T> lower_bound(const T& x) const

```

`x` 以上の最小要素を返す。

$$
\min \{ y \in S \mid y \ge x \}
$$

そのような要素が存在しないときは `std::nullopt` を返す。

**計算量**

$$
O(\log n)
$$

---

## upper_bound

```

std::optional<T> upper_bound(const T& x) const

```

`x` より大きい最小要素を返す。

$$
\min \{ y \in S \mid y > x \}
$$

そのような要素が存在しないときは `std::nullopt` を返す。

**計算量**

$$
O(\log n)
$$

---

## prev_le

```

std::optional<T> prev_le(const T& x) const

```

`x` 以下の最大要素を返す。

$$
\max \{ y \in S \mid y \le x \}
$$

そのような要素が存在しないときは `std::nullopt` を返す。

**計算量**

$$
O(\log n)
$$

---

## prev_lt

```

std::optional<T> prev_lt(const T& x) const

```

`x` 未満の最大要素を返す。

$$
\max \{ y \in S \mid y < x \}
$$

そのような要素が存在しないときは `std::nullopt` を返す。

**計算量**

$$
O(\log n)
$$

---

## 備考

このデータ構造は集合として振る舞うため，同じ値を複数個は持たない。  
重複を許したい場合は `multiset` 版を別に実装する必要がある。

また，扱いたい値はあらかじめコンストラクタに渡しておく必要がある。  
コンストラクタで与えていない値は後から `insert` できない。

---
