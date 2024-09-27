#include "GeometryDefaultInteger.h"
#include "Polar_Angle_Sort.cpp"
pll area_pair(Line a, Line b) 
{ return pll(cross(a.S - a.F, b.F - a.F), cross(a.S - a.F, b.S - a.F)); }
bool isin(Line l0, Line l1, Line l2) {
  // Check inter(l1, l2) strictly in l0
  auto [a02X, a02Y] = area_pair(l0, l2);
  auto [a12X, a12Y] = area_pair(l1, l2);
  if (a12X - a12Y < 0) a12X *= -1, a12Y *= -1;
  return (__int128) a02Y * a12X - (__int128) a02X * a12Y > 0; // C^4
}
/* Having solution, check size > 2 */
/* --^-- Line.X --^-- Line.Y --^-- */
vector<Line> halfPlaneInter(vector<Line> arr) {
  sort(all(arr), [&](Line a, Line b) -> int {
    if (cmp(a.S - a.F, b.S - b.F, 0) != -1)
      return cmp(a.S - a.F, b.S - b.F, 0);
    return ori(a.F, a.S, b.S) < 0;
  });
  deque<Line> dq(1, arr[0]);
  for (auto p : arr) {
    if (cmp(dq.back().S - dq.back().F, p.S - p.F, 0) == -1)
      continue;
    while ((int)dq.size() >= 2 && !isin(p, dq[(int)dq.size() - 2], dq.back()))
      dq.pop_back();
    while ((int)dq.size() >= 2 && !isin(p, dq[0], dq[1]))
      dq.pop_front();
    dq.emplace_back(p);
  }
  while ((int)dq.size() >= 3 && !isin(dq[0], dq[(int)dq.size() - 2], dq.back()))
    dq.pop_back();
  while ((int)dq.size() >= 3 && !isin(dq.back(), dq[0], dq[1]))
    dq.pop_front();
  return vector<Line>(all(dq));
}
