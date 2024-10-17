#include <bits/stdc++.h>
using namespace std;

int main() {

    // For fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    for(int ts = 1; ts <= t; ++ts) {
        pair <long long, long long> A, B;
        cin >> A.first >> A.second >> B.first >> B.second;

        cout << "Case " << ts << ": " << __gcd(abs(A.first - B.first), abs(A.second - B.second)) + 1 << '\n';
    }

    return 0;
}
