#include "Default_code.cpp"
void hull(vector<pll> &dots) { // n=1 => ans = {}
  sort(dots.begin(), dots.end());
  vector<pll> ans(1, dots[0]);
  for (int ct = 0; ct < 2; ++ct, reverse(all(dots)))
    for (int i = 1, t = ans.size(); i < dots.size(); ans.emplace_back(dots[i++]))
      while (ans.size() > t && ori(ans.end()[-2], ans.back(), dots[i]) <= 0) 
        ans.pop_back();
  ans.pop_back(), ans.swap(dots);
}
