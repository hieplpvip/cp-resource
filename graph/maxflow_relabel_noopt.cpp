/**
Push-relabel without any optimization/heuristic
**/

template<typename flow_t>
struct PreflowPush {
  struct Edge {
    int v;
    flow_t f, c;
    Edge(int _v, flow_t _c): v(_v), f(0), c(_c) {}
  };

  int n, s, t, seen[N], h[N];
  flow_t flowin[N];
  vector<Edge> edges;
  vector<int> adj[N];
  queue<int> ex_vert;

  PreflowPush(int _n, int _s, int _t): n(_n), s(_s), t(_t) {}

  void push(int id, flow_t d) {
    auto &e = edges[id];
    auto &rev = edges[id ^ 1];
    e.f += d; e.c -= d;
    rev.f -= d; rev.c += d;
    flowin[e.v] += d;
    flowin[rev.v] -= d;
    if (d == flowin[e.v]) ex_vert.emplace(e.v);
  }

  void addEdge(int u, int v, flow_t c) {
    adj[u].emplace_back(edges.size());
    edges.emplace_back(v, c);
    adj[v].emplace_back(edges.size());
    edges.emplace_back(u, 0);
  }

  flow_t run() {
    h[s] = n;
    for (int id: adj[s]) push(id, edges[id].c);
    while (!ex_vert.empty()) {
      int u = ex_vert.front(); ex_vert.pop();
      if (u == s || u == t) continue;

      while (flowin[u]) {
        if (seen[u] < (int)adj[u].size()) {
          int id = adj[u][seen[u]];
          if (h[u] > h[edges[id].v] && edges[id].c)
            push(id, min(flowin[u], edges[id].c));
          ++seen[u];
        } else {
          int minH = 1e9;
          for (int id: adj[u]) {
            if (edges[id].c && h[edges[id].v] < minH)
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
