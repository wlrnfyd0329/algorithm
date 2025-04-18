// dp인줄 알았지만 그냥 bfs를 순회하면 최단 거리를 구할 수 있다.
// dp로 풀려면 DAG 처럼 사이클이 생기면 안되는데 해당 문제는 사이클이 존재한다.

#include <iostream>
#include <vector>
#include <queue>
#define X first
#define Y second
#define endl "\n"

using namespace std;

int N, M, ans = 0;
int board[101];
int vis[101];
int bridge[101];
queue<int> q;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> M;
	int a, b;
	for(int i = 0; i < N; i++) {
		cin >> a >> b;
		bridge[a] = b;
	}
	for(int i = 0; i < M; i++) {
		cin >> a >> b;
		bridge[a] = b;
	}
	q.push(1);
	vis[1] = 1;
	while(!q.empty()) {
		int cur = q.front(); q.pop();

		for(int i = 1; i <= 6; i++) {
			int now = cur + i;
			if (now == 100) {
				cout << board[cur] + 1;
				return 0;
			}
			while(bridge[now] != 0) {
				now = bridge[now];
			}
			if (vis[now]) continue;
			vis[now] = 1;
			board[now] = board[cur] + 1;
			q.push(now);
		}
	}
}