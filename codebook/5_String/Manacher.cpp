int man[2000006];
int manacher(string s) {
  string t;
  for (int i = 0; i < s.size(); i++) {
    if (i) t.push_back('$');
    t.push_back(s[i]);
  }
  int mx = 0, ans = 0;
  for (int i = 0; i < t.size(); i++) {
    man[i] = 1;
    man[i] = min(man[mx] + mx - i, man[2 * mx - i]);
    while (man[i] + i < t.size() && i - man[i] >= 0 &&
      t[i + man[i]] == t[i - man[i]])
      man[i]++;
    if (i + man[i] > mx + man[mx]) mx = i;
  }
  for (int i = 0; i < t.size(); i++)
    ans = max(ans, man[i] - 1);
  return ans;
}