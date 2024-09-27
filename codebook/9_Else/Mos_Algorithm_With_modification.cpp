#include "include/common.h"
// Mo's Algorithm With modification
// Block: N^{2/3}, Complexity: N^{5/3}
struct Query {
  static const int blk = 2000;
  int L, R, LBid, RBid, T;
  Query(int l, int r, int t):
    L(l), R(r), LBid(l / blk), RBid(r / blk), T(t) {}
  bool operator<(const Query &q) const {
    if (LBid != q.LBid) return LBid < q.LBid;
    if (RBid != q.RBid) return RBid < q.RBid;
    return T < q.T;
  }
};

void solve(vector<Query> query) {
  sort(all(query));
  int L=0, R=0, T=-1;
  for (auto q : query) { // TODO: fill in
    // while (T < q.T) addTime(L, R, ++T); 
    // while (T > q.T) subTime(L, R, T--);
    // while (R < q.R) add(arr[++R]); 
    // while (L > q.L) add(arr[--L]); 
    // while (R > q.R) sub(arr[R--]);
    // while (L < q.L) sub(arr[L++]); 
    // answer query
  }
}
