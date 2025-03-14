#include <iostream>
#include <algorithm>

typedef long long ll;
using namespace std;

int n;
int road[100005];
int cost[100005];
ll ans;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for(int i = 0; i < n - 1; i++) {
        cin >> road[i];
    }
    for(int i = 0; i < n; i++) {
        cin >> cost[i];
    }
    int low_cost = 2'000'000'000;
    for(int i = 0; i < n; i++) {
        low_cost = min(low_cost, cost[i]);
        ans += road[i] * (ll)low_cost;
    }
    cout << ans;
}