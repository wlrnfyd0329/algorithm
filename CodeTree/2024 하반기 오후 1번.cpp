#include <iostream>
#include <deque>
#include <queue>
#include <algorithm>
#include <cmath>
#define endl "\n"
#define X first
#define Y second

using namespace std;

int N, M;
int board[55][55];
int vis[55][55];
pair<int, int> posi[55][55];
queue<pair<int, int>> q;
bool isArrive = false;
pair<int, int> snake;
pair<int, int> home;
deque<pair<int, int>> snake_turn;

int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

int solider_board[55][55];
int snake_board[55][55];
struct Solider {
	int x;
	int y;
	bool isDie = false;
} solider[305];

int solider_dx[4][3] = {
	{-1, -1, -1},
	{1, 1, 1},
	{-1, 0, 1},
	{-1, 0, 1}
};
int solider_dy[4][3] = {
	{-1, 0, 1},
	{-1, 0, 1},
	{-1, -1, -1},
	{1, 1, 1}
};

int move_dist;
int stun_solider;
int attack_solider;

void input() {
	cin >> N >> M;
	cin >> snake.X >> snake.Y >> home.X >> home.Y;
	for (int i = 0; i < M; i++) {
		cin >> solider[i].x >> solider[i].y;
		solider_board[solider[i].x][solider[i].y] = 1;
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
			vis[i][j] = 0;
		}
	}
	q.push({ snake.X, snake.Y });
	vis[snake.X][snake.Y] = 1;
}

void snake_move(int x, int y) {
	while (!q.empty()) {
		auto cur = q.front(); q.pop();
		if (cur.X == home.X && cur.Y == home.Y) {
			isArrive = true;
			break;
		}
		for (int i = 0; i < 4; i++) {
			int nx = cur.X + dx[i];
			int ny = cur.Y + dy[i];
			if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
			if (board[nx][ny] == 1 || vis[nx][ny]) continue;
			vis[nx][ny] = 1;
			posi[nx][ny] = { cur.X, cur.Y };
			q.push({ nx, ny });
		}
	}
	
	if (!isArrive) return;
	home = posi[home.X][home.Y];
	while (!(home.X == snake.X && home.Y == snake.Y)) {
		snake_turn.push_front(home);
		home = posi[home.X][home.Y];
	}
}

void snake_turning() {
	// first는 메두사가 보면 -1, 안보면 1
	// 0을 바라보면 2만 보는걸로 1을 바라보면 1만 안보게 2를 바라보면 0만 보는 걸로 계산한다
	pair<int, int> snake_watch[55][55]; 
	stun_solider = -1;
	int cnt = 0;
	for (int dir = 0; dir < 4; dir++) {
		fill(snake_watch[0], snake_watch[55], 0);
		for (int i = 0; i < 3; i++) {
			int nx = snake.X + solider_dx[dir][i];
			int ny = snake.Y + solider_dy[dir][i];
			if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
			snake_watch[nx][ny] = { -1, i };
			q.push({nx, ny});
		}
		while (!q.empty()) {
			auto cur = q.front(); q.pop();
			for (int i = 0; i < 3; i++) {
				int nx = cur.X + solider_dx[dir][i];
				int ny = cur.Y + solider_dy[dir][i];
				if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
				if (snake_watch[cur.X][cur.Y].X == 0 || solider_board[cur.X][cur.Y] == 1) {
					if (snake_watch[cur.X][cur.Y].Y == 1) {
						if (i == 2) {
							if (snake_watch[nx][ny].X == 0) {
								snake_watch[nx][ny] = { -1, snake_watch[cur.X][cur.Y].Y };
							}
						}
						else {
							snake_watch[nx][ny] = { 1, snake_watch[cur.X][cur.Y].Y };
						}
					}
					else if (snake_watch[cur.X][cur.Y].Y == 2) {
						if (i == 0) {
							if (snake_watch[nx][ny].X == 0) {
								snake_watch[nx][ny] = { -1, snake_watch[cur.X][cur.Y].Y };
							}
						}
						else {
							snake_watch[nx][ny] = { 1, snake_watch[cur.X][cur.Y].Y };
						}
					}
					else {
						if (i == 1) {
							snake_watch[nx][ny] = { 1, snake_watch[cur.X][cur.Y].Y };
						}
						else {
							if (snake_watch[nx][ny].X == 0) {
								snake_watch[nx][ny] = { -1, snake_watch[cur.X][cur.Y].Y };
							}
						}
					}
				}
				else {
					if (snake_watch[nx][ny].X == 0) {
						snake_watch[nx][ny] = { -1, snake_watch[cur.X][cur.Y].Y };
					}
				}
			}
		}

		if (stun_solider < cnt) {
			stun_solider = cnt;
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					snake_board[i][j] = snake_watch[i][j].X;
				}
			}
		}
	}
}

void solider_move() {
	fill(solider_board[0], solider_board[55], 0);
	move_dist = 0;
	attack_solider = 0;
	for (int i = 0; i < M; i++) {
		if (snake_board[solider[i].x][solider[i].y] == -1) continue;
		int dist = abs(snake.X - solider[i].x) + abs(snake.Y - solider[i].y);
		for (int dir = 0; dir < 4; dir++) {
			int nx = solider[i].x + dx[dir];
			int ny = solider[i].y + dy[dir];
			if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
			if () // 메두사가 바라보는 곳으로 가는지 체크, 메두사가 있는 곳으로 가는지 체크
			if (dist < abs(snake.X - nx) + abs(snake.Y - ny)) continue;
			solider[i].x = nx;
			solider[i].y = ny;
			break;
		}

		dist = abs(snake.X - solider[i].x) + abs(snake.Y - solider[i].y);
		for (int dir = 0; dir < 4; dir++) {
			int nx = solider[i].x + dx[(dir + 2) % 4];
			int ny = solider[i].y + dy[(dir + 2) % 4];
			if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
			if (dist < abs(snake.X - nx) + abs(snake.Y - ny)) continue;
			solider[i].x = nx;
			solider[i].y = ny;
			break;
		}
	}
}

void turn() {
	for (auto k : snake_turn) {
		snake = k;
		snake_turning();
		solider_move();
		cout << move_dist << " " << stun_solider << " " << attack_solider << endl;
	}
	cout << 0;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	input();
	snake_move(snake.X, snake.Y);
	if (!isArrive) {
		cout << -1;
	}
	else {
		turn();
	}

}