// Prefix Doubling Algorithm
// Time complexity: O(NlogN)

struct SuffixArray {
  string a;
  int n, m;
  vector<int> SA, LCP, x, y, w, c;
  SuffixArray(string _a, int m = 256): a(_a + "#"), n(a.length()), m(m), SA(n), LCP(n), x(n), y(n), w(max(m, n)), c(n) {
    a.back() = 0;
    prefix_doubling();
    kasai();
    #define ROTATE(A) rotate(A.begin(), A.begin() + 1, A.end()); A.pop_back()
    ROTATE(SA); ROTATE(LCP);
    a.pop_back();
  }

  inline bool cmp(int i, int j, int l) { return y[i] == y[j] && y[(i + l) % n] == y[(j + l) % n]; }

  void sort() {
    for (int i = 0; i < m; ++i) w[i] = 0;
    for (int i = 0; i < n; ++i) ++w[x[y[i]]];
    for (int i = 1; i < m; ++i) w[i] += w[i - 1];
    for (int i = n - 1; i >= 0; --i) SA[--w[x[y[i]]]] = y[i];
  }

  void prefix_doubling() {
    for (int i = 0; i < n; ++i) x[i] = a[i], y[i] = i;
    sort();
    for (int i, p = 1, h = 1; h < n; h <<= 1, m = p) {
      for (i = 0; i < n; ++i) {
        y[i] = SA[i] - h;
        if (y[i] < 0) y[i] += n;
      }
      sort();
      for (swap(x, y), p = 1, i = 1, x[SA[0]] = 0; i < n; ++i) {
        x[SA[i]] = cmp(SA[i], SA[i - 1], h) ? (p - 1) : p++;
      }
    }
  }

  void kasai() {
    for (int i = 0; i < n; ++i) c[SA[i]] = i;
    for (int i = 0, k = 0, j; i < n; LCP[c[i++]] = k) {
      if (c[i] == n - 1) k = 0;
      else for (k ? --k: 0, j = SA[c[i] + 1]; i + k < n && j + k < n && a[i + k] == a[j + k]; ++k);
    }
  }
};
