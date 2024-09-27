#include "include/common.h"
typedef pair<pdd, pdd> Line;
struct Cir{ pdd O; double R; };
const double pi = acos(-1);
const double eps = 1e-8;
pll operator+(pll a, pll b)
{ return pll(a.F + b.F, a.S + b.S); }
pll operator-(pll a, pll b)
{ return pll(a.F - b.F, a.S - b.S); }
pll operator-(pll a)
{ return pll(-a.F, -a.S); }
pll operator*(pll a, ll b)
{ return pll(a.F * b, a.S * b); }
pdd operator/(pll a, double b)
{ return pdd(a.F / b, a.S / b); }
ll dot(pll a, pll b)
{ return a.F * b.F + a.S * b.S; }
ll cross(pll a, pll b)
{ return a.F * b.S - a.S * b.F; }
ll abs2(pll a)
{ return dot(a, a); }
double abs(pll a)
{ return sqrt(dot(a, a)); }
int sign(ll a)
{ return fabs(a) < eps ? 0 : a > 0 ? 1 : -1; }
int ori(pll a, pll b, pll c)
{ return sign(cross(b - a, c - a)); }
bool collinearity(pll p1, pll p2, pll p3)
{ return sign(cross(p1 - p3, p2 - p3)) == 0; }
bool btw(pll a, pll b, pll c) {
  return collinearity(a, b, c) && sign(dot(a - c, b - c)) <= 0;
}
bool seg_strict_intersect(pdd p1, pdd p2, pdd p3, pdd p4) {
  int a123 = ori(p1, p2, p3);
  int a124 = ori(p1, p2, p4);
  int a341 = ori(p3, p4, p1);
  int a342 = ori(p3, p4, p2);
  return a123 * a124 < 0 && a341 * a342 < 0;
}
bool seg_intersect(pdd p1, pdd p2, pdd p3, pdd p4) {
  int a123 = ori(p1, p2, p3);
  int a124 = ori(p1, p2, p4);
  int a341 = ori(p3, p4, p1);
  int a342 = ori(p3, p4, p2);
  if (a123 == 0 && a124 == 0)
    return btw(p1, p2, p3) || btw(p1, p2, p4) ||
      btw(p3, p4, p1) || btw(p3, p4, p2);
  return a123 * a124 <= 0 && a341 * a342 <= 0;
}
pdd intersect(pdd p1, pdd p2, pdd p3, pdd p4) {
  double a123 = cross(p2 - p1, p3 - p1);
  double a124 = cross(p2 - p1, p4 - p1);
  return (p4 * a123 - p3 * a124) / (a123 - a124); // C^3 / C^2
}
pdd orth(pdd p1)
{ return pdd(-p1.S, p1.F); }
pdd projection(pdd p1, pdd p2, pdd p3)
{ return p1 + (p2 - p1) * dot(p3 - p1, p2 - p1) / abs2(p2 - p1); }
pdd reflection(pdd p1, pdd p2, pdd p3)
{ return p3 + orth(p2 - p1) * cross(p3 - p1, p2 - p1) / abs2(p2 - p1) * 2; }
pdd linearTransformation(pdd p0, pdd p1, pdd q0, pdd q1, pdd r) {
	pdd dp = p1 - p0, dq = q1 - q0, num(cross(dp, dq), dot(dp, dq));
	return q0 + pdd(cross(r - p0, num), dot(r - p0, num)) / abs2(dp);
} // from line p0--p1 to q0--q1, apply to r 
