#include "Fraction.cpp"
struct matrix { // m variables, n equations
  int n, m;
  fraction A[N][N + 1], sol[N];
  int solve() { //-1: inconsistent, >= 0: rank
    for (int i = 0; i < n; ++i) {
      int piv = 0;
      while (piv < m && !A[i][piv].n) ++piv;
      if (piv == m) continue;
      for (int j = 0; j < n; ++j) {
        if (i == j) continue;
        fraction tmp = -A[j][piv] / A[i][piv];
        for (int k = 0; k <= m; ++k)
          A[j][k] = tmp * A[i][k] + A[j][k];
      }
    }
    int rank = 0;
    for (int i = 0; i < n; ++i) {
      int piv = 0;
      while (piv < m && !A[i][piv].n) ++piv;
      if (piv == m && A[i][m].n) return -1;
      else if (piv < m)
        ++rank, sol[piv] = A[i][m] / A[i][piv];
    }
    return rank;
  }
};
