/**
Minkowski sum for checking if two polygons intersect
Time complexity: O(m + n)

Tested on https://vn.spoj.com/problems/NKLAND/
**/
#include <bits/stdc++.h>
#define X first
#define Y second
using namespace std;
using ll = long long;
using ii = pair<ll, ll>;
const ii ORIGIN = {0, 0};

inline ii operator +(const ii &a, const ii &b) {
  return {a.X + b.X, a.Y + b.Y};
}

inline ii operator -(const ii &a, const ii &b) {
  return {a.X - b.X, a.Y - b.Y};
}

inline ll cross(const ii &a, const ii &b) {
  return a.X * b.Y - b.X * a.Y;
}

int m, n;
vector<ii> A, B, C;

void rotate(vector<ii> &A) {
  int id = -1;
  ll minX = 1e18, minY = 1e18;
  for (size_t i = 0; i < A.size(); ++i) {
    if (A[i].X < minX || (A[i].X == minX && A[i].Y < minY)) {
      id = i;
      minX = A[i].X;
      minY = A[i].Y;
    }
  }
  rotate(A.begin(), A.begin() + id, A.end());
}

void minkowski() {
  C.push_back(A[0] + B[0]);
  int i = 0, j = 0;
  while (i < m || j < n) {
    ii last = C.back();
    ii v1 = A[(i + 1) % m] - A[i];
    ii v2 = B[(j + 1) % n] - B[j];
    if (j == n || (i < m && cross(v1, v2) >= 0)) {
      C.push_back(last + v1);
      ++i;
    } else {
      C.push_back(last + v2);
      ++j;
    }
  }
  C.pop_back();
}

void solve() {
  A.clear(); B.clear(); C.clear();
  cin >> m;
  for (int i = 1, x, y; i <= m; ++i) {
    cin >> x >> y;
    A.emplace_back(x, y);
  }
  cin >> n;
  for (int i = 1, x, y; i <= n; ++i) {
    cin >> x >> y;
    B.emplace_back(-x, -y);
  }
  rotate(A); rotate(B);
  minkowski();
  n = C.size();
  bool cut = true;
  for (int i = 0; i < n; ++i) {
    cut &= cross(C[(i + 1) % n] - C[i], ORIGIN - C[i]) > 0;
  }
  cout << (cut ? "YES\n" : "NO\n");
}

int main() {
  ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
  int t; cin >> t;
  while (t--) solve();
  return 0;
}
