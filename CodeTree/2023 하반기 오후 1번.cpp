#include <iostream>
#include <cmath>
#define endl "\n"
#define X first
#define Y second

using namespace std;

int N, M, P, C, D;
pair<int, int> ru;
struct Santa {
	int x; 
	int y;
	int score = 0;
	int isStun = 0;
	bool isLose = false;
} santa[35];

int board[55][55];
int rdx[8] = { 1, 1, 1, -1, -1, -1, 0, 0 };
int rdy[8] = { 1, -1, 0, 1, -1, 0, 1, -1 };
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

void input() {
	cin >> N >> M >> P >> C >> D;
	cin >> ru.X >> ru.Y;
	board[ru.X][ru.Y] = -1;
	for (int i = 0; i < P; i++) {
		int idx;
		cin >> idx;
		cin >> santa[idx].x >> santa[idx].y;
		board[santa[idx].x][santa[idx].y] = idx;
	}
}

void interaction() {

}

void move_ru() {
	int idx, dir;
	int dist = 20000;
	// 제일 가까운 산타 구하기
	for (int i = 1; i <= P; i++) {
		if (santa[i].isLose) continue;
		int tdist = pow(ru.X - santa[i].x, 2) + pow(ru.Y - santa[i].y, 2);
		if (dist > tdist) {
			dist = tdist;
			idx = i;
		}
		else if (dist == tdist) {
			if (santa[idx].x < santa[i].x) {
				idx = i;
			}
			else if (santa[idx].x == santa[i].x) {
				if (santa[idx].y < santa[i].y) {
					idx = i;
				}
			}
		}
	}
	// 루돌프 이동
	if (santa[idx].x > ru.X) {
		if (santa[idx].y > ru.Y) {
			dir = 0;
		}
		else if (santa[idx].y < ru.Y) {
			dir = 1;
		}
		else {
			dir = 2;
		}
	}
	else if (santa[idx].x < ru.X) {
		if (santa[idx].y > ru.Y) {
			dir = 3;
		}
		else if (santa[idx].y < ru.Y) {
			dir = 4;
		}
		else {
			dir = 5;
		}
	}
	else {
		if (santa[idx].y > ru.Y) {
			dir = 6;
		}
		else {
			dir = 7;
		}
	}

	board[ru.X][ru.Y] = 0;
	ru.X += rdx[dir];
	ru.Y += rdy[dir];

	if (board[ru.X][ru.Y] > 0) {
		int idx = board[ru.X][ru.Y];
		board[santa[idx].x][santa[idx].y] = -1;
		int nx = ru.X + rdx[dir] * C;
		int ny = ru.Y + rdy[dir] * C;
		santa[idx].x = nx;
		santa[idx].y = ny;
		santa[idx].score += C;
		santa[idx].isStun = 2;
		if (nx <= 0 || nx > N || ny <= 0 || ny > N) {
			santa[idx].isLose = true;
			return;
		}
		while (board[nx][ny]) {
			int origin_idx = idx;
			idx = board[nx][ny];
			board[nx][ny] = origin_idx;
			nx += rdx[dir];
			ny += rdy[dir];
			if (nx <= 0 || nx > N || ny <= 0 || ny > N) {
				santa[idx].isLose = true;
				break;
			}
			santa[idx].x = nx;
			santa[idx].y = ny;
		}
		if (!santa[idx].isLose) {
			board[nx][ny] = idx;
		}
	}
	else {
		board[ru.X][ru.Y] = -1;
	}
}

void move_santa() {
	// 산타 움직임
	for (int i = 1; i <= P; i++) {
		if (santa[i].isLose) continue;
		if (santa[i].isStun) {
			santa[i].isStun--;
			continue;
		}
		int dist = pow(ru.X - santa[i].x, 2) + pow(ru.Y - santa[i].y, 2);
		int min_dir = -1;
		for (int dir = 0; dir < 4; dir++) {
			int nx = santa[i].x + dx[dir];
			int ny = santa[i].y + dy[dir];
			if (nx <= 0 || nx > N || ny <= 0 || ny > N) continue;
			if (board[nx][ny] > 0) continue;
			int tdist = pow(ru.X - nx, 2) + pow(ru.Y - ny, 2);
			if (dist > tdist) {
				dist = tdist;
				min_dir = dir;
			}
		}
		if (min_dir == -1) continue;
		int nx = santa[i].x + dx[min_dir];
		int ny = santa[i].y + dy[min_dir];
		
		if (board[nx][ny] == 0) {
			board[santa[i].x][santa[i].y] = 0;
			board[nx][ny] = i;
			santa[i].x = nx;
			santa[i].y = ny;
		}
		else {
			int idx = i;
			board[santa[i].x][santa[i].y] = 0;
			nx -= dx[min_dir] * D;
			ny -= dy[min_dir] * D;
			santa[i].x = nx;
			santa[i].y = ny;
			santa[i].score += D;
			santa[i].isStun = 1;
			if (nx <= 0 || nx > N || ny <= 0 || ny > N) {
				santa[i].isLose = true;
				continue;
			}
			while (board[nx][ny]) {
				int origin_idx = idx;
				idx = board[nx][ny];
				board[nx][ny] = origin_idx;
				nx -= dx[min_dir];
				ny -= dy[min_dir];
				if (nx <= 0 || nx > N || ny <= 0 || ny > N) {
					santa[idx].isLose = true;
					break;
				}
				santa[idx].x = nx;
				santa[idx].y = ny;
			}
			if (!santa[idx].isLose) {
				board[nx][ny] = idx;
			}
		}
	}
}

void play() {
	for (int i = 0; i < M; i++) {
		move_ru();
		move_santa();
		int isDone = true;
		for (int i = 1; i <= P; i++) {
			if (!santa[i].isLose) {
				isDone = false;
				santa[i].score++;
			}
		}

		if (isDone) break;
	}

	for (int i = 1; i <= P; i++) {
		cout << santa[i].score << " ";
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	input();
	play();
}