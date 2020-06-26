#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;

int n, m, Time, num[N], low[N], comp[N], cntComp;
stack<int> stk;
vector<int> adj[N];

void dfs(int u, int p) {
  num[u] = low[u] = ++Time;
  for (int &v: adj[u]) {
    if (v == p) continue;
    if (num[v]) {
      low[u] = min(low[u], num[v]);
    } else {
      stk.emplace(u);
      dfs(v, u);
      low[u] = min(low[u], low[v]);
      if (low[v] >= num[u]) {
        cout << "Component " << (++cntComp) << ": ";
        int x;
        do {
          x = stk.top(); stk.pop();
          if (comp[x] != cntComp) cout << x << " ";
          comp[x] = cntComp;
        } while (x != u);
        cout << "\n";
      }
    }
  }
  stk.emplace(u);
}

int main() {
  ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
  cin >> n >> m;
  for (int i = 1, u, v; i <= m; ++i) {
    cin >> u >> v;
    adj[u].emplace_back(v);
    adj[v].emplace_back(u);
  }
  for (int i = 1; i <= n; ++i) {
    if (!num[i]) dfs(i, -1);
  }
  for (int i = 1; i <= n; ++i) {
    if (!comp[i]) cout << "Component " << (++cntComp) << ": " << i << "\n";
  }
  return 0;
}
