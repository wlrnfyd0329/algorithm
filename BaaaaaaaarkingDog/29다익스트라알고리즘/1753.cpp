#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int V, E, k;
const int INF = 0x3f3f3f3f;
vector<pair<int, int>> g[20005];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
int d[20005];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> V >> E >> k;
    for(int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({w, v});
    }
    fill(d, d + V + 1, INF);
    d[k] = 0;
    pq.push({d[k], k});
    while(!pq.empty()) {
        auto cur = pq.top();
        pq.pop();
        if(d[cur.second] != cur.first) continue;
        for(auto nxt : g[cur.second]) {
            if (d[nxt.second] <= nxt.first + d[cur.second]) continue;
            d[nxt.second] = nxt.first + d[cur.second];
            pq.push({d[nxt.second], nxt.second});
        }
    }
    for(int i = 1; i <= V; i++) {
        if (d[i] == INF) {
            cout << "INF\n";
        }
        else {
            cout << d[i] << "\n";
        }
    }
}