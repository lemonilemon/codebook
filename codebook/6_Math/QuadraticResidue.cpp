#include "include/common.h"
// Berlekamp-Rabin, log^2(p)
ll trial(ll y, ll z, ll m) {
  ll a0 = 1, a1 = 0, b0 = z, b1 = 1, p = (m - 1) / 2;
  while (p) {
    if (p & 1)
      tie(a0, a1) =
        make_pair((a1 * b1 % m * y + a0 * b0) % m,
          (a0 * b1 + a1 * b0) % m);
    tie(b0, b1) =
      make_pair((b1 * b1 % m * y + b0 * b0) % m,
        (2 * b0 * b1) % m);
    p >>= 1;
  }
  if (a1) return inv(a1, m);
  return -1;
}
mt19937 rd(49);
ll psqrt(ll y, ll p) { // sqrt(y) mod p
  if (y == 0) return 0;
  if (fpow(y, (p - 1) / 2, p) != 1) return -1;
  for (int i = 0; i < 30; i++) {
    ll z = rd() % p;
    if (z * z % p == y) return z;
    ll x = trial(y, z, p);
    if (x == -1) continue;
    return x;
  }
  return -1;
}
