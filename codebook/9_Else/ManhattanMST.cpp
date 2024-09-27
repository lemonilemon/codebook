#include "8_Geometry/GeometryDefaultInteger.h"
#define p3i tuple<int, int, int>
struct DSU {
  vector<int> v;
  DSU(int n);
  int query(int u);
  void merge(int x, int y);
};
vector<p3i> manhattanMST(vector<pll> ps) {
  vector<int> id(ps.size());
  iota(id.begin(), id.end(), 0);
  vector<p3i> edges;
  for (int k = 0; k < 4; ++k) {
    sort(id.begin(), id.end(), [&](int i, int j) {
      return (ps[i] - ps[j]).F < (ps[j] - ps[i]).S;
    });
    map<int, int> sweep;
    for (int i : id) {
      for (auto it = sweep.lower_bound(-ps[i].S);
           it != sweep.end(); sweep.erase(it++)) {
        int j = it->second;
        pll d = ps[i] - ps[j];
        if (d.S > d.F) break;
        edges.emplace_back(d.S + d.F, i, j);
      }
      sweep[-ps[i].S] = i;
    }
    for (auto &p : ps)
      if (k & 1) p.F = -p.F;
      else swap(p.F, p.S);
  }
  return edges;
}
vector<int> MST(int n, const vector<p3i> &e) {
  vector<int> idx(e.size());
  iota(idx.begin(), idx.end(), 0);
  sort(idx.begin(), idx.end(), [&](int i, int j) {
    return get<0>(e[i]) < get<0>(e[j]);
  });
  vector<int> r;
  DSU dsu(n);
  for (int o : idx) {
    const auto &[w, i, j] = e[o];
    if (dsu.query(i) == dsu.query(j)) continue;
    r.push_back(o);
    dsu.merge(i, j);
  }
  return r;
}
