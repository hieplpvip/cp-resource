vector<int> prefix_func(string s) {
  int n = (int)s.length();
  vector<int> pi(n);
  for (int i = 1, j = 0; i < n; ++i) {
    while (j > 0 && s[i] != s[j])
      j = pi[j - 1];
    if (s[i] == s[j])
      ++j;
    pi[i] = j;
  }
  return pi;
}
