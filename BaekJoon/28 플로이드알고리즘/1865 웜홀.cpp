// 음수의 가중치를 가진 것을 해결할 수 있는 알고리즘은 플로이드 워셜이다.
// 처음에는 dfs로 순회하면서 작아지는 노드를 찾으려 했지만, 
// vis처리를 할 수 없기에 무한 루프에 돌 것이라 판단되어 하지 않았다.

#include <iostream>
#include <algorithm>
#define endl "\n"

using namespace std;

const int INF = 0x3f3f3f3f;
int T;
int board[505][505];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
	cin >> T;
	for(int tc = 1; tc <= T; tc++) {
		int n, m, w;
		fill(board[0], board[504], INF);
		cin >> n >> m >> w;
		for(int i = 0; i < m; i++) {
			int s, e, t;
			cin >> s >> e >> t;
			board[s][e] = min(board[s][e], t);
			board[e][s] = min(board[e][s], t);
		}
		for(int i = 0; i < w; i++) {
			int s, e, t;
			cin >> s >> e >> t;
			board[s][e] = min(board[s][e], -t);
		}

		for(int k = 1; k <= n; k++) {
			for(int i = 1; i <= n; i++) {
				for(int j = 1; j <= n; j++) {
					if (board[i][j] > board[i][k] + board[k][j]) {
						board[i][j] = board[i][k] + board[k][j];
					}
				}
			}
		}

		bool isDo = false;
		for(int i = 1; i <= n; i++) {
			if (board[i][i] < 0) {
				isDo = true;
				break;
			}
		}

		cout << (isDo ? "YES" : "NO") << endl;
	}
}