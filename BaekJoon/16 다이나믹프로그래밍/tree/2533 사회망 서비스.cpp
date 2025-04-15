// 얼리어답터이거나 일반인이거나 state가 독립적이다.
// 트리 dp 문제다.
// dp[node][0] : 해당 노드가 얼리 어답터인 경우, dp[node][1] : 일반인인 경우
// 값은 본인 노드 + 해당 노드의 모든 자식노드 중에 최소 얼리어답터 수이다.

// 그래프에 대해 풀기 어려운 문제들이 트리에 대해서는 쉽게 풀리는 경우가 많기 때문에,
// 주어진 그래프가 '루트 없는 트리'인지 파악해보자 (사이클이 없이 연결된 그래프는 루트 없는 트리라 생각해도 좋다)

#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> graph;
vector<bool> vis;
vector<int[2]> dp;

void find(int node) {
	dp[node][0] = 1;

	for (auto nxt : graph[node]) {
		if (vis[nxt]) continue;
		vis[nxt] = 1;
		find(nxt);
		dp[node][0] += min(dp[nxt][0], dp[nxt][1]); // 본인이 얼리어답터라면 자식은 뭐든 상관 없으니까 문제 조건에 맞게 최소를 찾아준다.
		dp[node][1] += dp[nxt][0]; // 본인이 일반인이라면 자식은 얼리어답터여야 한다.
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n; cin >> n;
	graph = vector<vector<int>>(n + 1);
	vis = vector<bool> (n + 1);
	dp = vector<int[2]>(n + 1);
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}

	vis[1] = 1;
	find(1);
	cout << min(dp[1][0], dp[1][1]);
}