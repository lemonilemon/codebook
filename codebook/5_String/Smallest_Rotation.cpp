#include "include/common.h"
int mincyc(string s) {
  int n = (int)s.size();
  s = s + s;
  int i = 0, ans = 0;
  while (i < n) {
    ans = i;
    int j = i + 1, k = i;
    while (j < 2 * n && s[j] >= s[k]) {
      k = (s[j] > s[k] ? i : k + 1);
      ++j;
    }
    while (i <= k) i += j - k;
  }
  return ans;
}
