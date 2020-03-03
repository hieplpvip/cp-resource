const int N = 2005;

struct state {
  int len, link;
  unordered_map<char, int> next;
};

int sz, last;
state st[2 * N];

void st_init() {
  st[0].link = -1;
  sz++;
}

void st_extend(char c) {
  int cur = sz++;
  st[cur].len = st[last].len + 1;
  int p = last;
  while (p != -1 && !st[p].next.count(c)) {
    st[p].next[c] = cur;
    p = st[p].link;
  }
  if (p != -1) {
    int q = st[p].next[c];
    if (st[p].len + 1 == st[q].len) {
      st[cur].link = q;
    } else {
      int clone = sz++;
      st[clone].len = st[p].len + 1;
      st[clone].link = st[q].link;
      st[clone].next = st[q].next;
      while (p != -1 && st[p].next[c] == q) {
        st[p].next[c] = clone;
        p = st[p].link;
      }
      st[cur].link = st[q].link = clone;
    }
  }
  last = cur;
}