#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;

int n, m, Time, num[N], low[N];
stack<int> stk;
vector<int> adj[N];

void dfs(int u) {
  num[u] = low[u] = ++Time;
  stk.emplace(u);
  for (int &v: adj[u]) {
    if (num[v]) {
      low[u] = min(low[u], num[v]);
    } else {
      dfs(v);
      low[u] = min(low[u], low[v]);
    }
  }
  if (low[u] == num[u]) {
    int v;
    do {
      v = stk.top(); stk.pop();
      num[v] = low[v] = 1e9;
      cout << v << " ";
    } while (v != u);
    cout << "\n";
  }
}

int main() {
  ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
  cin >> n >> m;
  for (int i = 1, u, v; i <= m; ++i) {
    cin >> u >> v;
    adj[u].emplace_back(v);
  }
  for (int i = 1; i <= n; ++i) {
    if (!num[i]) dfs(i);
  }
  return 0;
}
