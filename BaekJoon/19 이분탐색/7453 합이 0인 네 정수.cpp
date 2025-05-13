#include <iostream>
#include <algorithm>
#include <vector>
#define endl "\n"

typedef long long ll;
using namespace std;

int N;
vector<ll> arr[4];
vector<ll> ans[2];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    ll cnt = 0;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < 4; j++) {
            int num; cin >> num;
            arr[j].push_back(num);
        }
    }

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            ans[0].push_back(arr[0][i] + arr[1][j]);
            ans[1].push_back(arr[2][i] + arr[3][j]);
        }
    }

    sort(ans[0].begin(), ans[0].end());
    sort(ans[1].begin(), ans[1].end());

    for(auto k : ans[0]) {
        cnt += upper_bound(ans[1].begin(), ans[1].end(), -k) - lower_bound(ans[1].begin(), ans[1].end(), -k);
    }

    cout << cnt;
}