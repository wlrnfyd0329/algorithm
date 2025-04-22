// 트리의 지름을 구하는 건 임의의 한 정점에서 가장 먼 정점을 찾은 후,
// 그 먼 정점을 기준으로 가장 먼 정점이 트리의 지름이다.

#include <iostream>
#include <vector>
#define X first
#define Y second

using namespace std;

int N;
vector<vector<pair<int, int>>> graph;
vector<bool> vis;
int max_node, max_dist;


void dfs(int cur, int dist) {
	if (max_dist < dist) {
		max_dist = dist;
		max_node = cur;
	}

	for(auto nxt : graph[cur]) {
		if (vis[nxt.Y]) continue;
		vis[nxt.Y] = 1;
		dfs(nxt.Y, dist + nxt.X);
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

	max_dist = 0;
	vis = vector<bool> (N + 1);
	vis[1] = 1;
	dfs(1, 0);

	max_dist = 0;
	vis = vector<bool> (N + 1);
	vis[max_node] = 1;
	dfs(max_node, 0);

	cout << max_dist;
}