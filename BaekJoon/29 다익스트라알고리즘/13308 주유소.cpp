#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

typedef long long ll;

using namespace std;

int n, m;
ll ans;
int fuel[2505];
struct Road {
    int en;
    int len;
};
struct Node {
    ll value;
    int city;
    int cost;

    bool operator<(const Node& other) const {
        return value > other.value;
    }
};
vector<Road> road[2505];
priority_queue<Node> pq;
ll dist[2505][2505]; // 1번 도시에서 [0]도시까지 기름의 가격이 [1]일때 최소 비용

ll dijkstra() {
    pq.push({0, 1, fuel[1]});
    dist[1][fuel[1]] = 0;

    while(!pq.empty()) {
        Node now;
        now = pq.top(); pq.pop();

        if (now.city == n) return dist[n][now.cost];

        if (dist[now.city][now.cost] != now.value) continue;
        for(auto next : road[now.city]) {
            int low_cost = min(now.cost, fuel[next.en]);
            if (dist[next.en][low_cost] <= dist[now.city][now.cost] + (ll)now.cost * next.len) continue;
            dist[next.en][low_cost] = dist[now.city][now.cost] + (ll)now.cost * next.len;
            pq.push({dist[next.en][low_cost], next.en, low_cost});
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        cin >> fuel[i];
    }

    for(int i = 0; i < m; i++) {
        int st, en, len;
        cin >> st >> en >> len;
        road[st].push_back({en, len});
        road[en].push_back({st, len});
    }

    for(int i = 0; i < 2505; i++) {
        for(int j = 0; j < 2505; j++) {
            dist[i][j] = 1e18;
        }
    }

    cout << dijkstra();
}