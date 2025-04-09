// 꼬리 잡기라면 1과 3이 이어져있는 경우도 있다.
// 꼬리의 앞 뒤가 바뀌는 것도 잘못 작동했다. 1, 3은 2만 따라가게 해야지 제대로 된 범위가 나온다.
// 문제 꼼꼼히 읽자... 범위 시작이 잘못되어서 틀렸다.

#include <iostream>
#include <vector>
#include <queue>
#define X first
#define Y second

using namespace std;

int n, m, k, ans;
int board[25][25]; // 0은 빈칸, 1은 머리 사람, 2는 머리사람과 꼬리사람이 아닌 나머지, 3은 꼬리 사람, 4는 이동 선
vector<pair<int, int>> heads;

int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };

struct Node {
	int x;
	int y;
	int cnt;
};

void move() {
	for (int i = 0; i < heads.size(); i++) {
		queue<pair<int, int>> q;
		q.push(heads[i]);
		int tboard[25][25] = { 0, };

		while (!q.empty()) {
			auto cur = q.front(); q.pop();

			int grade = board[cur.X][cur.Y];
			for (int dir = 0; dir < 4; dir++) {
				int nx = cur.X + dx[dir];
				int ny = cur.Y + dy[dir];
				if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
				if (board[nx][ny] == 0) continue;
				if (grade == 1) {
					if (board[nx][ny] == 2) {
						q.push({ nx, ny });
					}
					else {
						tboard[nx][ny] = board[cur.X][cur.Y];
						board[cur.X][cur.Y] = -1;
						heads[i] = { nx ,ny };
					}
				}
				else if (grade == 2) {
					if (board[nx][ny] == 2 || board[nx][ny] == 3) {
						q.push({ nx, ny });
					}
					else {
						tboard[nx][ny] = board[cur.X][cur.Y];
						board[cur.X][cur.Y] = -2;
					}
				}
				else {
					if (board[nx][ny] == -2) {
						tboard[nx][ny] = board[cur.X][cur.Y];
						board[cur.X][cur.Y] = 4;
					}
				}
			}
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (tboard[i][j] != 0) {
					board[i][j] = tboard[i][j];
				}
			}
		}
	}
}

int find_grade(int x, int y) {
	int cnt = 0;
	pair<int, int> start = { -1, -1 };
	pair<int, int> end = { -1, -1 };
	queue<Node> q;
	int vis[25][25] = { 0, };
	q.push({ x, y, 1 });
	vis[x][y] = 1;

	while (!q.empty()) {
		auto cur = q.front(); q.pop();

		if (board[cur.x][cur.y] == 1) {
			start = { cur.x, cur.y };
			cnt = cur.cnt;
		}
		else if (board[cur.x][cur.y] == 3) {
			end = { cur.x, cur.y };
		}

		for (int dir = 0; dir < 4; dir++) {
			int nx = cur.x + dx[dir];
			int ny = cur.y + dy[dir];
			if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
			if (board[nx][ny] == 0 || board[nx][ny] == 4 || vis[nx][ny]) continue;
			if (board[cur.x][cur.y] == 1 || board[cur.x][cur.y] == 3) {
				if (board[nx][ny] == 2) {
					vis[nx][ny] = 1;
					q.push({ nx, ny, cur.cnt + 1 });
				}
			}
			else {
				vis[nx][ny] = 1;
				q.push({ nx, ny, cur.cnt + 1 });
			}
		}
	}

	board[start.X][start.Y] = 3;
	board[end.X][end.Y] = 1;
	for (int i = 0; i < heads.size(); i++) {
		if (heads[i] == start) {
			heads[i] = end;
			break;
		}
	}
	return cnt * cnt;
}

void turn() {
	while (1) {
		for (int i = 0; i < n; i++) {
			move();
			for (int j = 0; j < n; j++) {
				if (board[i][j] == 1 || board[i][j] == 2 || board[i][j] == 3) {
					ans += find_grade(i, j);
					break;
				}
			}
			if (--k == 0) {
				cout << ans;
				return;
			}
		}

		for (int j = 0; j < n; j++) {
			move();
			for (int i = n - 1; i >= 0; i--) {
				if (board[i][j] == 1 || board[i][j] == 2 || board[i][j] == 3) {
					ans += find_grade(i, j);
					break;
				}
			}
			if (--k == 0) {
				cout << ans;
				return;
			}
		}

		for (int i = n - 1; i >= 0; i--) {
			move();
			for (int j = n - 1; j >= 0; j--) {
				if (board[i][j] == 1 || board[i][j] == 2 || board[i][j] == 3) {
					ans += find_grade(i, j);
					break;
				}
			}
			if (--k == 0) {
				cout << ans;
				return;
			}
		}

		for (int j = n - 1; j >= 0; j--) {
			move();
			for (int i = 0; i < n; i++) {
				if (board[i][j] == 1 || board[i][j] == 2 || board[i][j] == 3) {
					ans += find_grade(i, j);
					break;
				}
			}
			if (--k == 0) {
				cout << ans;
				return;
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m >> k;
	ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> board[i][j];
			if (board[i][j] == 1) {
				heads.push_back({ i, j });
			}
		}
	}

	turn();
}
