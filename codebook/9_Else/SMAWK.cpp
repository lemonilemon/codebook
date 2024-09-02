#include "include/common.h"
int opt[N];
ll A(int x, int y); // target func
void smawk(vector<int> &r, vector<int> &c);
void interpolate(vector<int> &r, vector<int> &c) {
  int n = (int)r.size();
  vector<int> er;
  for (int i = 1; i < n; i += 2) er.emplace_back(r[i]);
  smawk(er, c);
  for (int i = 0, j = 0; j < c.size(); j++) {
    if (A(r[i], c[j]) < A(r[i], opt[r[i]]))
      opt[r[i]] = c[j];
    if (i + 2 < n && c[j] == opt[r[i + 1]])
      j--, i += 2;
  }
}
void reduce(vector<int> &r, vector<int> &c) {
  int n = (int)r.size();
  vector<int> nc;
  for (int i : c) {
    int j = (int)nc.size();
    while (
      j && A(r[j - 1], nc[j - 1]) > A(r[j - 1], i))
      nc.pop_back(), j--;
    if (nc.size() < n) nc.emplace_back(i);
  }
  smawk(r, nc);
}
void smawk(vector<int> &r, vector<int> &c) {
  if (r.size() == 1 && c.size() == 1) opt[r[0]] = c[0];
  else if (r.size() >= c.size()) interpolate(r, c);
  else reduce(r, c);
}