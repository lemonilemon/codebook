#include "include/common.h"
int KMP(string s, string t) {
  t = " "s + t; // consistency with ACa
  int ans = 0;
  vector<int> f(t.size(), 0);
  f[0] = -1;
  for (int i = 1, j = -1; i < (int)t.size(); i++) {
    while (j >= 0 && t[j + 1] != t[i]) j = f[j];
    f[i] = ++j;
  }
  for (int i = 0, j = 0; i < (int)s.size(); i++) {
    while (j >= 0 && t[j + 1] != s[i]) j = f[j];
    if (++j + 1 == (int)t.size()) ans++, j = f[j];
  }
  return ans;
}