#include <iostream>
#include <queue>

using namespace std;

int n, m, k;
struct Player {
	int x;
	int y;
	int dir;
	int stat;
	int gun;
};
vector<Player> player;
int board[25][25];
priority_queue<int> gun[25][25];

int point[35];

int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

void get_gun(int x, int y, int id) {
	if (!gun[x][y].empty()) {
		if (player[id].gun == 0) {
			player[id].gun = gun[x][y].top();
			gun[x][y].pop();
		}
		else {
			if (gun[x][y].top() > player[id].gun) {
				gun[x][y].push(player[id].gun);
				player[id].gun = gun[x][y].top();
				gun[x][y].pop();
			}
		}
	}
}

void result(int x, int y, int win, int lose) {
	point[win] += (player[win].stat + player[win].gun) - (player[lose].stat + player[lose].gun);
	if (player[lose].gun != 0) {
		gun[x][y].push(player[lose].gun);
		player[lose].gun = 0;
	}
	int lose_x = x + dx[player[lose].dir]; // x를 player[lose].x로 해서 예제가 틀렸어
	int lose_y = y + dy[player[lose].dir];
	while (lose_x < 0 || lose_x >= n || lose_y < 0 || lose_y >= n || board[lose_x][lose_y] > 0) {
		player[lose].dir = (player[lose].dir + 1) % 4;
		lose_x = x + dx[player[lose].dir];
		lose_y = y + dy[player[lose].dir];
	}
	player[lose].x = lose_x;
	player[lose].y = lose_y;
	board[lose_x][lose_y] = lose;
	get_gun(lose_x, lose_y, lose);

	player[win].x = x;
	player[win].y = y;
	board[x][y] = win;
	get_gun(x, y, win);
}

void move() {
	for (int i = 1; i <= m; i++) {
		board[player[i].x][player[i].y] = 0;
		int nx = player[i].x + dx[player[i].dir];
		int ny = player[i].y + dy[player[i].dir];
		if (nx < 0 || nx >= n || ny < 0 || ny >= n) {
			player[i].dir ^= 2;
			nx = player[i].x + dx[player[i].dir];
			ny = player[i].y + dy[player[i].dir];
		}
		if (board[nx][ny] == 0) { // 사람이 없을 때
			player[i].x = nx;
			player[i].y = ny;
			board[nx][ny] = i;
			get_gun(nx, ny, i);
		}
		else { // 사람이 있을 때
			if (player[i].stat + player[i].gun > player[board[nx][ny]].stat + player[board[nx][ny]].gun) {
				result(nx, ny, i, board[nx][ny]);
			}
			else if (player[i].stat + player[i].gun < player[board[nx][ny]].stat + player[board[nx][ny]].gun) {
				result(nx, ny, board[nx][ny], i);
			} 
			else {
				if (player[i].stat > player[board[nx][ny]].stat) {
					result(nx, ny, i, board[nx][ny]);
				}
				else {
					result(nx, ny, board[nx][ny], i);
				}
			}

		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int num; cin >> num;
			if (num != 0) gun[i][j].push(num);
		}
	}

	player = vector<Player>(m + 1);
	for (int i = 1; i <= m; i++) {
		int x, y, d, s;
		cin >> x >> y >> d >> s;
		board[x - 1][y - 1] = i;
		player[i] = { x - 1, y - 1, d, s, 0 };
	}

	while (k--) {
		move();
	}

	for (int i = 1; i <= m; i++) {
		cout << point[i] << " ";
	}
}