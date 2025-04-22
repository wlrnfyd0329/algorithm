#include <iostream>
#include <algorithm>
#include <vector>
#define X first
#define Y second

using namespace std;

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
	int n; cin >> n;
	graph = vector<vector<pair<int, int>>> (n + 1);
	for(int i = 1; i < n; i++) {
		int st, en, cost;
		cin >> st >> en >> cost;
		graph[st].push_back({cost, en});
		graph[en].push_back({cost, st});
	}

	vis = vector<bool> (n + 1);
	vis[1] = 1;
	max_dist = 0;
	dfs(1, 0);

	vis = vector<bool> (n + 1);
	vis[max_node] = 1;
	max_dist = 0;
	dfs(max_node, 0);

	cout << max_dist;
}