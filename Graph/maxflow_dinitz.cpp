/**
Dinitz Algorithm
Time complexity: O(E * V^2) in general. O(E * sqrt(V)) on unit graph

Tested on:
- http://vn.spoj.com/problems/NKFLOW/ (directed)
**/

template<typename flow_t>
struct Dinitz {
  const flow_t INF = numeric_limits<flow_t>::max();
  struct Edge {
    int v;
    flow_t c;
  };
  int n, s, t;
  vector<Edge> edges;
  vector<int> ptr, level;
  vector<vector<int>> adj;
  Dinitz(int n, int s, int t): n(n), s(s), t(t), ptr(n + 1), level(n + 1), adj(n + 1) {};

  void addEdge(int u, int v, flow_t c, bool directed = true) {
    adj[u].emplace_back(edges.size());
    edges.push_back({v, c});
    adj[v].emplace_back(edges.size());
    edges.push_back({u, directed ? 0 : c});
  }

  bool bfs() {
    fill(level.begin(), level.end(), -1);
    queue<int> q;
    level[s] = 0; q.emplace(s);
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (int &id: adj[u]) {
        auto &e = edges[id];
        if (level[e.v] == -1 && e.c > 0) {
          level[e.v] = level[u] + 1;
          q.emplace(e.v);
        }
      }
    }
    return (level[t] != -1);
  }

  flow_t dfs(int u, flow_t pushed) {
    if (u == t) return pushed;
    while (ptr[u] < (int)adj[u].size()) {
      int id = adj[u][ptr[u]++];
      auto &e = edges[id];
      if (level[e.v] == level[u] + 1 && e.c > 0) {
        flow_t tmp = dfs(e.v, min(pushed, e.c));
        if (tmp > 0) {
          edges[id].c -= tmp;
          edges[id ^ 1].c += tmp;
          return tmp;
        }
      }
    }
    return 0;
  }

  flow_t calc() {
    flow_t res = 0;
    while (bfs()) {
      fill(ptr.begin(), ptr.end(), 0);
      while (flow_t delta = dfs(s, INF)) res += delta;
    }
    return res;
  }
};
