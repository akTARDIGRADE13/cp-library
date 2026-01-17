---
title: Fenwick Tree
documentation_of: //src/data_structure/fenwicktree.hpp
---

点更新および区間和クエリを高速に処理するためのデータ構造。

- 外部インデックス：**0-indexed**
- 内部実装：**1-indexed**
- 区間：半開区間 `[l, r)`

## 型

- `T`：加算・比較が可能な型

  - `lower_bound` / `upper_bound` を使用する場合、  
    木に格納される値は **非負**である必要がある。

## 計算量

- 構築：`O(1)`（空） / `O(n)`（サイズ指定）
- 点更新：`O(log n)`
- 区間和：`O(log n)`
- `lower_bound` / `upper_bound`：`O(log n)`

## 区間和

- `[l, r)` の総和を返す  
- 制約：`0 <= l <= r <= n`

## lower_bound

prefix sum が `w` 以上となる最小の index を返す。

```

sum([0, i)) >= w

```

- `w <= 0` の場合：`0`
- 条件を満たす `i` が存在しない場合：`n+1`

## upper_bound

prefix sum が `w` を超える最小の index を返す。

```

sum([0, i)) > w

```

- `w <= 0` の場合：`0`
- 条件を満たす `i` が存在しない場合：`n+1`
```
