#include "Default_code.cpp"
using Line = pair<pll, pll>;
struct lineCmp {
  bool operator()(Line l1, Line l2) const {
    int X =
      (max(l1.F.F, l2.F.F) + min(l1.S.F, l2.S.F)) / 2;
    ll p1 =
         (X - l1.F.F) * l1.S.S + (l1.S.F - X) * l1.F.S,
       p2 =
         (X - l2.F.F) * l2.S.S + (l2.S.F - X) * l2.F.S,
       q1 = (l1.S.F - l1.F.F), q2 = (l2.S.F - l2.F.F);
    if (q1 == 0) p1 = l1.F.S + l1.S.S, q1 = 2;
    if (q2 == 0) p2 = l2.F.S + l2.S.S, q2 = 2;
    if (l1.F == l2.F || l2.F == l2.S) l1 = l2;
    return make_tuple((__int128)(p1 * q2), l1) <
      make_tuple((__int128)(p2 * q1), l2);
  }
};