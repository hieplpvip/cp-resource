#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;

int n, m, Time, num[N], low[N], P = 0, Q = 0;
bool isCut[N];
unordered_map<int, int> adj[N];
vector<pair<int, int>> bridges;

void dfs(int u, int p) {
  int nChild = 0;
  num[u] = low[u] = ++Time;
  for (auto &e: adj[u]) {
    int v = e.first;
    if (v == p) continue;
    ++nChild;
    if (num[v]) {
      low[u] = min(low[u], num[v]);
    } else {
      dfs(v, u);
      low[u] = min(low[u], low[v]);
      if ((p == -1 && nChild >= 2) || (p != -1 && low[v] >= num[u])) {
        if (!isCut[u]) ++Q;
        isCut[u] = true;
      }
      if (low[v] >= num[v] && e.second == 1) {
        bridges.emplace_back(u, v);
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
  cin >> n >> m;
  for (int i = 1, u, v; i <= m; ++i) {
    cin >> u >> v;
    ++adj[u][v];
    ++adj[v][u];
  }
  for (int i = 1; i <= n; ++i) {
    if (!num[i]) dfs(i, -1);
  }

  P = bridges.size();
  cout << P << " " << Q << "\n";
  for (auto &b: bridges) {
    cout << b.first << " " << b.second << "\n";
  }
  for (int i = 1; i <= n; ++i) {
    if (isCut[i]) cout << i << "\n";
  }
  return 0;
}
