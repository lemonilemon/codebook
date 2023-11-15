#include "common.h"
#define sumS 500005
#define sigma 26
#define base 'a'
struct AhoCorasick {
  int ch[sumS][sigma] = {{}}, f[sumS] = {-1},
      tag[sumS], mv[sumS][sigma], jump[sumS],
      cnt[sumS];
  int idx = 0, t = -1;
  vector<int> E[sumS], q;
  pii o[sumS];
  int insert(string &s, int t) {
    int j = 0;
    for (int i = 0; i < (int)s.size(); i++) {
      if (!ch[j][s[i] - base])
        ch[j][s[i] - base] = ++idx;
      j = ch[j][s[i] - base];
    }
    tag[j] = 1;
    return j;
  }
  int next(int u, int c) {
    return u < 0 ? 0 : mv[u][c];
  }
  void dfs(int u) {
    o[u].F = ++t;
    for (auto v : E[u]) dfs(v);
    o[u].S = t;
  }
  void build() {
    int k = -1;
    q.emplace_back(0);
    while (++k < q.size()) {
      int u = q[k];
      for (int v = 0; v < sigma; v++) {
        if (ch[u][v]) {
          f[ch[u][v]] = next(f[u], v);
          q.emplace_back(ch[u][v]);
        }
        mv[u][v] =
          (ch[u][v] ? ch[u][v] : next(f[u], v));
      }
      if (u) jump[u] = (tag[f[u]] ? f[u] : jump[f[u]]);
    }
    reverse(q.begin(), q.end());
    for (int i = 1; i <= idx; i++)
      E[f[i]].emplace_back(i);
    dfs(0);
  }
  void match(string &s) {
    fill(cnt, cnt + idx + 1, 0);
    for (int i = 0, j = 0; i < (int)s.size(); i++)
      cnt[j = next(j, s[i] - base)]++;

    for (int i : q)
      if (f[i] > 0) cnt[f[i]] += cnt[i];
  }
} ac;