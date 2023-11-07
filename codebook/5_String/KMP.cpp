#include "common.h"
int KMP(string s, string t) {
  int n = t.size(), ans = 0;
  vector<int> f(t.size(), 0);
  f[0] = -1;
  for (int i = 1, j = -1; i < t.size(); i++) {
    while (j >= 0)
      if (t[j + 1] == t[i]) break;
      else j = f[j];
    f[i] = ++j;
  }
  for (int i = 0, j = 0; i < s.size(); i++) {
    while (j >= 0)
      if (t[j + 1] == s[i]) break;
      else j = f[j];
    if (++j + 1 == t.size()) ans++, j = f[j];
  }
  return ans;
}