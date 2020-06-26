#include <bits/stdc++.h>
#define X first
#define Y second
using namespace std;
using ll = long long;
using ii = pair<int, int>;

inline ll cross(const ii &a, const ii &b, const ii &c) {
  return 1LL * (b.X - a.X) * (c.Y - a.Y) - 1LL * (c.X - a.X) * (b.Y - a.Y);
}

void convexHull(const vector<ii> &A, vector<ii> &hull) {
  vector<ii> B(A);
  sort(B.begin(), B.end());
  B.resize(unique(B.begin(), B.end()) - B.begin());
  hull.clear();

  int n = B.size();
  for (int i = 0; i < n; ++i) {
    while (hull.size() > 1 && cross(hull[(int)hull.size() - 2], hull.back(), B[i]) <= 0) hull.pop_back();
    hull.push_back(B[i]);
  }
  size_t k = hull.size();
  for (int i = n - 1; i >= 0; --i) {
    while (hull.size() > k && cross(hull[(int)hull.size() - 2], hull.back(), B[i]) <= 0) hull.pop_back();
    hull.push_back(B[i]);
  }
  hull.pop_back();
}

// return double of area
ll calcArea(const vector<ii> &hull) {
  ll area = 0;
  int n = hull.size();
  for (int i = 0, j; i < n; ++i) {
    j = (i + 1) % n;
    area += 1LL * (hull[i].X - hull[j].X) * (hull[i].Y + hull[j].Y);
  }
  return abs(area);
}
