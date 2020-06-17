/**
Deterministic Miller-Rabin primality test for 64-bit number
Reference: https://cp-algorithms.com/algebra/primality_tests.html#toc-tgt-3

Tested on:
- https://www.spoj.com/problems/PON/
**/

#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;

// for 64 bit integer it is enough to check the first 12 prime bases
const ull BASE[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
ull mulmod(ull a, ull b, ull mod) {
  ull res = 0;
  for (; b; (a += a) %= mod, b >>= 1)
    if (b & 1) (res += a) %= mod;
  return res;
}
ull powmod(ull a, ull b, ull mod) {
  ull res = 1;
  for (; b; a = mulmod(a, a, mod), b >>= 1)
    if (b & 1) res = mulmod(res, a, mod);
  return res;
}
bool check_prime(ull n, ull a, ull d, int s) {
  ull x = powmod(a, d, n);
  if (x == 1 || x == n - 1) return true;
  for (int r = 2; r <= s; ++r) {
    x = mulmod(x, x, n);
    if (x == n - 1) return true;
  }
  return false;
}
bool miller_rabin(ull n) {
  if (n < 4) return (n == 2 || n == 3);
  ull d = n - 1;
  int s = 0;
  while ((d & 1) == 0) ++s, d >>= 1;
  for (auto a: BASE) {
    if (n == a) return true;
    if (!check_prime(n, a, d, s)) return false;
  }
  return true;
}
