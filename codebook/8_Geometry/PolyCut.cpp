#include "GeometryDefaultFloat.h"
vector<pdd> cut(vector<pdd> poly, pdd s, pdd e) {
  vector<pdd> res;
  for (int i = 0; i < (int)poly.size(); ++i) {
    pdd cur = poly[i], prv = i ? poly[i - 1] : poly.back();
    bool side = ori(s, e, cur) < 0;
    if (side != (ori(s, e, prv) < 0))
      res.emplace_back(intersect(s, e, cur, prv));
    if (side)
      res.emplace_back(cur);
  }
  return res;
}
