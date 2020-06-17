/**
Order statistics tree. Use like set/map.

Support these two operations:
find_by_order(k) returns an iterator to the k-th smallest element (counting from zero)
order_of_key(x) returns the number of items that are strictly smaller than x

Tested on https://www.spoj.com/problems/ORDERSET/
**/

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template<class key, class value, class cmp = less<key>>
using ordered_map = tree<key, value, cmp, rb_tree_tag, tree_order_statistics_node_update>;

template<class key, class cmp = less<key>>
using ordered_set = tree<key, null_type, cmp, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
  ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
  int q; cin >> q;
  ordered_set<int> st;
  while (q--) {
    char c; int x;
    cin >> c >> x;
    if (c == 'K') {
      if (x > (int)st.size()) cout << "invalid\n";
      else cout << *st.find_by_order(x - 1) << "\n";
    } else if (c == 'C') {
      cout << st.order_of_key(x) << "\n";
    } else if (c == 'I') {
      st.insert(x);
    } else {
      st.erase(x);
    }
  }
  return 0;
}
