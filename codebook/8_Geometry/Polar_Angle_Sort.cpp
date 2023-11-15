#include "Default_code.cpp"
int cmp(pll a, pll b, bool same = true) {
#define is_neg(k) (sign(k.S) < 0 || (sign(k.S) == 0 && sign(k.F) < 0))
  int A = is_neg(a), B = is_neg(b);
  if (A != B)
    return A < B;
  if (sign(cross(a, b)) == 0)
    return same ? abs2(a) < abs2(b) : -1;
  return sign(cross(a, b)) > 0;
}
