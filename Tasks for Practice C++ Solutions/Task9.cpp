#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef __uint128_t u128;

// Function to perform modular multiplication safely
ull mod_mul(ull a, ull b, ull mod) {
    return ((u128)a * b) % mod;
}

// Function to perform modular exponentiation
ull mod_pow(ull base, ull exponent, ull mod) {
    ull result = 1;
    base %= mod;
    while (exponent > 0) {
        if (exponent & 1)
            result = mod_mul(result, base, mod);
        base = mod_mul(base, base, mod);
        exponent >>= 1;
    }
    return result;
}

// Miller-Rabin primality test
bool is_prime(ull n) {
    if (n < 2)
        return false;
    if (n <= 3)
        return true;
    if (n % 2 == 0)
        return false;

    // Write n-1 as d * 2^s by factoring powers of 2 from n-1
    ull s = 0;
    ull d = n - 1;
    while (d % 2 == 0) {
        d >>= 1;
        s++;
    }

    // Witnesses for deterministic test up to 1e18
    ull witnesses[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41};

    for (ull a : witnesses) {
        if (a >= n)
            continue;
        ull x = mod_pow(a, d, n);
        if (x == 1 || x == n - 1)
            continue;
        bool composite = true;
        for (ull r = 1; r < s; ++r) {
            x = mod_mul(x, x, n);
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite)
            return false;
    }
    return true;
}

int main() {
    ull m;
    cin >> m;

    if (m == 1) {
        cout << 0 << endl;
    } else if (is_prime(m)) {
        cout << m - 1 << endl;
    } else {
        cout << 1 << endl;
    }

    return 0;
}
