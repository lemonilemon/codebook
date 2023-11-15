#include "Default_code.cpp"
pdd circenter(
  pdd p0, pdd p1, pdd p2) { // radius = abs(center)
  p1 = p1 - p0, p2 = p2 - p0;
  double x1 = p1.F, y1 = p1.S, x2 = p2.F, y2 = p2.S;
  double m = 2. * (x1 * y2 - y1 * x2);
  pdd center = pdd((x1 * x1 * y2 - x2 * x2 * y1 +
                     y1 * y2 * (y1 - y2)) / m,
    (x1 * x2 * (x2 - x1) - y1 * y1 * x2 +
      x1 * y2 * y2) / m);
  return center + p0;
}
pdd incenter(
  pdd p1, pdd p2, pdd p3) { // radius = area / s * 2
  double a = abs(p2 - p3), b = abs(p1 - p3),
         c = abs(p1 - p2);
  double s = a + b + c;
  return (a * p1 + b * p2 + c * p3) / s;
}
pdd masscenter(pdd p1, pdd p2, pdd p3) {
  return (p1 + p2 + p3) / 3;
}
pdd orthcenter(pdd p1, pdd p2, pdd p3) {
  return masscenter(p1, p2, p3) * 3 -
    circenter(p1, p2, p3) * 2;
}
