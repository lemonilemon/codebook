#include "common.h"
int low[N], dfn[N], Time; // 1-base
vector<pii> G[N], edge;
vector<bool> is_bridge;

void init(int n) {
  Time = 0;
  for (int i = 1; i <= n; ++i)
    G[i].clear(), low[i] = dfn[i] = 0;
}

void add_edge(int a, int b) {
  G[a].emplace_back(pii(b, edge.size()));
  G[b].emplace_back(pii(a, edge.size()));
  edge.emplace_back(pii(a, b));
}

void dfs(int u, int f) {
  dfn[u] = low[u] = ++Time;
  for (auto i : G[u])
    if (!dfn[i.F])
      dfs(i.F, i.S), low[u] = min(low[u], low[i.F]);
    else if (i.S != f) low[u] = min(low[u], dfn[i.F]);
  if (low[u] == dfn[u] && f != -1) is_bridge[f] = 1;
}

void solve(int n) {
  is_bridge.resize(edge.size());
  for (int i = 1; i <= n; ++i)
    if (!dfn[i]) dfs(i, -1);
}
