#include "GeometryDefaultInteger.h"
bool down(pll k) {
  return sign(k.S) < 0 ||
    (sign(k.S) == 0 && sign(k.F) < 0);
}
int cmp(pll a, pll b, bool same = true) {
  int A = down(a), B = down(b);
  if (A != B) return A < B;
  if (sign(cross(a, b)) == 0)
    return same ? abs2(a) < abs2(b) : -1;
  return sign(cross(a, b)) > 0;
}
