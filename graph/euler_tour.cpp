/**
The Algorithm below is known as Heirholzer's Algorithm. It runs in O(V + E).

The algorithm finds an Euler Tour or an Euler Circuit depending on whether the
graph has 0 or 2 nodes with odd degree.

Sample Input:
8 9
1 2
1 3
4 2
4 3
4 5
4 6
5 7
6 8
7 8

Sample Output:
1 3 4 6 8 7 5 4 2 1
**/

#include <bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;
const int N = 1e5 + 5;

int n, m, deg[N], seen[N];
bool rem[N];
vector<ii> adj[N];

int main() {
  ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
  cin >> n >> m;
  for (int i = 1, u, v; i <= m; ++i) {
    cin >> u >> v;
    adj[u].emplace_back(v, i);
    adj[v].emplace_back(u, i);
    ++deg[u]; ++deg[v];
  }

  int start = 1;
  for (int i = 1; i <= n; ++i) {
    if (deg[i] & 1) start = i;
  }

  stack<int> st;
  st.emplace(start);
  while (!st.empty()) {
    int u = st.top();
    while (seen[u] < (int)adj[u].size()) {
      auto &e = adj[u][seen[u]++];
      if (rem[e.second]) continue;
      rem[e.second] = true;
      u = e.first;
      st.emplace(u);
    }
    cout << st.top() << " ";
    st.pop();
  }
  return 0;
}