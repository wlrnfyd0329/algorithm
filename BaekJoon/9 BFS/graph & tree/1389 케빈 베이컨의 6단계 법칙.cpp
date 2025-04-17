// 플로이드 워셜과 다익스트라를 사용해도 된다.

#include <iostream>
#include <vector>
#include <queue>
#define endl "\n"

using namespace std;

int N, M, ans, ans_v = 1234567891;
vector<int> graph[105];

int cal(int idx) {
	int depth[105] = {0, };
	queue<int> q;
	depth[idx]++;
	q.push(idx);
	while(!q.empty()) {
		int cur = q.front(); q.pop();

		for(auto nxt : graph[cur]) {
			if (depth[nxt] > 0) continue;
			depth[nxt] = depth[cur] + 1;
			q.push(nxt);
		}
	}

	int sum = 0;
	for(int i = 1; i <= N; i++) {
		sum += depth[i] - 1;
	}
	return sum;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int a, b; cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	for(int i = 1; i <= N; i++) {
		int value = cal(i);
		if (ans_v > value) {
			ans_v = value;
			ans = i;
		}
	}

	cout << ans;
}