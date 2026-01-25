---
title: Polar Angle Sort (atan2-compatible)
documentation_of: //src/geometry/angularsort.hpp
---

点（ベクトル）を原点からの **偏角** に基づいて並べるための比較器。

並び順は，各点 $p=(x,y)$ に対する
$$
\operatorname{atan2}(y, x)
$$
の昇順と同じである。

ただし，実装では `atan2` や浮動小数点演算を用いず，
半平面判定と外積を用いることで，
上記と同じ角度順を **整数演算のみ**で実現している。

境界および特別な点の扱いは次のとおりである。

- 負の $x$ 軸 $(x<0,\,y=0)$ は角 $\pi$ として扱う
- 原点 $(0,0)$ については $\operatorname{atan2}(0,0)=0$ と定義する
- 偏角が等しい点同士（同一直線・同方向，原点を含む）は，原点からの距離の昇順でタイブレークする

---

## 型

* `Point`

  * メンバ変数 `x`, `y` を持つ型
  * 整数型を想定

* `BigInt`

  * 外積・二乗距離の計算に用いる型
  * デフォルトは `long long`

---

## 比較器

```

template <typename Point, typename BigInt = long long>
struct cmp {
    bool operator()(const Point& a, const Point& b) const;
};

```

`a` が `b` より先（偏角が小さい，または同角で距離が短い）場合に `true` を返す。

---

## 計算量

* 比較 1 回あたり
  $$
  O(1)
  $$

---
