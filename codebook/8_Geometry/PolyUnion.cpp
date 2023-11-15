#include "Default_code.cpp"
double rat(pll a, pll b) {
  return sign(b.F) ? (double)a.F / b.F : (double)a.S / b.S;
} // all poly. should be ccw
double polyUnion(vector<vector<pll>> &poly) {
  double res = 0;
  for (auto &p : poly)
    for (int a = 0; a < (int)p.size(); ++a) {
      pll A = p[a], B = p[(a + 1) % (int)p.size()];
      vector<pair<double, int>> segs = {{0, 0}, {1, 0}};
      for (auto &q : poly) {
        if (&p == &q) continue;
        for (int b = 0; b < (int)q.size(); ++b) {
          pll C = q[b], D = q[(b + 1) % (int)q.size()];
          int sc = ori(A, B, C), sd = ori(A, B, D);
          if (sc != sd && min(sc, sd) < 0) {
            double sa = cross(D - C, A - C), sb = cross(D - C, B - C);
            segs.emplace_back(sa / (sa - sb), sign(sc - sd));
          }
          if (!sc && !sd && &q < &p && sign(dot(B - A, D - C)) > 0) {
            segs.emplace_back(rat(C - A, B - A), 1);
            segs.emplace_back(rat(D - A, B - A), -1);
          }
        }
      }
      sort(all(segs));
      for (auto &s : segs) s.F = clamp(s.F, 0.0, 1.0);
      double sum = 0;
      int cnt = segs[0].second;
      for (int j = 1; j < (int)segs.size(); ++j) {
        if (!cnt) sum += segs[j].F - segs[j - 1].F;
        cnt += segs[j].S;
      }
      res += cross(A, B) * sum;
    }
  return res / 2;
}
