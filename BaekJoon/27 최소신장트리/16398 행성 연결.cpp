#include <iostream>
#include <queue>
#include <vector>
#include <tuple>

using namespace std;

int cnt;
long long result;
vector<pair<int, int>> v[1005];
bool chk[1005];
priority_queue < tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            int a;
            cin >> a;
            if (a == 0) continue;
            v[i].push_back({a, j});
        }
    }

    chk[1] = true;
    for(auto k : v[1]) {
        pq.push({k.first, 1, k.second});
    }

    while(cnt < n - 1) {
        int cost, a, b;
        tie(cost, a, b) = pq.top(); pq.pop();
        if (chk[b]) continue;
        chk[b] = true;
        cnt++;
        result += cost;
        for(auto k : v[b]) {
            if (chk[k.second]) continue;
            pq.push({k.first, b, k.second});
        }
    }
    
    cout << result;
}