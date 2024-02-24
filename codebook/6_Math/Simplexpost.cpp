// basic define and includes
#include <bits/stdc++.h>
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pdd pair<double, double>
#define ll long long
#define ld long double
#define i128 __int128
#define F first
#define S second
#define all(x) x.begin(), x.end()
using namespace std;

const ll mod = 998'244'353;

// infeasible < 0, unbounded = inf, Ax <= b, max
struct simplex {
  const double inf = 1 / .0, eps = 1e-9;
  int n, m = 0;
  double A[2005][2005], B[2005];
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
            if (B[j] / A[j][i] <= bx)
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
    // for (int i = 0; i <= m; i++)
    //   if (B[i] < -eps) return -inf;
    return B[0] / A[0][n];
  }
} lp;

signed main() {
  int N, K, idx = 0;
  cin >> N >> K;
  vector<int> v(N);
  vector<int> x(N);
  vector w(N, vector<int>(N));
  for (auto &p : v) cin >> p;

  for (int i = 0; i < N; i++) x[i] = idx++;
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++) w[i][j] = idx++;

  vector<double> zero(idx, 0);
  lp.init(idx);
  for (int i = 0; i < N; i++) {
    vector<double> r = zero;
    r[x[i]] = 1;
    lp.equation(r, 1);
    r[x[i]] = -1;
    lp.equation(r, 0);
  }
  {
    vector<double> r = zero;
    for (int i = 0; i < N; i++) r[x[i]] = 1;
    lp.equation(r, K);
  }
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++) {
      vector<double> r = zero;
      r[w[i][j]] = -1;
      lp.equation(r, 0);
      r[w[i][j]] = 1;
      r[x[j]] = -1;
      lp.equation(r, 0);
    }
  for (int j = 0; j < N; j++) {
    vector<double> r = zero;
    for (int i = 0; i < N; i++) r[w[i][j]] = -1;
    lp.equation(r, -1);
  }
  vector<double> r = zero;
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      r[w[i][j]] = -abs(v[i] - v[j]);
  cout << -lp.solve(r);
}