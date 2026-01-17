---
title: Fenwick Tree
documentation_of: //src/data_structure/fenwicktree.hpp
---

長さ $n$ の配列に対し，

- 要素の 1 点加算
- 区間和の取得

を高速に行うことができるデータ構造。

- 外部インデックスは **0-indexed**
- 区間は半開区間 $[l, r)$ を扱う

---

## 型

- `T`：加算・比較が可能な型

  - `lower_bound` / `upper_bound` を使用する場合，  
    木に格納される値は **非負**である必要がある。

---

## コンストラクタ

```

fenwick_tree<T>(int n)

```

長さ $n$ の配列  

$$
a_0, a_1, \dots, a_{n-1}
$$

を作る。初期値はすべて $0$。

**制約**

$$
0 \le n
$$

**計算量**

$$
O(n)
$$

---

## add

```

void add(int p, T x)

```

$$
a[p] \mathrel{+}= x
$$

を行う。

**制約**

$$
0 \le p < n
$$

**計算量**

$$
O(\log n)
$$

---

## sum

```

T sum(int l, int r)

```

$$
a_l + a_{l+1} + \dots + a_{r-1}
$$

を返す。

**制約**

$$
0 \le l \le r \le n
$$

**計算量**

$$
O(\log n)
$$

---

## lower_bound

```

size_t lower_bound(T w)

```

prefix sum が $w$ 以上となる最小の $i$ を返す。

$$
\sum_{k=0}^{i-1} a_k \ge w
$$

**注意**

- 返り値は **要素の index ではなく prefix の長さ**
- $$ w \le 0 $$ の場合は $0$
- 条件を満たす $i$ が存在しない場合は $n+1$
- 木に格納される値は **非負**である必要がある

**計算量**

$$
O(\log n)
$$

---

## upper_bound

```

size_t upper_bound(T w)

```

prefix sum が $w$ を超える最小の $i$ を返す。

$$
\sum_{k=0}^{i-1} a_k > w
$$

**注意**

- 返り値は **要素の index ではなく prefix の長さ**
- $$ w \le 0 $$ の場合は $0$
- 条件を満たす $i$ が存在しない場合は $n+1$
- 木に格納される値は **非負**である必要がある

**計算量**

$$
O(\log n)
$$

---
