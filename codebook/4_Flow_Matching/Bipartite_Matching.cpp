#include "include/common.h"
struct BipartiteMatching { // 0-base
  int l, r;
  int mp[N], mq[N];
  int dis[N], cur[N];
  vector<int> G[N];
  bool dfs(int u) {
    for (int &i = cur[u]; i < G[u].size(); ++i) {
      int e = G[u][i];
      if (!~mq[e] ||
        (dis[mq[e]] == dis[u] + 1 && dfs(mq[e])))
        return mp[mq[e] = u] = e, 1;
    }
    dis[u] = -1;
    return 0;
  }
  bool bfs() {
    int rt = 0;
    queue<int> q;
    fill_n(dis, l, -1);
    for (int i = 0; i < l; ++i)
      if (!~mp[i]) q.push(i), dis[i] = 0;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int e : G[u])
        if (!~mq[e]) rt = 1;
        else if (!~dis[mq[e]]) {
          q.push(mq[e]);
          dis[mq[e]] = dis[u] + 1;
        }
    }
    return rt;
  }
  int matching() {
    int rt = 0;
    fill_n(mp, l, -1);
    fill_n(mq, r, -1);
    while (bfs()) {
      fill_n(cur, l, 0);
      for (int i = 0; i < l; ++i)
        if (!~mp[i] && dfs(i)) ++rt;
    }
    return rt;
  }
  void add_edge(int s, int t) { G[s].emplace_back(t); }
  void init(int _l, int _r) {
    l = _l, r = _r;
    for (int i = 0; i < l; ++i) G[i].clear();
  }
};
