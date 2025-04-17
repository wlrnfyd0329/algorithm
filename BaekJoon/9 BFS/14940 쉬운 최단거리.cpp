#include <iostream>
#include <vector>
#include <queue>
#define X first
#define Y second
#define endl "\n"

using namespace std;

int n, m;
int board[1005][1005];
int vis[1005][1005];
queue<pair<int, int>> q;

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			cin >> board[i][j];
			if (board[i][j] == 2) {
				vis[i][j] = 1;
				q.push({i, j});
				board[i][j] = 0;
			}
		}
	}

	while(!q.empty()) {
		auto cur = q.front(); q.pop();
		
		for(int dir = 0; dir < 4; dir++) {
			int nx = cur.X + dx[dir];
			int ny = cur.Y + dy[dir];
			if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
			if (board[nx][ny] == 0 || vis[nx][ny]) continue;
			vis[nx][ny] = 1;
			board[nx][ny] = board[cur.X][cur.Y] + 1;
			q.push({nx, ny});
		}
	}

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			if (board[i][j] == 1 && vis[i][j] == 0) cout << -1 << " ";
			else cout << board[i][j] << " ";
		}
		cout << endl;
	}
}