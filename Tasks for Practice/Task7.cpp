#include <bits/stdc++.h>
using namespace std;
typedef int64_t ll;
typedef uint64_t ull;

// Modulo value (given as 10^8 + 7)
const ll M = 100000007;

// Custom hash function to prevent hash collisions in unordered_map
struct custom_hash {
    static ull splitmix64(ull x) {
        // SplitMix64 hash function
        x += 0x9e3779b97f4a7c15ull;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ull;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebull;
        return x ^ (x >> 31);
    }
    size_t operator()(ull x) const {
        static const ull FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

// Modular multiplication to handle large numbers without overflow
ll mod_mul(ll a, ll b, ll mod) {
    return (__int128)a * b % mod;
}

// Modular exponentiation (fast power)
ll mod_pow(ll a, ll b, ll mod) {
    ll res = 1;
    a %= mod;
    while (b > 0) {
        if (b & 1)
            res = mod_mul(res, a, mod);
        a = mod_mul(a, a, mod);
        b >>= 1;
    }
    return res;
}

// Modular inverse using Fermat's Little Theorem (since mod is prime)
ll mod_inv(ll a, ll mod) {
    return mod_pow(a, mod - 2, mod);
}

// Baby-Step Giant-Step algorithm to solve for minimal n in K^n ≡ result (mod M)
ll bsgs(ll K, ll result) {
    if (result == 1)
        return 0; // The minimal n is 0 if result is 1
    ll m = sqrt(M) + 1;
    unordered_map<ll, ll, custom_hash> table; // Hash table for baby steps
    ll e = 1;
    // Baby steps: K^i mod M
    for (ll i = 0; i < m; ++i) {
        if (!table.count(e))
            table[e] = i;
        e = mod_mul(e, K, M);
    }
    // Compute K^{-m} mod M
    ll factor = mod_inv(mod_pow(K, m, M), M);
    e = result % M;
    // Giant steps
    for (ll j = 0; j <= m; ++j) {
        if (table.count(e)) {
            ll n = j * m + table[e];
            return n; // Minimal n found
        }
        e = mod_mul(e, factor, M);
    }
    return -1; // No solution found (should not happen as per problem statement)
}

int main() {
    int T;
    scanf("%d", &T); // Read number of test cases
    for (int case_num = 1; case_num <= T; ++case_num) {
        ll K, result;
        scanf("%lld %lld", &K, &result); // Read K and result for each test case
        ll n = bsgs(K % M, result % M); // Compute minimal n using BSGS algorithm
        printf("Case %d: %lld\n", case_num, n); // Output the result
    }
    return 0;
}
