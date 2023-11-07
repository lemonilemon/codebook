#define poly vector<base>

poly inv(poly A) {
  A.resize(1 << (__lg(A.size() - 1) + 1));
  poly B = {inverse(A[0])};
  for (int n = 1; n < A.size(); n += n) {
    poly pA(A.begin(), A.begin() + 2 * n);
    calcrev(4 * n);
    calcW(4 * n);
    pA.resize(4 * n);
    B.resize(4 * n);
    pA = NTT(pA, 0);
    B = NTT(B, 0);
    for (int i = 0; i < 4 * n; i++)
      B[i] =
        ((B[i] * 2 - pA[i] * B[i] % mod * B[i]) % mod +
          mod) %
        mod;
    B = NTT(B, 1);
    B.resize(2 * n);
  }
  return B;
}

pair<poly, poly> div(poly A, poly B) {
  if (A.size() < B.size()) return make_pair(poly(), A);
  int n = A.size(), m = B.size();
  poly revA = A, invrevB = B;
  reverse(revA.begin(), revA.end());
  reverse(invrevB.begin(), invrevB.end());
  revA.resize(n - m + 1);
  invrevB.resize(n - m + 1);
  invrevB = inv(invrevB);

  poly Q = mul(revA, invrevB);
  Q.resize(n - m + 1);
  reverse(Q.begin(), Q.end());
  poly R = mul(Q, B);
  R.resize(m - 1);
  for (int i = 0; i < m - 1; i++)
    R[i] = (A[i] - R[i] + mod) % mod;
  return make_pair(Q, R);
}

ll fast_kitamasa(ll k, poly A, poly C) {
  int n = A.size();
  C.emplace_back(mod - 1);
  poly Q, R = {0, 1}, F = {1};
  R = div(R, C);
  while (k) {
    if (k & 1) F = div(mul(F, R), C);
    R = div(mul(R, R), C);
    k >>= 1;
  }
  ll ans = 0;
  for (int i = 0; i < F.size(); i++)
    ans = (ans + A[i] * F[i]) % mod;
  return ans;
}

vector<ll> fpow(vector<ll> f, ll p, ll m) {
  int b = 0;
  while (b < f.size() && f[b] == 0) b++;
  f = vector<ll>(f.begin() + b, f.end());
  int n = f.size();
  f.emplace_back(0);
  vector<ll> q(min(m, b * p), 0);
  q.emplace_back(fpow(f[0], p));
  for (int k = 0; q.size() < m; k++) {
    ll res = 0;
    for (int i = 0; i < min(n, k + 1); i++)
      res = (res +
              p * (i + 1) % mod * f[i + 1] % mod *
                q[k - i + b * p]) %
        mod;
    for (int i = 1; i < min(n, k + 1); i++)
      res = (res -
              f[i] * (k - i + 1) % mod *
                q[k - i + 1 + b * p]) %
        mod;
    res = (res < 0 ? res + mod : res) *
      inv(f[0] * (k + 1) % mod) % mod;
    q.emplace_back(res);
  }
  return q;
}