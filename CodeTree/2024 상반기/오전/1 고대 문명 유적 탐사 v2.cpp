#include <iostream>
#include <queue>
#include <vector>
#include <string.h>

using namespace std;

int K, M;
int board[5][5];
queue<int> piece;

void rotate(int x, int y, int cnt, int arr[5][5]) {
	for (int k = 0; k < cnt; k++) {
		int temp[3];
		for (int i = 1; i >= -1; i--) {
			temp[i + 1] = arr[x - 1][y + i];
		}
		for (int i = 1; i >= -1; i--) {
			arr[x - 1][y + i] = arr[x - i][y - 1];
		}
		for (int i = 1; i >= -1; i--) {
			arr[x - i][y - 1] = arr[x + 1][y - i];
		}
		for (int i = 1; i >= -1; i--) {
			arr[x + 1][y - i] = arr[x + i][y + 1];
		}
		for (int i = 1; i >= -1; i--) {
			arr[x + i][y + 1] = temp[i + 1];
		}
	}
}

int score(int arr[5][5], bool isBlank) {
	int ans = 0;
	int vis[5][5] = { 0, };
	int dx[4] = { 1, 0, -1, 0 };
	int dy[4] = { 0, 1, 0, -1 };
	queue<pair<int, int>> q;
	vector<pair<int, int>> v;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (vis[i][j]) continue;
			vis[i][j] = 1;
			q.push({ i, j });
			v.clear();
			v.push_back({ i, j });
			while (!q.empty()) {
				auto cur = q.front(); q.pop();
				for (int dir = 0; dir < 4; dir++) {
					int nx = cur.first + dx[dir];
					int ny = cur.second + dy[dir];
					if (nx < 0 || nx >= 5 || ny < 0 || ny >= 5) continue;
					if (arr[nx][ny] != arr[cur.first][cur.second] || vis[nx][ny]) continue;
					vis[nx][ny] = 1;
					q.push({ nx, ny });
					v.push_back({ nx, ny });
				}
			}
			if (v.size() >= 3) {
				if (isBlank) {
					for (auto k : v) {
						arr[k.first][k.second] = 0;
					}
				}
				ans += v.size();
			}
		}
	}

	return ans;
}

bool search() {
	int x, y, dir = 4, sc = 0;
	int temp[5][5];
	for (int j = 1; j < 4; j++) {
		for (int i = 1; i < 4; i++) {
			memcpy(temp, board, sizeof(board));
			for (int k = 1; k < 4; k++) {
				rotate(i, j, 1, temp);
				int tsc = score(temp, false);
				if (sc < tsc) {
					sc = tsc;
					x = i;
					y = j;
					dir = k;
				}
				else if (sc == tsc) {
					if (dir > k) {
						x = i;
						y = j;
						dir = k;
					}
				}
			}
		}
	}

	if (sc == 0) return false;
	rotate(x, y, dir, board);
	return true;
}

void filling() {
	for (int j = 0; j < 5; j++) {
		for (int i = 4; i >= 0; i--) {
			if (board[i][j] == 0) {
				board[i][j] = piece.front(); piece.pop();
			}
		}
	}
}

void turn() {
	for (int i = 0; i < K; i++) {
		int ans = 0;
		if (!search()) return;
		while (1) {
			int tans = score(board, true);
			if (tans == 0) break;
			ans += tans;
			filling();
		}
		cout << ans << " ";
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> K >> M;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cin >> board[i][j];
		}
	}
	for (int i = 0; i < M; i++) {
		int num; cin >> num;
		piece.push(num);
	}
	turn();
}