/**
segmengedSievewithpregen is faster
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <random>
using namespace std;
const int NLOOP = 20;

vector<bool> segmengedSievewithpregen(long long L, long long R) {
  // generate all prime up to sqrt(R)
  long long lim = sqrt(R);
  vector<bool> mark(lim + 1, false);
  vector<long long> primes;
  for (long long i = 2; i <= lim; ++i) {
    if (!mark[i]) {
      primes.emplace_back(i);
      for (long long j = i * i; j <= lim; j += i) mark[j] = true;
    }
  }

  vector<bool> isPrime(R - L + 1, true); // x is prime if isPrime[x - L] == true
  for (long long i: primes)
    for (long long j = max(i * i, (L + i - 1) / i * i); j <= R; j += i)
      isPrime[j - L] = false;
  if (L == 1) isPrime[0] = false;
  return isPrime;
}

vector<bool> segmengedSievenopregen(long long L, long long R) {
  vector<bool> isPrime(R - L + 1, true); // x is prime if isPrime[x - L] == true
  long long lim = sqrt(R);
  for (long long i = 2; i <= lim; ++i)
    for (long long j = max(i * i, (L + i - 1) / i * i); j <= R; j += i)
      isPrime[j - L] = false;
  if (L == 1) isPrime[0] = false;
  return isPrime;
}

mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
long long Rand(long long l, long long h) {
  return uniform_int_distribution<long long>(l, h)(rng);
}

int main() {
  for (int loop = 1; loop <= NLOOP; ++loop) {
    long long L = Rand(1e10, 1e12);
    long long R = L + Rand(1e6, 2e6);
    cout << "Loop " << loop << ": L = " << L << " R = " << R << "\n";
    vector<bool> isPrime1, isPrime2;
    {
      auto t1 = chrono::high_resolution_clock::now();
      isPrime1 = segmengedSievewithpregen(L, R);
      auto t2 = chrono::high_resolution_clock::now();
      auto duration = chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count() * 1e-9;
      cout << "segmengedSievewithpregen took " << duration << "s\n";
    }
    {
      auto t1 = chrono::high_resolution_clock::now();
      isPrime2 = segmengedSievenopregen(L, R);
      auto t2 = chrono::high_resolution_clock::now();
      auto duration = chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count() * 1e-9;
      cout << "segmengedSievenopregen took " << duration << "s\n";
    }
    if (isPrime1 == isPrime2)
      cout << "Same result\n";
    else
      cout << "Different result\n";
    cout << "\n\n";
  }
  return 0;
}