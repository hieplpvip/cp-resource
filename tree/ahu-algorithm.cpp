/**
Check if two trees are isomorphic or not by rooting the trees at their centroids, then run AHU algorithm.

This code is the solution to https://codeforces.com/contest/1252/problem/F
**/

#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define emb emplace_back
#define pb push_back
using namespace std;
using vi = vector<int>;
const int N = 4005;

int n, child[N], root, par[2][N], labels[2][N];
vi adj[N], centroid[2], levels[2][N];

void input() {
  cin >> n;
  for (int i = 1; i < n; ++i) {
    int u, v; cin >> u >> v;
    adj[u].emb(v);
    adj[v].emb(u);
  }
}

int findCentroid(int tid, int u, int p, int nn) {
  int nChild = 1;
  bool ok = true;
  for (int v: adj[u]) {
    if (v != p && v != root) {
      int t = findCentroid(tid, v, u, nn);
      if (t > (nn >> 1)) ok = false;
      nChild += t;
    }
  }
  if (ok && (nn - nChild) <= (nn >> 1)) {
    centroid[tid].emb(u);
  }
  return nChild;
}

void countChild(int u, int p) {
  child[u] = 1;
  for (int v: adj[u]) {
    if (v != p) {
      countChild(v, u);
      child[u] += child[v];
    }
  }
}

int setLevels(int tid, int u, int p, int d) {
  par[tid][u] = p;
  levels[tid][d].emb(u);
  int mx = d;
  for (int v: adj[u]) {
    if (v != p && v != root)
      mx = max(mx, setLevels(tid, v, u, d + 1));
  }
  return mx;
}

bool checkISO(int lvl) {
  for (int curl = lvl; curl >= 0; --curl) {
    vector<pair<vi, int>> order[2];
    for (int id = 0; id < 2; ++id) {
      for (int u: levels[id][curl]) {
        order[id].pb({vi(), u});
        for (int v: adj[u]) {
          if (v != par[id][u] && v != root) {
            order[id].back().first.emb(labels[id][v]);
          }
        }
      }
    }

    if (order[0].size() != order[1].size()) return false;

    for (int i = 0; i < (int)order[0].size(); ++i) {
      sort(all(order[0][i].first));
      sort(all(order[1][i].first));
    }
    sort(all(order[0]));
    sort(all(order[1]));

    int labelid = 0;
    for (int i = 0; i < (int)order[0].size(); ++i) {
      if (order[0][i].first != order[1][i].first) return false;
      if (i && order[0][i].first != order[0][i - 1].first) ++labelid;
      labels[0][order[0][i].second] = labelid;
      labels[1][order[1][i].second] = labelid;
    }
  }
  return true;
}

bool check(int r1, int r2) {
  centroid[0].clear();
  centroid[1].clear();
  findCentroid(0, r1, -1, child[r1]);
  findCentroid(1, r2, -1, child[r2]);
  if (centroid[0].size() != centroid[1].size())
    return false;

  for (int c1: centroid[0]) {
    for (int c2: centroid[1]) {
      for (int i = 0; i <= n; ++i) {
        levels[0][i].clear();
        levels[1][i].clear();
        labels[0][i] = labels[1][i] = 0;
      }
      int d1 = setLevels(0, c1, -1, 0);
      int d2 = setLevels(1, c2, -1, 0);
      if (d1 != d2) continue;
      if (checkISO(d1)) return true;
    }
  }
  return false;
}

void solve() {
  findCentroid(0, 1, -1, n);
  vi cutting(centroid[0]);
  int res = -1;
  for (int r: cutting) {
    root = r;
    countChild(r, -1);
    bool ok = true;
    for (int i = 1; i < (int)adj[r].size(); ++i) {
      if (!check(adj[r][0], adj[r][i])) {
        ok = false;
        break;
      }
    }
    if (ok) res = max(res, (int)adj[r].size());
  }
  cout << res;
}

int main() {
  ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
  input();
  solve();
  return 0;
}