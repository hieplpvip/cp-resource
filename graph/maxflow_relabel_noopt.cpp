/**
Push-relabel without any optimization/heuristic

Tested on:
- http://vn.spoj.com/problems/NKFLOW/ (directed)
**/

template<typename flow_t>
struct PreflowPush {
  struct Edge {
    int v;
    flow_t c;
  };
  vector<Edge> edges;
  int n, s, t;
  vector<vector<int>> adj;
  vector<int> h, seen;
  vector<flow_t> flowin;
  queue<int> ex_vert;
  PreflowPush(int n, int s, int t): n(n), s(s), t(t), adj(n + 1), h(n + 1), seen(n + 1), flowin(n + 1) {};

  void addEdge(int u, int v, flow_t c, bool directed = true) {
    adj[u].emplace_back(edges.size());
    edges.push_back({v, c});
    adj[v].emplace_back(edges.size());
    edges.push_back({u, directed ? 0 : c});
  }

  void push(int id, flow_t d) {
    auto &e = edges[id];
    auto &rev = edges[id ^ 1];
    e.c -= d; rev.c += d;
    flowin[e.v] += d;
    flowin[rev.v] -= d;
    if (flowin[e.v] == d) ex_vert.emplace(e.v);
  }

  flow_t calc() {
    h[s] = n;
    for (int &id: adj[s]) push(id, edges[id].c);
    while (!ex_vert.empty()) {
      int u = ex_vert.front(); ex_vert.pop();
      if (u == s || u == t) continue;
      while (flowin[u] > 0) {
        if (seen[u] < (int)adj[u].size()) {
          int id = adj[u][seen[u]++];
          if (h[u] > h[edges[id].v] && edges[id].c > 0)
            push(id, min(flowin[u], edges[id].c));
        } else {
          int minH = 1e9;
          for (int &id: adj[u]) {
            if (edges[id].c > 0 && h[edges[id].v] < minH)
              minH = h[edges[id].v];
          }
          h[u] = minH + 1;
          seen[u] = 0;
        }
      }
    }
    return -flowin[s];
  }
};
