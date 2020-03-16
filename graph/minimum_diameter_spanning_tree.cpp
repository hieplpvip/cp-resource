/**
Find the spanning tree with minimum diameter in O(n^3)

This code only output the value of minimum diameter.
To rebuild the spanning tree, perform multi-source Dijkstra from u and v,
where (u, v) is the edge that minimizes ans (see code below)

Source: https://web.archive.org/web/20160309101249/https://adn.botao.hu/adn-backup/blog/attachments/month_0705/32007531153238.pdf
Implemented by myself. Tested on https://codeforces.com/contest/266/problem/D
**/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll oo = 1e18;
const int N = 500;
 
struct Edge {
  int u, v, w;
  Edge(int _u, int _v, int _w): u(_u), v(_v), w(_w) {}
};
 
int n, m;
ll d[N][N], ans = oo;
vector<int> que[N];
vector<Edge> edges;
 
int main() {
  ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      d[i][j] = (i == j) ? 0 : oo;
    }
  }
  for (int i = 1, u, v, w; i <= m; ++i) {
    cin >> u >> v >> w;
    w *= 2;
    d[u][v] = d[v][u] = min(d[u][v], (ll)w);
    edges.emplace_back(u, v, w);
  }
  for (int k = 1; k <= n; ++k) {
    for (int u = 1; u <= n; ++u) {
      for (int v = 1; v <= n; ++v) {
        d[u][v] = min(d[u][v], d[u][k] + d[k][v]);
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    que[i].resize(n);
    iota(que[i].begin(), que[i].end(), 1);
    sort(que[i].begin(), que[i].end(), [&](const int &a, const int &b) {
      return d[i][a] > d[i][b];
    });
  }
  for (auto &e: edges) {
    int &u = e.u, &v = e.v, cur = que[u][0];
    ll w = e.w, tans = oo;
    tans = min({tans, d[u][cur], d[v][cur] + w});
    for (int &z: que[u]) {
      if (d[v][cur] < d[v][z]) {
        tans = min(tans, (w + d[v][cur] + d[u][z]) / 2);
        cur = z;
      }
    }
    tans = min({tans, d[v][cur], d[u][cur] + w});
    ans = min(ans, tans);
  }
  cout << fixed << setprecision(2) << (double)ans / 2.0;
  return 0;
}