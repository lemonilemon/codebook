vector<int> sa, cnt, rk, tmp, lcp;
void SA(string s) {
  int n = s.size();
  sa.resize(n), cnt.resize(n), rk.resize(n),
    tmp.resize(n);
  iota(sa.begin(), sa.end(), 0);
  sort(sa.begin(), sa.end(),
    [&](int i, int j) { return s[i] < s[j]; });
  rk[0] = 0;
  for (int i = 1; i < n; i++)
    rk[sa[i]] =
      rk[sa[i - 1]] + (s[sa[i - 1]] != s[sa[i]]);
  for (int k = 1; k <= n; k <<= 1) {
    fill(cnt.begin(), cnt.end(), 0);
    for (int i = 0; i < n; i++)
      cnt[rk[(sa[i] - k + n) % n]]++;
    for (int i = 1; i < n; i++) cnt[i] += cnt[i - 1];
    for (int i = n - 1; i >= 0; i--)
      tmp[--cnt[rk[(sa[i] - k + n) % n]]] =
        (sa[i] - k + n) % n;
    sa.swap(tmp);
    tmp[sa[0]] = 0;
    for (int i = 1; i < n; i++)
      tmp[sa[i]] = tmp[sa[i - 1]] +
        (rk[sa[i - 1]] != rk[sa[i]] ||
          rk[(sa[i - 1] + k) % n] !=
            rk[(sa[i] + k) % n]);
    rk.swap(tmp);
  }
}

void LCP(string s) {
  int n = s.size(), k = 0;
  lcp.resize(n);
  for (int i = 0; i < n; i++)
    if (rk[i] == 0) lcp[rk[i]] = 0;
    else {
      if (k) k--;
      int j = sa[rk[i] - 1];
      while (
        i + k < n && j + k < n && s[i + k] == s[j + k])
        k++;
      lcp[rk[i]] = k;
    }
}