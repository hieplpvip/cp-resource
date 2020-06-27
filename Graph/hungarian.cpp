#include <bits/stdc++.h>
using namespace std;

struct Hungarian {
  const long long INF = 1e18;
  struct Edge {
    int u, v;
    long long c;
  };
  int n, start, finish, head;
  vector<int> trace, arg, matchX, matchY, q;
  vector<long long> fx, fy, d;
  vector<vector<int>> adj;
  vector<Edge> edges;

  Hungarian(int n): n(n), trace(n + 1), arg(n + 1), matchX(n + 1), matchY(n + 1), fx(n + 1), fy(n + 1), d(n + 1), adj(n + 1) {};

  inline int getC(int id) {
    return edges[id].c - fx[edges[id].u] - fy[edges[id].v];
  }

  void addEdge(int u, int v, long long c) {
    adj[u].emplace_back(edges.size());
    edges.push_back({u, v, c});
  }

  void initBFS() {
    for (int u = 1; u <= n; ++u) {
      d[u] = INF;
      arg[u] = -1;
      trace[u] = 0;
    }
    for (int &id: adj[start]) {
      d[edges[id].v] = getC(id);
      arg[edges[id].v] = start;
    }
    finish = 0;
    q.clear(); head = 0;
    q.emplace_back(start);
  }

  void findAugPath() {
    while (head < (int)q.size()) {
      int u = q[head++];
      for (int &id: adj[u]) {
        auto &e = edges[id];
        if (trace[e.v]) continue;
        long long c = getC(id);
        if (c == 0) {
          trace[e.v] = u;
          if (!matchY[e.v]) {
            finish = e.v;
            return;
          }
          q.emplace_back(matchY[e.v]);
        }
        if (d[e.v] > c) {
          d[e.v] = c;
          arg[e.v] = u;
        }
      }
    }
  }

  void subX_addY() {
    long long delta = INF;
    for (int v = 1; v <= n; ++v) {
      if (trace[v] == 0) delta = min(delta, d[v]);
    }

    fx[start] += delta;
    for (int v = 1; v <= n; ++v) {
      if (trace[v]) {
        int u = matchY[v];
        fx[u] += delta;
        fy[v] -= delta;
      } else {
        d[v] -= delta;
      }
    }

    for (int v = 1; v <= n; ++v) {
      if (trace[v] == 0 && d[v] == 0) {
        trace[v] = arg[v];
        if (matchY[v] == 0) {
          finish = v;
          return;
        }
        q.emplace_back(matchY[v]);
      }
    }
  }

  void enlarge() {
    do {
      int u = trace[finish];
      int nxt = matchX[u];
      matchX[u] = finish;
      matchY[finish] = u;
      finish = nxt;
    } while (finish);
  }

  void run() {
    for (int u = 1; u <= n; ++u) fx[u] = fy[u] = INF;
    for (auto &e: edges) fx[e.u] = min(fx[e.u], e.c);
    for (auto &e: edges) fy[e.v] = min(fy[e.v], e.c - fx[e.u]);
    for (int u = 1; u <= n; ++u) {
      start = u;
      initBFS();
      while (finish == 0) {
        findAugPath();
        if (!finish) subX_addY();
      }
      enlarge();
    }

    long long res = 0;
    for (int u = 1; u <= n; ++u) {
      long long rr = INF;
      for (int &id: adj[u]) {
        if (matchX[u] == edges[id].v) rr = min(rr, edges[id].c);
      }
      res += rr;
    }

    cout << res << "\n";
    for (int u = 1; u <= n; ++u) {
      cout << u << " " << matchX[u] << "\n";
    }
  }
};

int main() {
  ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
  int n; cin >> n;
  Hungarian match(n);
  int u, v, c;
  while (cin >> u >> v >> c) {
    match.addEdge(u, v, c);
  }
  match.run();
  return 0;
}
