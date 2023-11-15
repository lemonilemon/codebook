#include "common.h"
template <typename T>
vector<T> BerlekampMassey(const vector<T> &output) {
  vector<T> d(output.size() + 1), me, he;
  for (int f = 0, i = 1; i <= output.size(); ++i) {
    for (int j = 0; j < me.size(); ++j)
      d[i] += output[i - j - 2] * me[j];
    if ((d[i] -= output[i - 1]) == 0) continue;
    if (me.empty()) {
      me.resize(f = i);
      continue;
    }
    vector<T> o(i - f - 1);
    T k = -d[i] / d[f];
    o.pb(-k);
    for (T x : he) o.emplace_back(x * k);
    o.resize(max(o.size(), me.size()));
    for (int j = 0; j < me.size(); ++j) o[j] += me[j];
    if (i - f + (int)he.size()) >= (int)me.size()) he = me, f = i;
    me = o;
  }
  return me;
}
