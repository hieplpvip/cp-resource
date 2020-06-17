/**
Find all prime numbers in [L, R].
To use this, you must be able to create a vector of R - L + 1 elements.
Time complexity: O(sqrt(R))
Tested on: https://www.spoj.com/problems/PRIME1/
**/

vector<bool> segmentedSieve(long long L, long long R) {
  // generate all primes up to sqrt(R)
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
  if (L == 1) isPrime[0] = false; // special case when L = 1
  return isPrime;
}
