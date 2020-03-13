/**
Dinitz Algorithm
Time complexity: O(E * V^2) in general. O(E * sqrt(V)) on unit graph

Tested on:
- http://vn.spoj.com/problems/NKFLOW/ (directed)
**/

template<int MAXN, typename T = long long>
struct Dinitz {
  const T INF = numeric_limits<T>::max();
  struct Edge {
    int v;
    T c;
    Edge(int _v, T _c): v(_v), c(_c) {}
  };

  int n, s, t, level[MAXN], q[MAXN];
  size_t ptr[MAXN];
  vector<Edge> edges;
  vector<int> adj[MAXN];

  Dinitz(int _n, int _s, int _t): n(_n), s(_s), t(_t) {}

  void addEdge(int u, int v, T c, bool directed = true) {
    adj[u].emplace_back(edges.size());
    edges.emplace_back(v, c);
    adj[v].emplace_back(edges.size());
    edges.emplace_back(u, directed ? 0 : c);
  }

  T dfs(int u, T pushed) {
    if (u == t)
      return pushed;
    while (ptr[u] < adj[u].size()) {
      int id = adj[u][ptr[u]++];
      auto &e = edges[id];
      if (level[e.v] == level[u] + 1 && e.c) {
        T tmp = dfs(e.v, min(pushed, e.c));
        if (tmp > 0) {
          edges[id].c -= tmp;
          edges[id ^ 1].c += tmp;
          return tmp;
        }
      }
    }
    return 0;
  }

  T calc() {
    T flow = 0;
    while (true) {
      memset(level, -1, sizeof(int) * (n + 1));
      int qh = 0, qt = 0;
      level[s] = 0;
      q[qt++] = s;
      while (qh < qt && level[t] == -1) {
        int u = q[qh++];
        for (int &id: adj[u]) {
          auto &e = edges[id];
          if (level[e.v] == -1 && e.c) {
            level[e.v] = level[u] + 1;
            q[qt++] = e.v;
          }
        }
      }
      if (level[t] == -1) break;
      memset(ptr, 0, sizeof(size_t) * (n + 1));
      while (T delta = dfs(s, INF)) flow += delta;
    }
    return flow;
  }
};