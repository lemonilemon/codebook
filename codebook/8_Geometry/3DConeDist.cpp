#include "include/common.h"
const double eps = 1e-12, pi = acos(-1);
struct point {
  ld x, y, z;
};
ld r, h;

bool on_edge(point p) {
  return abs(p.z) < eps &&
    abs(p.x * p.x + p.y * p.y - r * r) < eps;
}

bool on_bottom(point p) { return abs(p.z) < eps; }

ld straight(point a, point b) {
  return sqrtl((a.x - b.x) * (a.x - b.x) +
    (a.y - b.y) * (a.y - b.y) +
    (a.z - b.z) * (a.z - b.z));
}

ld arc(point a, point b) {
  if (abs(a.x) < eps && abs(a.y) < eps &&
    abs(a.z - h) < eps)
    return straight(a, b);
  swap(a, b);
  if (abs(a.x) < eps && abs(a.y) < eps &&
    abs(a.z - h) < eps)
    return straight(a, b);
  swap(a, b);

  ld ans = 1e18;

  for (int t = 0; t <= 1; t++) {
    double alpha = (a.x < 0 ? pi + atan2l(-a.y, -a.x)
                            : atan2l(a.y, a.x));
    if (alpha < 0) alpha += 2 * pi;
    alpha *= r / sqrtl(h * h + r * r);
    double lA = sqrtl(
      a.x * a.x + a.y * a.y + (a.z - h) * (a.z - h));

    double beta = (b.x < 0 ? pi + atan2l(-b.y, -b.x)
                           : atan2l(b.y, b.x));
    if (beta < 0) beta += 2 * pi;
    beta *= r / sqrtl(h * h + r * r);
    double lB = sqrtl(
      b.x * b.x + b.y * b.y + (b.z - h) * (b.z - h));

    double Ax = lA * cosl(alpha),
           Ay = lA * sinl(alpha), Bx = lB * cosl(beta),
           By = lB * sinl(beta);
    ans = min(ans,
      sqrtl((Ax - Bx) * (Ax - Bx) +
        (Ay - By) * (Ay - By)));
    a.x = -a.x;
    b.x = -b.x;
  }
  return ans;
}

ld distance(point a, point b) {
  if (on_bottom(a) && !on_edge(a) && !on_bottom(b))
    return 1e18;
  if (on_bottom(b) && !on_edge(b) && !on_bottom(a))
    return 1e18;

  if (on_bottom(a) && on_bottom(b))
    return straight(a, b);
  return arc(a, b);
}

const int s = 90;
ld ans = 1e18, theta = pi / 180.0;
point a, b;
vector<point> p;
vector<ld> ar;
vector<ld> dis, from, center = {0.0, pi};
vector<int> vis;

void iterate() {

  p = {a, b};
  ar = {-1e9, -1e9};
  dis.clear();
  from.clear();
  vis.clear();

  for (auto d : center)
    for (int i = -s; i <= s; i++) {
      p.emplace_back(point{r * cosl(d + i * theta),
        r * sinl(d + i * theta), 0});
      ar.emplace_back(d + i * theta);
    }
  int n = p.size();
  dis.resize(n);
  from.resize(n);
  vis.resize(n);
  for (int i = 1; i < n; i++) dis[i] = 1e18;
  for (int t = 0; t < n; t++) {
    int u = 0;
    ld d = 1e18;
    for (int i = 0; i < n; i++)
      if (!vis[i] && dis[i] < d) u = i, d = dis[i];
    vis[u] = 1;
    for (int v = 0; v < n; v++)
      if (d + distance(p[u], p[v]) < dis[v]) {
        from[v] = u;
        dis[v] = distance(p[u], p[v]) + d;
      }
  }
  ans = min(ans, dis[1]);
  center.clear();
  if (from[1] > 1) center.emplace_back(ar[from[1]]);
  if (from[from[1]] > 1)
    center.emplace_back(ar[from[from[1]]]);
  theta /= 20.0;
}

double cone_distance(
  double r, double h, point a, point b) {
  if (on_bottom(a) && on_bottom(b))
    return straight(a, b);
  else {
    for (int t = 1; t <= 10; t++) iterate();
    return ans;
  }
}