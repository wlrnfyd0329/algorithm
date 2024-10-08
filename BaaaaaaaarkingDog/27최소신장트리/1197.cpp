#include <iostream>
#include <queue>
#include <tuple>

using namespace std;

int V, E, cnt, result;
vector<pair<int, int>> v[10005];
bool chk[10005];
priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> V >> E;
    for(int i = 0; i < E; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        v[a].push_back({c, b});
        v[b].push_back({c, a}); // 항상 방향 그래프가 아니라면 필수다.
    }
    chk[1] = 1;
    for(auto k : v[1]){
        pq.push({k.first, 1, k.second});
    }
    while(cnt < V-1) {
        int cost, a, b;
        tie(cost, a, b) = pq.top(); pq.pop();
        if (chk[b]) continue;
        chk[b] = true;
        result += cost;
        cnt++;
        for(auto k : v[b]){
            if (chk[k.second]) continue;
            pq.push({k.first, b, k.second});
        }
    }
    cout << result;
}