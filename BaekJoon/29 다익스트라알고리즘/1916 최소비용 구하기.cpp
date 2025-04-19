#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define X first
#define Y second
#define endl "\n"

using namespace std;

const int INF = 0x3f3f3f3f;
int N, M;
vector<pair<int, int>> graph[1005];
int dist[1005];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
int st, en;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> M;
	for(int i = 0; i < M; i++) {
		int st, en, cost;
		cin >> st >> en >> cost;
		graph[st].push_back({cost, en});
	}
	cin >> st >> en;
	fill(dist, dist + 1005, INF);
	dist[st] = 0;
	pq.push({dist[st], st});

	while(!pq.empty()) {
		auto cur = pq.top(); pq.pop();

		if (dist[cur.Y] != cur.X) continue;
		for(auto nxt : graph[cur.Y]) {
			if (dist[nxt.Y] <= nxt.X + dist[cur.Y]) continue;
			dist[nxt.Y] = nxt.X + dist[cur.Y];
			pq.push({dist[nxt.Y], nxt.Y});
		}
 	}

	cout << dist[en];
}