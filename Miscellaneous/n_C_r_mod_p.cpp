#include <iostream>
#include <vector>
using namespace std;

// Function to perform modular exponentiation
// It returns (x^y) % p
int power(int x, int y, int p) {
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
int modInverse(int a, int p) {
    return power(a, p - 2, p);
}

// Function to precompute factorials and modular inverses of factorials
void precomputeFactorials(int n, int p, vector<int>& fact, vector<int>& invFact) {
    fact[0] = fact[1] = 1;
    for (int i = 2; i <= n; ++i) {
        fact[i] = fact[i - 1] * i % p;
    }
    invFact[n] = modInverse(fact[n], p);
    for (int i = n - 1; i >= 0; --i) {
        invFact[i] = invFact[i + 1] * (i + 1) % p;
    }
}

// Function to calculate nCr % p using precomputed factorials and inverses
int nCrModP(int n, int k, int p, const vector<int>& fact, const vector<int>& invFact) {
    if (k > n) return 0;
    return fact[n] * invFact[k] % p * invFact[n - k] % p;
}

int main() {
    int n = 10, k = 3, p = 7;

    vector<int> fact(n + 1), invFact(n + 1);
    precomputeFactorials(n, p, fact, invFact);

    int result = nCrModP(n, k, p, fact, invFact);
    cout << "nCr % p = " << result << endl;

    return 0;
}
