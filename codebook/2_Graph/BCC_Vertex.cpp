#include "common.h"
int n, m, dfn[N], low[N], is_cut[N], nbcc = 0, t = 0;
vector<int> g[N], bcc[N], G[2 * N];
stack<int> st;
void tarjan(int p, int lp) {
  dfn[p] = low[p] = ++t;
  st.push(p);
  for (auto i : g[p]) {
    if (!dfn[i]) {
      tarjan(i, p);
      low[p] = min(low[p], low[i]);
      if (dfn[p] <= low[i]) {
        nbcc++;
        is_cut[p] = 1;
        for (int x = 0; x != i; st.pop()) {
          x = st.top();
          bcc[nbcc].push_back(x);
        }
        bcc[nbcc].push_back(p);
      }
    } else low[p] = min(low[p], dfn[i]);
  }
}
void build() { // [n+1,n+nbcc] cycle, [1,n] vertex
  for (int i = 1; i <= nbcc; i++) {
    for (auto j : bcc[i]) {
      G[i + n].push_back(j);
      G[j].push_back(i + n);
    }
  }
}