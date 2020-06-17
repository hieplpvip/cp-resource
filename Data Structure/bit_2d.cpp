// how to use? init first
// run once through all the query, do get/update as usual but with real = false
// run normalize then get and update with real = true to get result
const int N = 2e5 + 5;
template<typename T>
struct BIT2D {
  int n;
  vector<int> nodes[N];
  vector<T> F[N];

  void init(int _n) {
    n = _n;
  }

  void normalize() {
    for (int x = 1; x <= n; ++x) {
      sort(nodes[x].begin(), nodes[x].end());
      nodes[x].resize(unique(nodes[x].begin(), nodes[x].end()) - nodes[x].begin());
      F[x].resize(nodes[x].size() + 3);
    }
  }

  void update(int x, int y, T val, bool real = true) {
    if (!real) {
      for (; x <= n; x += x & -x) nodes[x].emplace_back(y);
      return;
    }

    int orig_y = y;
    for (; x <= n; x += x & -x) {
      for (y = lower_bound(nodes[x].begin(), nodes[x].end(), orig_y) - nodes[x].begin() + 1; y <= (int)nodes[x].size(); y += y & -y) {
        F[x][y] += val;
      }
    }
  }

  T get(int x, int y, bool real = true) {
    if (!real) {
      for (; x > 0; x -= x & -x) nodes[x].emplace_back(y);
      return 0;
    }

    T res = 0;
    int orig_y = y;
    for (; x > 0; x -= x & -x) {
      for (y = lower_bound(nodes[x].begin(), nodes[x].end(), orig_y) - nodes[x].begin() + 1; y > 0; y -= y & -y) {
        res += F[x][y];
      }
    }
    return res;
  }
};
