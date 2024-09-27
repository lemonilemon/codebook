#include "include/common.h"
struct SuffixArray {
#define add(x, k) (x + k + n) % n
  vector<int> sa, cnt, rk, tmp, lcp;
  // sa: order, rk[i]: pos of s[i..],
  // lcp[i]: LCP of sa[i], sa[i-1]
  void SA(string s) { // remember to append '\1'
    int n = (int)s.size();
    sa.resize(n), cnt.resize(n);
    rk.resize(n), tmp.resize(n);
    iota(all(sa), 0);
    sort(all(sa),
      [&](int i, int j) { return s[i] < s[j]; });
    rk[0] = 0;
    for (int i = 1; i < n; i++)
      rk[sa[i]] =
        rk[sa[i - 1]] + (s[sa[i - 1]] != s[sa[i]]);
    for (int k = 1; k <= n; k <<= 1) {
      fill(all(cnt), 0);
      for (int i = 0; i < n; i++)
        cnt[rk[add(sa[i], -k)]]++;
      for (int i = 1; i < n; i++) cnt[i] += cnt[i - 1];
      for (int i = n - 1; i >= 0; i--)
        tmp[--cnt[rk[add(sa[i], -k)]]] =
          add(sa[i], -k);
      sa.swap(tmp);
      tmp[sa[0]] = 0;
      for (int i = 1; i < n; i++)
        tmp[sa[i]] = tmp[sa[i - 1]] +
          (rk[sa[i - 1]] != rk[sa[i]] ||
            rk[add(sa[i - 1], k)] !=
              rk[add(sa[i], k)]);
      rk.swap(tmp);
    }
  }
  void LCP(string s) {
    int n = (int)s.size(), k = 0;
    lcp.resize(n);
    for (int i = 0; i < n; i++)
      if (rk[i] == 0) lcp[rk[i]] = 0;
      else {
        if (k) k--;
        int j = sa[rk[i] - 1];
        while (
          max(i, j) + k < n && s[i + k] == s[j + k])
          k++;
        lcp[rk[i]] = k;
      }
  }
};