#include "ExtGCD.cpp"
ll solve(ll x1, ll m1, ll x2, ll m2) {
  ll g = gcd(m1, m2);
  if ((x2 - x1) % g) return -1; // no sol
  m1 /= g; m2 /= g;
  ll x, y;
  extgcd(m1, m2, __gcd(m1, m2), x, y);
  ll lcm = m1 * m2 * g;
  ll res = x * (x2 - x1) * m1 + x1;
  // be careful with overflow
  return (res % lcm + lcm) % lcm;
}
