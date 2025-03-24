#include <iostream>
#include <vector>
#define endl "\n"

typedef long long ll;
using namespace std;

ll N, M;
vector<ll> cnt;

ll solve() {
    ll lf = 1, rg = 1'000'000'000'000'000'000;
    while (lf <= rg) {
        ll mid = (lf + rg) >> 1;
        ll sum = 0;
        for (auto k : cnt) {
            sum += k / mid;
        }
        if (sum >= M) {
            lf = mid + 1;
        }
        else {
            rg = mid - 1;
        }
    }

    return rg;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T; cin >> T;

    for (int tc = 1; tc <= T; tc++) {
        cin >> N >> M;
        cnt = vector<ll>(N);
        for (int i = 0; i < N; i++) {
            ll num; cin >> num;
            cnt[i] = num;
        }

        cout << "#" << tc << " " << solve() << endl;
    }
}