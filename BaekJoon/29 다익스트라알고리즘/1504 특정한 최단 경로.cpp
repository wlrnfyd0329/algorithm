#include <iostream>
#include <queue>
#include <vector>
#define X first
#define Y second

typedef long long ll;
using namespace std;

const ll INF = 0x3f3f3f3f;
int n, e, v1, v2;
vector<pair<int, int>> graph[805];
ll st_v1, st_v2, v1_v2, v1_en, v2_en;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

void djikstra(int st) {
    int dist[n+1];
    for(int i = 1; i <= n; i++) {
        dist[i] = INF;
    }

    dist[st] = 0;
    pq.push({dist[st], st});
    while(!pq.empty()) {
        auto cur = pq.top(); pq.pop();
        if(dist[cur.Y] != cur.X) continue;
        for(auto nxt : graph[cur.Y]) {
            if (dist[nxt.Y] <= nxt.X + dist[cur.Y]) continue;
            dist[nxt.Y] = nxt.X + dist[cur.Y];
            pq.push({dist[nxt.Y], nxt.Y});
        }
    }

    if (st == v1) {
        st_v1 = dist[1];
        v1_v2 = dist[v2];
        v1_en = dist[n];
    }
    else {
        st_v2 = dist[1];
        v2_en = dist[n];
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> e;
    for(int i = 0; i < e; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].push_back({c, b});
        graph[b].push_back({c, a});
    }
    cin >> v1 >> v2;
    djikstra(v1);
    djikstra(v2);
    ll distance = min(INF, st_v1 + v1_v2 + v2_en);
    distance = min(distance, st_v2 + v1_v2 + v1_en);
    if (distance >= INF) cout << -1;
    else cout << distance;
    
}