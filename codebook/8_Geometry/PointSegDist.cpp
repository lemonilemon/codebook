#include "GeometryDefaultFloat.h"
double PointSegDist(pdd q0, pdd q1, pdd p) {
  if (abs(q0 - q1) <= eps) return abs(q0 - p);
  if (dot(q1 - q0, p - q0) >= -eps && dot(q0 - q1, p - q1) >= -eps)
    return fabs(cross(q1 - q0, p - q0) / abs(q0 - q1));
  return min(abs(p - q0), abs(p - q1));
}
