#include <iostream>
#include <vector>
#include <queue>
#define X first
#define Y second

using namespace std;

int n, m, r;
const int INF = 0x3f3f3f3f;
vector<pair<int, int>> v[105];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
int item[105];

int dijkstra(int st) {
    int item_cnt = 0;
    int dist[105];
    for(int i = 1; i <= n; i++) {
        dist[i] = INF;
    }

    dist[st] = 0;
    pq.push({dist[st], st});

    while(!pq.empty()) {
        auto cur = pq.top(); pq.pop();
        if (dist[cur.Y] != cur.X) continue;
        for(auto nxt : v[cur.Y]) {
            if (dist[nxt.Y] <= nxt.X + dist[cur.Y]) continue;
            dist[nxt.Y] = nxt.X + dist[cur.Y];
            pq.push({dist[nxt.Y], nxt.Y});
        }
    }

    for(int i = 1; i <= n; i++) {
        if (dist[i] > m) continue;
        item_cnt += item[i]; 
    }

    return item_cnt;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> r;
    for(int i = 1; i <= n; i++) {
        cin >> item[i];
    }
    
    for(int i = 0; i < r; i++) {
        int a, b, l;
        cin >> a >> b >> l;
        v[a].push_back({l, b});
        v[b].push_back({l, a});
    }

    int total = 0;
    for(int i = 1; i <= n; i++) {
        total = max(total, dijkstra(i));
    }
    cout << total;
}