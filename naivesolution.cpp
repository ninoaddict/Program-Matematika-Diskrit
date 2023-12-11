#include <bits/stdc++.h>
#define int long long int
using namespace std;

// Constant
const int MOD = 998244353;

// Array to save factorial results from preprocessing
vector <int> fact;

// Function that returns a^b mod m
int binpow(int a, int b, int m)
{
    int res = 1;
    while (b)
    {
        if (b & 1) 
            res = (res * a) % m;
        a = (a * a) % m;
        b /= 2;
    }
    return res;
}

// Preprocessing procedure
void prep(int n)
{
    fact.resize(n + 1, 0);
    fact[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        fact[i] = (i * fact[i - 1]) % MOD;
    }
}

int32_t main()
{
    int n, k, kPow;
    cin >> k >> n; // Read n and k
    auto start = std::chrono::high_resolution_clock::now();
    kPow = 1 << k;
    prep(n);
    vector <int> a(kPow, 0);
    // Calculate coefficients for all terms
    for (int i = 0; i <= n; i++)
    {
        int denominator = (fact[i] * fact[n - i]) % MOD;
        int numerator = fact[n];
        a[i % kPow] = (a[i % kPow] + (numerator * binpow(denominator, MOD - 2, MOD)) % MOD) % MOD; 
    }

    // Show answer
    for (int i = 0; i < kPow; i++)
    {
        cout << a[i] << ' ';
    }
    cout << '\n';
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    cout << "Execution time: " << duration.count() << " miliseconds." << std::endl;
    return 0;
}