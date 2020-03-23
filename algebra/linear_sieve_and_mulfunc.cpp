/**
Sieve of Eratosthenes
Bonus: Euler's totient function and Mobius function
Time complexity: O(N)

Tested on:
- http://www.spoj.com/problems/ETF/
**/

#include <bits/stdc++.h>
using namespace std;
const int N = 10000000; // 1e7

int lp[N + 1], phi[N + 1], mu[N + 1];
vector<int> pr;

// Prime sieve only
void primeSieve() {
  for (int i = 2; i <= N; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.emplace_back(i);
    }
    for (int j = 0; j < (int)pr.size() && pr[j] <= lp[i] && i * pr[j] <= N; ++j) {
      lp[i * pr[j]] = pr[j];
    }
  }
}

// Prime sieve + phi function + mobius function
void primeSieveBonus() {
  phi[1] = mu[1] = 1;
  for (int i = 2; i <= N; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.emplace_back(i);
      phi[i] = i - 1;
      mu[i] = -1;
    }
    for (int j = 0; j < (int)pr.size() && pr[j] <= lp[i] && i * pr[j] <= N; ++j) {
      lp[i * pr[j]] = pr[j];
      if (pr[j] < lp[i]) {
        phi[i * pr[j]] = phi[i] * phi[pr[j]];
        mu[i * pr[j]] = mu[i] * mu[pr[j]];
      } else {
        phi[i * pr[j]] = phi[i] * pr[j];
        mu[i * pr[j]] = 0;
      }
    }
  }
}

int main() {
  primeSieveBonus();
  for (int i = 1; i <= 100; ++i) {
    printf("lp[%d] = %d; phi[%d] = %d; mu[%d] = %d\n", i, lp[i], i, phi[i], i, mu[i]);
  }
  return 0;
}