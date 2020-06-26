/**
Hopcroft-Karp algorithm to find maximum cardinality matching on bipartite graph
Time complexity: O(E * sqrt(V))

Tested on:
- https://vn.spoj.com/problems/FMATCH/
- https://www.spoj.com/problems/MATCHING/

How to use:
```
  int a, b, m;
  scanf("%d %d %d", &a, &b, &m);
  HopcroftKarp match(max(a, b));
  for (int i = 1, u, v; i <= m; ++i) {
    scanf("%d %d", &u, &v);
    match.addEdge(u, v);
  }
  printf("%d", match.calc());
```
**/

struct HopcroftKarp {
  const int INF = 1e9;
  int n;
  vector<int> d, matchL, matchR;
  vector<vector<int>> adj;
  HopcroftKarp(int n): n(n), d(n + 1), matchL(n + 1), matchR(n + 1), adj(n + 1) {}

  // u is left vertex, v is right vertex
  void addEdge(int u, int v) {
    adj[u].emplace_back(v);
  }

  bool bfs() {
    queue<int> q;
    for (int u = 1; u <= n; ++u) {
      if (!matchL[u]) d[u] = 0, q.emplace(u);
      else d[u] = INF;
    }
    d[0] = INF;
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (int &v: adj[u]) {
        if (d[matchR[v]] == INF) {
          d[matchR[v]] = d[u] + 1;
          q.emplace(matchR[v]);
        }
      }
    }
    return d[0] != INF;
  }

  bool dfs(int u) {
    if (!u) return true;
    for (int &v: adj[u]) {
      if (d[matchR[v]] == d[u] + 1 && dfs(matchR[v])) {
        matchR[v] = u;
        matchL[u] = v;
        return true;
      }
    }
    d[u] = INF;
    return false;
  }

  int calc() {
    int res = 0;
    while (bfs())
      for (int u = 1; u <= n; ++u)
        if (!matchL[u] && dfs(u)) ++res;
    return res;
  }
};
