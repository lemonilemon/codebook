#include "GeometryDefaultFloat.h"
vector<Line> go(Cir c1, Cir c2, int sign1) {
  // sign1 = 1 for outer tang, -1 for inter tang
  vector<Line> ret;
  double d_sq = abs2(c1.O - c2.O);
  if (sign(d_sq) == 0) return ret;
  double d = sqrt(d_sq);
  pdd v = (c2.O - c1.O) / d;
  double c = (c1.R - sign1 * c2.R) / d;
  if (c * c > 1) return ret;
  double h = sqrt(max(0.0, 1.0 - c * c));
  for (int sign2 = 1; sign2 >= -1; sign2 -= 2) {
    pdd n = pdd(v.F * c - sign2 * h * v.S,
      v.S * c + sign2 * h * v.F);
    pdd p1 = c1.O + n * c1.R;
    pdd p2 = c2.O + n * (c2.R * sign1);
    if (sign(p1.F - p2.F) == 0 and
      sign(p1.S - p2.S) == 0)
      p2 = p1 + perp(c2.O - c1.O);
    ret.emplace_back(Line(p1, p2));
  }
  return ret;
}
