// 따라서 해당 문제는 이분탐색으로 찾아야 한다.

#include <iostream>
#include <algorithm>
#include <vector>
#define endl "\n"

using namespace std;

int t, n, m;
vector<int> v;
long long ans;
int a[1005];
int b[1005];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ans = 0;
    cin >> t >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] += a[i - 1];
    }
    cin >> m;
    for(int i = 1; i <= m; i++) {
        cin >> b[i];
        b[i] += b[i - 1];
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < i; j++) {
            v.push_back(a[i] - a[j]);
        }
    }

    sort(v.begin(), v.end());

    for(int i = 1; i <= m; i++) {
        for(int j = 0; j < i; j++) {
            int diff = t - (b[i] - b[j]);
            ans += upper_bound(v.begin(), v.end(), diff) - lower_bound(v.begin(), v.end(), diff);
        }
    }

    cout << ans;
}