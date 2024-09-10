#include "include/common.h"
auto cmp = [](int x, int y) { return x < y; };
std::set<int, decltype(cmp)> st(cmp);