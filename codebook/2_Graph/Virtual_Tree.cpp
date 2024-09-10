#include "include/common.h"
// requires DFS io, lca, is_child
vector<int> tre[N];
bool cmp(int a, int b){ return in[a] < in[b]; }
void add_edge(int a, int b){
  tre[a].emplace_back(b);
  tre[b].emplace_back(a);
}
void virtual_tree(vector<int> arr, int k){
  vector<int> sta;
  sort(arr.begin(), arr.end(), cmp);
  for (int i = 1; i < k; i++)
    arr.emplace_back(lca(arr[i], arr[i - 1]));
  sort(arr.begin(), arr.end(), cmp);
  arr.resize(unique(arr.begin(), arr.end()) - arr.begin());
  for (auto i : arr){
    while (!sta.empty() && !is_child(sta.back(), i)) sta.pop_back();
    if (!sta.empty()) add_edge(sta.back(), i);
    sta.push_back(i);
  }
}