---
title: Tree
documentation_of: //src/data_structure/tree.hpp
---

GNU pbds の `tree` を用いて

* 要素の挿入
* 要素の削除
* 存在判定
* 指定した値の個数の取得
* `k` 番目に小さい要素の取得
* `x` 未満 / 以下の要素数の取得
* `x` 以上 / より大きい最小要素の取得
* `x` 以下 / 未満の最大要素の取得

を高速に行うことができるデータ構造。

`OfflineTree` と異なり，扱う値を事前に列挙する必要がなく，任意の値を後から `insert` できる。

* 外部の順序は `T` の `<` に従う
* `k` は **0-indexed**
* `Multi = false` のとき，同じ値は 2 回以上入らない
* `Multi = true` のとき，同じ値を複数個持つことができる

---

## 型

```
template <class T, bool Multi = false>
struct OnlineTree;
```

* `T`：比較可能な型

  * `std::less<T>`
  * `pbds::tree` 上での順序比較

  が使用できる必要がある。

* `Multi`：重複を許すかどうか

  * `false`：集合として扱う
  * `true`：多重集合として扱う

また，次の alias が定義されている。

```
template <class T>
using OnlineSet = OnlineTree<T, false>;

template <class T>
using OnlineMultiSet = OnlineTree<T, true>;
```

---

## コンストラクタ

```
OnlineTree<T, Multi>()
```

空の `OnlineTree` を作る。

**計算量**

$$
O(1)
$$

---

## count

```
int count(const T& x) const
```

現在含まれている `x` の個数を返す。

* `Multi = false` のとき，返り値は `0` または `1`
* `Multi = true` のとき，返り値は現在の多重度

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

`Multi = true` の場合は，`x` の個数が 1 個以上なら `true` を返す。

**計算量**

$$
O(\log n)
$$

---

## insert

```
bool insert(const T& x)
```

`x` を追加する。

* `Multi = false` のとき，すでに `x` が含まれている場合は何もしない
* `Multi = true` のとき，すでに `x` が含まれていても個数を 1 増やす

追加に成功したとき `true`，失敗したとき `false` を返す。

`Multi = true` の場合は常に追加できるため，基本的に `true` を返す。

**計算量**

$$
O(\log n)
$$

---

## erase

```
bool erase(const T& x)
```

`x` を 1 個削除する。

* `x` が現在 1 個も含まれていない場合は何もしない
* `Multi = true` の場合も，削除されるのは 1 個だけである

削除に成功したとき `true`，失敗したとき `false` を返す。

**計算量**

$$
O(\log n)
$$

---

## erase_all

```
int erase_all(const T& x)
```

`x` をすべて削除する。

削除した個数を返す。

* `x` が現在 1 個も含まれていない場合は `0` を返す
* `Multi = false` のとき，返り値は `0` または `1`
* `Multi = true` のとき，返り値は削除前の `x` の多重度

**計算量**

`Multi = false` の場合

$$
O(\log n)
$$

`Multi = true` の場合，削除する個数を $c$ として

$$
O(c \log n)
$$

---

## size

```
int size() const
```

現在含まれている要素数を返す。

`Multi = true` の場合は，重複を個別に数える。
例えば `3` が 2 個，`5` が 1 個含まれているなら `size()` は `3` を返す。

**計算量**

$$
O(1)
$$

---

## empty

```
bool empty() const
```

空なら `true`，そうでなければ `false` を返す。

**計算量**

$$
O(1)
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

`Multi = true` の場合は，重複を個別に数える。

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

`Multi = true` の場合は，重複を個別に数える。

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

`Multi = true` の場合は，重複を個別に数える。

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

* `k = 0` は最小要素
* `k = size() - 1` は最大要素

範囲外なら `std::nullopt` を返す。

`pbds` の `tree::find_by_order` に対応する。

`Multi = true` の場合は，重複も別々の要素として数える。
例えば `{1, 3, 3, 5}` に対して `find_by_order(1)` と `find_by_order(2)` はどちらも `3` を返す。

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

`Multi = true` の場合でも，返す値は 1 つである。

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

`Multi = true` の場合でも，`x` と等しい要素はスキップされる。

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

`Multi = true` の場合でも，返す値は 1 つである。

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

`Multi = true` の場合でも，`x` と等しい要素はスキップされる。

**計算量**

$$
O(\log n)
$$

---

## 使用例

```
akTARDIGRADE13::OnlineSet<int> st;

st.insert(3); // true
st.insert(3); // false

st.count(3);    // 1
st.contains(3); // true
st.size();      // 1
```

```
akTARDIGRADE13::OnlineMultiSet<int> mst;

mst.insert(3); // true
mst.insert(3); // true
mst.insert(3); // true

mst.count(3); // 3
mst.size();   // 3

mst.erase(3);

mst.count(3); // 2
```

alias を使わずに直接書くこともできる。

```
akTARDIGRADE13::OnlineTree<int> st;        // set
akTARDIGRADE13::OnlineTree<int, true> mst; // multiset
```

---

## 備考

このデータ構造は GNU pbds の `tree` を用いているため，GCC 環境に依存する。

`OfflineTree` と異なり，扱いたい値をあらかじめ列挙する必要はない。
そのため，後から現れる値をそのまま `insert` できる。

`Multi = false` の場合は集合として振る舞うため，同じ値を複数個は持たない。
`Multi = true` の場合は多重集合として振る舞い，同じ値を複数個持つことができる。

`Multi = true` の内部実装では，値 `x` に一意な ID を付けた組 `(x, id)` を pbds の `tree` に格納することで，同じ値を複数個管理している。

---

