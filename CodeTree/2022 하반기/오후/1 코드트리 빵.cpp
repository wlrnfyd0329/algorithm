// 문제 조건에서 3번 행동에 행과 열에 대한 조건을 빼먹었다

#include <iostream>
#include <vector>
#include <string.h>
#include <queue>
#define X first
#define Y second

using namespace std;

int n, m, cnt;
int board[20][20];
int vis[40][20][20];
struct Human {
	int x;
	int y;
	int num;
	bool isArrive = false;
};
vector<Human> human;
queue<Human> arrive;
vector<pair<int, int>> comb;
vector<pair<int, int>> base_camp;

int dx[4] = { -1, 0, 0, 1 };
int dy[4] = { 0, -1, 1, 0 };

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> board[i][j];
		}
	}
	for (int i = 1; i <= m; i++) {
		int x, y;
		cin >> x >> y;
		comb.push_back({ x - 1, y - 1 });
	}
	cnt = 0;
	int time = -1;
	while (cnt != m) {
		time++;
		for (int i = 0; i < human.size(); i++) { // 1번 행동
			if (human[i].isArrive) continue;
			queue<pair<int, int>> q;
			int tvis[20][20];
			for (int i = 0; i < n; i++) {
				memset(tvis[i], 0, sizeof(int) * n);
			}
			pair<int, int> tb[20][20];
			tvis[human[i].x][human[i].y] = 1;
			q.push({ human[i].x, human[i].y });
			while (!q.empty()) {
				auto cur = q.front(); q.pop();
				if (cur.X == comb[i].X && cur.Y == comb[i].Y) {
					break;
				}
				for (int dir = 0; dir < 4; dir++) {
					int nx = cur.X + dx[dir];
					int ny = cur.Y + dy[dir];
					if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
					if (vis[0][nx][ny] || vis[i + 1][nx][ny] || tvis[nx][ny]) continue;
					tvis[nx][ny] = 1;
					tb[nx][ny] = { cur.X, cur.Y };
					q.push({ nx, ny });
				}
			}

			pair<int, int> tcomb = tb[comb[i].X][comb[i].Y];
			if (tcomb.X == human[i].x && tcomb.Y == human[i].y) {
				cnt++;
				human[i].isArrive = true;
				arrive.push({ comb[i].X, comb[i].Y, human[i].num });
			}
			else {
				while (!(tb[tcomb.X][tcomb.Y].X == human[i].x && tb[tcomb.X][tcomb.Y].Y == human[i].y)) {
					tcomb = tb[tcomb.X][tcomb.Y];
				}
				vis[i + 1][tcomb.X][tcomb.Y] = 1;
				human[i] = { tcomb.X, tcomb.Y, human[i].num };
			}
		}

		while (!arrive.empty()) { // 2번 행동
			auto cur = arrive.front(); arrive.pop();
			vis[0][cur.x][cur.y] = 1;
		}

		if (time < m) { // 3번 행동
			queue<pair<int, int>> q;
			int tvis[20][20];
			int targetx = 20, targety = 20, dist = 400;
			for (int i = 0; i < n; i++) {
				memset(tvis[i], 0, sizeof(int) * n);
			}
			tvis[comb[time].X][comb[time].Y] = 1;
			q.push({ comb[time].X, comb[time].Y });
			while (!q.empty()) {
				auto cur = q.front(); q.pop();
				if (board[cur.X][cur.Y] == 1) {
					if (dist > tvis[cur.X][cur.Y]) {
						dist = tvis[cur.X][cur.Y];
						targetx = cur.X;
						targety = cur.Y;
					}
					else if (dist == tvis[cur.X][cur.Y]) {
						if (targetx > cur.X) {
							targetx = cur.X;
							targety = cur.Y;
						}
						else if (targetx == cur.X) {
							if (targety > cur.Y) {
								targety = cur.Y;
							}
						}
					}
					else {
						break;
					}
				}
				for (int dir = 0; dir < 4; dir++) {
					int nx = cur.X + dx[dir];
					int ny = cur.Y + dy[dir];
					if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
					if (vis[0][nx][ny] || tvis[nx][ny]) continue;
					tvis[nx][ny] = tvis[cur.X][cur.Y] + 1;
					q.push({ nx, ny });
				}
			}
			human.push_back({ targetx, targety, time });
			vis[0][targetx][targety] = 1;
		}

	}
	cout << time + 1;
}
