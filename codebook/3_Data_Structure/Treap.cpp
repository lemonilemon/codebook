#include "include/common.h"
mt19937 rd(1);
#define sz(t) ((t) == 0 ? 0 : (t)->size)
struct Treap {
  int pri, size;
  Treap *l, *r;
  Treap(ll val = 0)
    : pri(rd()), size(1), l(0), r(0) {};
  void push();
  void pull() { size = 1 + sz(l) + sz(r); }
};
void spilt(int k, Treap *rt, Treap *&a, Treap *&b) {
  if (!rt) return a = b = 0, void();
  rt->push();
  int lsz = 1 + sz(rt->l);
  if (k >= lsz)
    a = rt, spilt(k - lsz, a->r, a->r, b), a->pull();
  else b = rt, spilt(k, b->l, a, b->l), b->pull();
}
Treap *merge(Treap *l, Treap *r) {
  if (!l) return r;
  if (!r) return l;
  if (l->pri < r->pri) {
    l->push(), l->r = merge(l->r, r), l->pull();
    return l;
  } else {
    r->push(), r->l = merge(l, r->l), r->pull();
    return r;
  }
}
