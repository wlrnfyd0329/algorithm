// 트리의 지름을 구하는 건 임의의 한 정점에서 가장 먼 정점을 찾은 후,
// 그 먼 정점을 기준으로 가장 먼 정점이 트리의 지름이다.

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define X first
#define Y second

using namespace std;

int N;
vector<vector<pair<int, int>>> graph;
vector<int> dist;

void bfs(int st) {
	dist = vector<int> (N + 1, -1);
	queue<int> q;
	q.push(st);
	dist[st] = 0;

	while(!q.empty()) {
		int cur = q.front(); q.pop();

		for(auto nxt : graph[cur]) {
			if (dist[nxt.Y] >= 0) continue;
			dist[nxt.Y] = dist[cur] + nxt.X;
			q.push(nxt.Y);
		}
	}
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
	cin >> N;
	graph = vector<vector<pair<int, int>>> (N + 1);
	for(int i = 1; i <= N; i++) {
		int st, cost, en;
		cin >> st >> en;
		while(en != -1) {
			cin >> cost;
			graph[st].push_back({cost, en});
			cin >> en;
		}
	}

	bfs(1);
	bfs(max_element(dist.begin(), dist.end()) - dist.begin());
    sort(dist.begin(), dist.end(), greater());

	cout << dist[0];
}