#include "include/common.h"
// beware of negative numbers!
void extgcd(ll a, ll b, ll c, ll &x, ll &y) {
  if (b == 0) x = c / a, y = 0;
  else {
    extgcd(b, a % b, c, y, x);
    y -= x * (a / b);
  }
} // |x| <= b/2, |y| <= a/2