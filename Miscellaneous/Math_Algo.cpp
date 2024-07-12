// power fucntion in log(n)
int binpow(int a, int b) {
  int res = 1;
  while (b > 0) {
  if (b & 1)
  res = res * a;
  a = a * a;
  b >>= 1;
  }
return res;
}
// log function
int log_(int n){
    return 31 - __builtin_clz(n);
}
// gcd fucntion
int gcd(int a, int b)
{
if (a == 0)
return b;
return gcd(b % a, a);
}
// mod inverse
int modInverse(int a, int p) {
    return power(a, p - 2, p);
}
// power with mod
int power(int x, unsigned int y, int p) {
    int res = 1; 
    x = x % p; 
    while (y > 0) {
        if (y & 1)
            res = (res * x) % p;
        y = y >> 1; 
        x = (x * x) % p;
    }
    return res;
}
// prime factorization
vector<int> primeFactors(int n) {
    vector<int> factors;
    while (n % 2 == 0) {
        factors.push_back(2);
        n /= 2;
    }
    for (int i = 3; i <= sqrt(n); i += 2) {
        while (n % i == 0) {
            factors.push_back(i);
            n /= i;
        }
    }
    if (n > 2) {
        factors.push_back(n);
    }
    return factors;
}
// Function to genrate all prime
vector<int> sieveOfEratosthenes(int n) {
    vector<bool> isPrime(n + 1, true); // Initialize all entries as true
    isPrime[0] = isPrime[1] = false;   // 0 and 1 are not prime numbers
    for (int p = 2; p * p <= n; ++p) {
        if (isPrime[p]) {
            for (int i = p * p; i <= n; i += p) {
                isPrime[i] = false;
            }
        }
    }
    vector<int> primes;
    for (int p = 2; p < n; ++p) {
        if (isPrime[p]) {
            primes.push_back(p);
        }
    }
    return primes;
}
