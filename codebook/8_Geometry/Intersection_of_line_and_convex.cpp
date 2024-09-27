#include "GeometryDefaultFloat.h"
int cyc_tsearch(int n, auto pred); // ref: TanPointHull
int TangentDir(vector<pll> &C, pll dir) {
  return cyc_tsearch((int)C.size(), [&](int a, int b) {
    return cross(dir, C[a]) > cross(dir, C[b]);
  });
}
#define cmpL(i) sign(cross(C[i] - a, b - a))
pii lineHull(pll a, pll b, vector<pll> &C) {
  int A = TangentDir(C, a - b);
  int B = TangentDir(C, b - a);
  int n = (int)C.size();
  if (cmpL(A) < 0 || cmpL(B) > 0)
    return pii(-1, -1); // no collision
  auto gao = [&](int l, int r) {
    for (int t = l; (l + 1) % n != r;) {
      int m = ((l + r + (l < r ? 0 : n)) / 2) % n;
      (cmpL(m) == cmpL(t) ? l : r) = m;
    }
    return (l + !cmpL(r)) % n;
  };
  pii res = pii(gao(B, A), gao(A, B)); // (i, j)
  if (res.F == res.S) // touching the corner i
    return pii(res.F, -1);
  if (!cmpL(res.F) &&
    !cmpL(res.S)) // along side i, i+1
    switch ((res.F - res.S + n + 1) % n) {
    case 0: return pii(res.F, res.F);
    case 2: return pii(res.S, res.S);
    }
  /* crossing sides (i, i+1) and (j, j+1)
  crossing corner i is treated as side (i, i+1)
  returned in the same order as the line hits the
  convex */
  return res;
} // convex cut: (r, l]
