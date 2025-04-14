#include <iostream>
#include <cmath>
#define endl "\n"

typedef long long ll;
using namespace std;

const int MOD = 1234567891;

ll square(int cnt) {
    if (cnt == 0) return 1;
    if (cnt == 1) return 31;

    ll tmp = square(cnt / 2);

    if (cnt % 2 == 0) {
        return (tmp * tmp) % MOD;
    }
    else {
        return (((tmp * tmp) % MOD) * 31) % MOD;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    string s;
    cin >> n >> s;
    ll ans = 0;
    for(int i = 0; i < n; i++) {
        ans += ((s[i] - 'a' + 1) * square(i));
        ans %= MOD;
    }
    cout << ans;
}