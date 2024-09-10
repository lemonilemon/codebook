#include "GeometryDefaultFloat.h"
void rotatingSweepLine(vector<pii> &ps) {
  int n = (int)ps.size(), m = 0;
  vector<int> id(n), pos(n);
  vector<pii> line(n * (n - 1));
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      if (i != j) line[m++] = pii(i, j);
  sort(all(line), [&](pii a, pii b) {
    return cmp(ps[a.S] - ps[a.F], ps[b.S] - ps[b.F]);
  }); // cmp(): polar angle compare
  iota(all(id), 0);
  sort(all(id), [&](int a, int b) {
    if (ps[a].S != ps[b].S) return ps[a].S < ps[b].S;
    return ps[a] < ps[b];
  }); // initial order, since (1, 0) is the smallest
  for (int i = 0; i < n; ++i) pos[id[i]] = i;
  for (int i = 0; i < m; ++i) {
    auto l = line[i];
    // do something
    tie(pos[l.F], pos[l.S], id[pos[l.F]], id[pos[l.S]]) = make_tuple(pos[l.S], pos[l.F], l.S, l.F);
  }
}
