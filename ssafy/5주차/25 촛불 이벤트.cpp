#include <iostream>
#define endl "\n"

typedef long long ll;
using namespace std;

ll cnt;

ll solve() {
    ll lf = 1, rg = 10'000'000'000;
    while(lf <= rg) {
        ll mid = (lf + rg) >> 1;
        ll candle = mid * (mid + 1) / 2;
        if (candle == cnt) {
            return mid;
        }
        else if (candle < cnt) {
            lf = mid + 1;
        }
        else {
            rg = mid - 1;
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        cin >> cnt;
        cout << "#" << tc << " " << solve() << endl;
    }
}