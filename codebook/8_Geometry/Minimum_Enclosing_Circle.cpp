#include "GeometryDefaultFloat.h"
#include "Heart.cpp"
pdd Minimum_Enclosing_Circle(vector<pdd> dots, double &r) {
  pdd cent;
  random_shuffle(all(dots));
  cent = dots[0], r = 0;
  for (int i = 1; i < (int)dots.size(); ++i) 
    if (abs(dots[i] - cent) > r) {
      cent = dots[i], r = 0;
      for (int j = 0; j < i; ++j)
        if (abs(dots[j] - cent) > r) {
          cent = (dots[i] + dots[j]) / 2;
          r = abs(dots[i] - cent);
          for(int k = 0; k < j; ++k)
            if(abs(dots[k] - cent) > r)
              cent = excenter(dots[i], dots[j], dots[k]),
              r = abs(cent - dots[i]);
        }
    }
  return cent;
}
