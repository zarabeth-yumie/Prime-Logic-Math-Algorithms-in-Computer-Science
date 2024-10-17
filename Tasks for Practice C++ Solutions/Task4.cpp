#include<bits/stdc++.h>
using namespace std;

typedef long long LL;

LL mod = 1000000007;

vector<LL> primes;
map<LL, LL> times;

LL bigmod (LL b, LL p, LL m)
{
    if (p==0) return 1;
    if (p%2==0) {
        LL x=bigmod(b, p/2, m)%m;
        return (x*x)%m;
    }
    else return (b%m * bigmod(b, p-1, m))%m;
}

LL inv_mod(LL a, LL m) {
    return bigmod(a, m-2, m);
}

void factorization(long long n) {
    if (n % 2 == 0) {
        primes.push_back(2);
        while (n % 2 == 0) {
            times[2]++;
            n /= 2;
        }
    }
    for (long long d = 3; d * d <= n; d += 2) {
        if (n % d == 0) {
        primes.push_back(d);
            while (n % d == 0) {
                times[d]++;
                n /= d;
            }
        }
    }
    if (n > 1) {
        if (!times[n])
            primes.push_back(n);
        times[n]++;
    }
}

int main()
{
    int t, ca=1;
    cin>>t;
    while (t--) {
        primes.clear();
        times.clear();
        LL n, m;
        cin>>n>>m;

        factorization(n);
        for (auto i: primes) {
            times[i] *= m;
        }

        LL ans = 1;

        for (auto i: primes) {
            LL now = bigmod(i, times[i] + 1, mod);
            now -= 1;
            if (now < 0)  // The program may give a negative result for modulo of negative numbers
                now += mod;  // So we convert it to a positive value by adding mod
            LL low = inv_mod(i - 1, mod);
            now *= low;
            ans = ((ans % mod) * (now % mod)) % mod;
        }
        cout<<"Case "<<ca++<<": "<<ans<<endl;
    }

    return 0;
}
