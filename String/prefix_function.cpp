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

void compute_automaton(string s, vector<vector<int>> &aut) {
  int n = s.length();
  vector<int> pi = prefix_func(s);
  aut.assign(n, vector<int>(26));
  for (int i = 0; i < n; ++i) {
    for (int c = 0; c < 26; ++c) {
      if (i > 0 && s[i] != 'a' + c) {
        aut[i][c] = aut[pi[i - 1]][c];
      } else {
        aut[i][c] = i + (s[i] == 'a' + c);
      }
    }
  }
}
