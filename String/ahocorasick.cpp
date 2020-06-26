struct AhoCorasick {
  struct Node {
    int p = -1, link = -1, nxt[26], go[26];
    bool leaf = false;
    char pch;
    Node(int p = -1, char pch = '#'): p(p), pch(pch) {
      memset(nxt, -1, sizeof(nxt));
      memset(go, -1, sizeof(go));
    }
  };
  vector<Node> trie;

  void init() {
    trie.emplace_back(-1, '#');
  }

  void add_string(const string &s) {
    int v = 0;
    for (auto x: s) {
      int c = x - 'a';
      if (!trie[v].nxt[c]) {
        trie[v].nxt[c] = trie.size();
        trie.emplace_back(v, x);
      }
      v = trie[v].nxt[c];
    }
    trie[v].leaf = true;
  }

  int get_link(int u) {
    if (trie[u].link == -1) {
      if (u == 0 || trie[u].p == 0) {
        trie[u].link = 0;
      } else {
        trie[u].link = go(get_link(trie[u].p), trie[u].pch);
      }
    }
    return trie[u].link;
  }

  int go(int u, char ch) {
    int c = ch - 'a';
    if (trie[u].go[c] == -1) {
      if (trie[u].nxt[c] != -1) {
        trie[u].go[c] = trie[u].nxt[c];
      } else {
        trie[u].go[c] = (u == 0) ? 0 : go(get_link(u), ch);
      }
    }
    return trie[u].go[c];
  }
};
