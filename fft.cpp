#include <bits/stdc++.h>
#include <chrono>
#define int long long int
using namespace std;

// constants
const int MAXN = 5e5;
const int MOD = 998244353;
const int root = 15311432;
const int root_1 = 469870224;
const int root_pw = 1 << 23;

// function that returns a^b mod m
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

// recursive FFT
void fft (vector <int> &a, bool invert)
{
    int n = a.size();
    if (n == 1)
        return;
    vector <int> a0(n / 2), a1(n / 2);
    for (int i = 0; 2 * i < n; i++)
    {
        a0[i] = a[2 * i];
        a1[i] = a[2 * i + 1];
    }
    // do recursive call on a0 and a1
    fft(a0, invert);
    fft(a1, invert);
    
    int w = 1, wn = invert? root_1 : root;

    for (int i = n; i < root_pw; i <<= 1)
        wn = (wn * wn) % MOD;

    for (int i = 0; 2 * i < n; i++)
    {
        int u = a0[i], v = (w * a1[i]) % MOD;
        a[i] = (u + v) % MOD;
        a[i + n / 2] = (u - v + MOD) % MOD;

        if (invert)
        {
            a[i] = (a[i] * 499122177) % MOD; // a[i] /= 2 but in modular arithmetic
            a[i + n / 2] = (a[i + n / 2] * 499122177) % MOD; // a[i + n / 2] /= 2 but in modular arithmetic
        }
        w = (1LL * w * wn % MOD); 
    }
}

int32_t main()
{
    vector <int> a;
    int n, k;
    cin >> k >> n; // input n and k
    auto start = std::chrono::high_resolution_clock::now();
    int l = 1 << k;
    a.resize(l, 0); // set array size to 2^k
    a[0] = 1;
    a[1] = 1;
    // do fft
    fft(a, false);
    // polynomial multiplication of (1 + x)^n
    for (int i = 0; i < l; i++)
        a[i] = binpow(a[i], n, MOD);
    // inverse fft
    fft(a, true);
    for (int i = 0; i < l; i++)
    {
        cout << a[i] << ' ';
    }
    cout << endl;
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    cout << "Execution time: " << duration.count() << " miliseconds." << std::endl;
    return 0;
}