#include "include/common.h"
void all_lcs(string s, string t) { // 0-base
  vector<int> h((int)t.size());
  iota(all(h), 0);
  for (int a = 0; a < (int)s.size(); ++a) {
    int v = -1;
    for (int c = 0; c < (int)t.size(); ++c)
      if (s[a] == t[c] || h[c] < v)
        swap(h[c], v);
    // LCS(s[0, a], t[b, c]) = 
    // c - b + 1 - sum([h[i] >= b] | i <= c)
    // h[i] might become -1 !!
  }
}
