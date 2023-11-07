ll floorsum(ll A, ll B, ll C, ll N) {
  if (A == 0) return (N + 1) * (B / C);
  if (A > C || B > C)
    return (N + 1) * (B / C) +
      N * (N + 1) / 2 * (A / C) +
      floorsum(A % C, B % C, C, N);
  ll M = (A * N + B) / C;
  return N * M - floorsum(C, C - B - 1, A, M - 1);
} // \sum^{n}_0 floor((ai + b) / m)
