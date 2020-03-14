/** Dynamic LiChao Segment Tree
    Add lines/segments in arbitrary slope order. Query maximum value at x.
    To get minimum value, add lines/segments with -a and -b and get -query
    Time complexity: O(lgn) for each operation
    Source: my own code
    
    Tested on:
    - https://codeforces.com/gym/101175/problem/F (can also be solved with dynamic convex hull)
    - https://vn.spoj.com/problems/VOMARIO/ (can only be solved with LiChao Segment Tree since the objects are segments, not lines)
**/

template<typename T, T minX, T maxX, T defVal>
struct DynamicLiChaoTree {
private:
  struct Line {
    T a, b;
    inline T calc(T x) const { return a * x + b; }
  };
  struct Node {
    Line line = {0, defVal};
    Node *lt = nullptr, *rt = nullptr;
  };
  Node* root;
  vector<Node*> listNode;
  void update(Node* cur, T l, T r, T u, T v, Line nw) {
    if (v < l || r < u) return;
    T mid = (l + r) >> 1;
    if (u <= l && r <= v) {
      if (cur->line.calc(l) >= nw.calc(l)) swap(cur->line, nw);
      if (cur->line.calc(r) <= nw.calc(r)) {
        cur->line = nw;
        return;
      }
      if (nw.calc(mid) >= cur->line.calc(mid)) {
        if (!cur->rt) cur->rt = new Node(), listNode.push_back(cur->rt);
        update(cur->rt, mid + 1, r, u, v, cur->line);
        cur->line = nw;
      } else {
        if (!cur->lt) cur->lt = new Node(), listNode.push_back(cur->lt);
        update(cur->lt, l, mid, u, v, nw);
      }
    } else {
      if (!cur->rt) cur->rt = new Node(), listNode.push_back(cur->lt);
      if (!cur->lt) cur->lt = new Node(), listNode.push_back(cur->rt);
      update(cur->lt, l, mid, u, v, nw);
      update(cur->rt, mid + 1, r, u, v, nw);
    }
  }
  T query(Node* cur, T l, T r, T x) {
    T res = cur->line.calc(x);
    T mid = (l + r) >> 1;
    if (x <= mid && cur->lt)
      res = max(res, query(cur->lt, l, mid, x));
    else if (x > mid && cur-> rt)
      res = max(res, query(cur->rt, mid + 1, r, x));
    return res;
  }
public:
  void addLine(T a, T b, T l = minX, T r = maxX) {
    update(root, minX, maxX, l, r, {a, b});
  }
  T query(T x) {
    return query(root, minX, maxX, x);
  }
  void init() {
    for (auto ptr: listNode) delete(ptr);
    root = new Node;
    listNode.clear();
    listNode.push_back(root);
  }
};