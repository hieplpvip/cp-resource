/** Minimum Hull
    Add line in decreasing slope, query in increasing x
**/
template<typename T = long long>
struct MinHull {
  struct Line {
    T a, b;
    Line(T a, T b): a(a), b(b) {}
    T calc(T x) { return a * x + b; }
  };

  vector<Line> dq;
  size_t seen;
  bool overlap(const Line &p1, const Line &p2, const Line &p3) {
    return 1.0 * (p3.b - p1.b) / (p1.a - p3.a) <= 1.0 * (p2.b - p1.b) / (p1.a - p2.a);
  }
  void addLine(T a, T b) {
    Line newLine(a, b);
    while (dq.size() > seen + 1 && overlap(dq[(int)dq.size() - 2], dq.back(), newLine))
      dq.pop_back();
    dq.push_back(newLine);
  }
  T query(T x) {
    while (seen + 1 < dq.size() && dq[seen].calc(x) >= dq[seen + 1].calc(x))
      ++seen;
    return dq[seen].calc(x);
  }
};

/** Maximum Hull
    Add line in increasing slope, query in increasing x
**/
template<typename T = long long>
struct MaxHull {
  struct Line {
    T a, b;
    Line(T a, T b): a(a), b(b) {}
    T calc(T x) { return a * x + b; }
  };

  vector<Line> dq;
  size_t seen;
  bool overlap(const Line &p1, const Line &p2, const Line &p3) {
    return 1.0 * (p3.b - p1.b) / (p1.a - p3.a) <= 1.0 * (p2.b - p1.b) / (p1.a - p2.a);
  }
  void addLine(T a, T b) {
    Line newLine(a, b);
    while (dq.size() > seen + 1 && overlap(dq[(int)dq.size() - 2], dq.back(), newLine))
      dq.pop_back();
    dq.push_back(newLine);
  }
  T query(T x) {
    while (seen + 1 < dq.size() && dq[seen].calc(x) <= dq[seen + 1].calc(x))
      ++seen;
    return dq[seen].calc(x);
  }
};

/**
Fully dynamic maximum convex hull
Add lines with -a and -b and return -ans to convert it to minimum convex hull.
Source: https://github.com/kth-competitive-programming/kactl/blob/master/content/data-structures/LineContainer.h
**/
struct Line {
  mutable ll k, m, p;
  bool operator<(const Line& o) const { return k < o.k; }
  bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
  // (for doubles, use inf = 1/.0, div(a,b) = a/b)
  const ll inf = LLONG_MAX;
  ll div(ll a, ll b) { // floored division
    return a / b - ((a ^ b) < 0 && a % b); }
  bool isect(iterator x, iterator y) {
    if (y == end()) { x->p = inf; return false; }
    if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
    else x->p = div(y->m - x->m, x->k - y->k);
    return x->p >= y->p;
  }
  void add(ll a, ll b) {
    auto z = insert({a, b, 0}), y = z++, x = y;
    while (isect(y, z)) z = erase(z);
    if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
    while ((y = x) != begin() && (--x)->p >= y->p)
      isect(x, erase(y));
  }
  ll query(ll x) {
    assert(!empty());
    auto l = *lower_bound(x);
    return l.k * x + l.m;
  }
};