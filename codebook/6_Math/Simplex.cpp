#include "common.h"
// infeasible < 0, unbounded = inf, Ax <= b, max
struct simplex {
  const double inf = 1 / .0, eps = 1e-9;
  int n, m = 0;
  double A[205][205], B[205];
  void init(int _n) { n = _n; }
  void equation(vector<double> a, double b) {
    ++m;
    for (int i = 0; i < n; i++) A[m][i] = a[i];
    A[m][n + m] = 1, B[m] = b;
  }
  double solve(vector<double> c) {
    for (int i = 0; i < n; i++) A[0][i] = -c[i];
    A[0][n] = 1;
    int flag = 1;
    while (flag--)
      for (int i = 0; i <= n + m; i++)
        if (A[0][i] < -eps) {
          double bx = inf;
          int piv = -1;

          for (int j = 1; j <= m; j++)
            if (0 <= A[j][i] && B[j] / A[j][i] <= bx)
              piv = j, bx = B[j] / A[j][i];
          if (piv == -1) continue;
          if (bx == inf) return inf;
          flag = 1;
          for (int j = 0; j <= m; j++)
            if (j != piv) {
              for (int k = 0; k <= n + m; k++)
                if (k != i)
                  A[j][k] -=
                    A[piv][k] * A[j][i] / A[piv][i];
              B[j] -= B[piv] * A[j][i] / A[piv][i];
              A[j][i] = 0;
            }
        }
    for (int i = 0; i <= m; i++)
      if (B[i] < -eps) return -inf;
    return B[0] / A[0][n];
  }
} lp;
