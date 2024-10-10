#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;
int n, m, st, en;
vector<pair<int, int>> city[1005];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
int d[1005];
int pr[1005];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        city[u].push_back({w, v});
    }
    cin >> st >> en;
    fill(d, d+n+1, INF);
    d[st] = 0;
    pq.push({d[st], st});
    while(!pq.empty()) {
        auto cur = pq.top(); pq.pop();
        if (d[cur.second] != cur.first) continue;
        for(auto nxt: city[cur.second]) {
            if (d[nxt.second] <= nxt.first + d[cur.second]) continue;
            d[nxt.second] = nxt.first + d[cur.second];
            pq.push({d[nxt.second], nxt.second});
            pr[nxt.second] = cur.second;
        }
    }

    cout << d[en] << "\n";
    vector<int> pc;
    int tmp = en;
    while(tmp != st){
        pc.push_back(tmp);
        tmp = pr[tmp];
    }
    pc.push_back(st);
    reverse(pc.begin(), pc.end());
    cout<< pc.size() << "\n";
    for(auto k : pc) {
        cout << k << " ";
    }
}