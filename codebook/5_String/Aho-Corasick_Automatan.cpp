#define sumS 500005
#define sigma 26
#define base 'a'
struct AhoCorasick {
  int ch[sumS][sigma] = {{}}, f[sumS] = {-1},
      tag[sumS], mv[sumS][sigma], jump[sumS],
      cnt[sumS];
  int idx = 0;
  int insert(string &s) {
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
  void build() {
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int v = 0; v < sigma; v++) {
        if (ch[u][v]) {
          f[ch[u][v]] = next(f[u], v);
          q.push(ch[u][v]);
        }
        mv[u][v] =
          (ch[u][v] ? ch[u][v] : next(f[u], v));
      }
      if (u) jump[u] = (tag[f[u]] ? f[u] : jump[f[u]]);
    }
  }
  void match(string &s) {
    for (int i = 0; i <= idx; i++) cnt[i] = 0;
    for (int i = 0, j = 0; i < (int)s.size(); i++) {
      j = next(j, s[i] - base);
      cnt[j]++;
    }
    vector<int> v;
    v.emplace_back(0);
    for (int i = 0; i < (int)v.size(); i++)
      for (int j = 0; j < sigma; j++)
        if (ch[v[i]][j]) v.emplace_back(ch[v[i]][j]);
    reverse(v.begin(), v.end());
    for (int i : v)
      if (f[i] > 0) cnt[f[i]] += cnt[i];
  }
} ac;