// 도둑이 움직이지 않을 때도 vis에 값 표기를 안해줌...
// 동시에 움직일 때는 새로운 배열에 넣는데, 업데이트시 표기를 안해줬다..

#include <iostream>

using namespace std;

int n, m, h, k, turn, ans;
int board[100][100];
int pb[7][7];
int dx[4] = { -1, 0, 1, 0 }; // 상 우 하 좌
int dy[4] = { 0, 1, 0, -1 };

struct Thief {
	int x;
	int y;
	int dir;
	bool isCatch = false;
} thief[10'000];

struct Police {
	int x;
	int y;
	int dir; // 상 우 하 좌로 이동하는데 시계 방향이면 +1씩 증가, 반시계면 -1씩 증가
	int dist; // 이동하는 거리인데 0이 되면 바로 방향 틀기
	bool flag; // 참이면 시계 방향 이동 거짓이면 반시계 이동
	int dist_record = 1;
	int flag_cnt = 2; // 방향을 두번 틀면 dist를 변화 시켜야 함

	void move() {
		// 해당하는 방향으로 이동하는데, 이동방향이 틀어지는 지점이라면 방향을 바로 튼다
		// (0, 0)이나 정중앙에 도달하면 방향을 바로 틀어줘야 함 dir^2 하면 됨
		pb[x][y] = 0;
		x += dx[dir];
		y += dy[dir];
		if (x == 0 && y == 0) {
			dir ^= 2;
			flag = !flag;
			dist = dist_record - 1;
			flag_cnt = 1;
		}
		else if (x == n / 2 && y == n / 2) {
			dir ^= 2;
			flag = !flag;
			dist = 1;
			flag_cnt = 2;
		}
		else {
			if (--dist == 0) {
				rotate();
			}
		}
		find();
		pb[x][y] = dir + 1;
	}

	void find() {
		// 술래의 시야는 항상 자기 위치를 포함해서 3칸
		// 나무가 있으면 도망자를 못잡음
		// 잡으면 잡은 수 * 현재 턴
		int cnt = 0;
		int nx = x - dx[dir];
		int ny = y - dy[dir];
		for (int i = 0; i < 3; i++) {
			nx += dx[dir];
			ny += dy[dir];
			if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
			if (board[nx][ny] > 0) {
				for (int j = 1; j <= m; j++) {
					if (thief[j].isCatch) continue;
					if (thief[j].x == nx && thief[j].y == ny) {
						thief[j].isCatch = true;
						cnt++;
						board[nx][ny] = 0;
					}
				}
			}
		}
		ans += turn * cnt;
	}

	void rotate() {
		if (flag) {
			if (++dir > 3) dir = 0;
			if (--flag_cnt == 0) {
				flag_cnt = 2;
				++dist_record;
			}
			dist = dist_record;
		}
		else {
			if (--dir < 0) dir = 3;
			if (--flag_cnt == 0) {
				flag_cnt = 2;
				--dist_record;
			}
			dist = dist_record;
		}
	}
} police;

inline int cal_dist(int x1, int y1, int x2, int y2) {
	return abs(x1 - x2) + abs(y1 - y2);
}

void thief_move() {
	// 격자 안벗어나면 술래 있는 곳에 안감, 술래 없으면 이동함(나무 상관 없음)
	// 격자 벗어나면 먼저 방향을 틀고 한칸 움직이는데, 해당 위치에 술래가 없으면 1칸 이동
	// 격자 벗어나면 방향만 바꾸고 똑같이 하면 되겠당
	int vis[100][100] = {0, };
	for (int i = 1; i <= m; i++) {
		if (thief[i].isCatch || cal_dist(police.x, police.y, thief[i].x, thief[i].y) > 3) continue;
		int nx = thief[i].x + dx[thief[i].dir];
		int ny = thief[i].y + dy[thief[i].dir];
		if (nx < 0 || nx >= n || ny < 0 || ny >= n) {
			thief[i].dir ^= 2;
			nx = thief[i].x + dx[thief[i].dir];
			ny = thief[i].y + dy[thief[i].dir];
		}
		if (nx == police.x && ny == police.y) {
			vis[thief[i].x][thief[i].y] = 1; // 도둑이 움직이지 않을 때 사라짐..
			continue;
		}
		// 나무가 있는 곳에 들어갈 때
		// 나무가 있던 곳에서 나올 때
		// 그냥 움직일 때
		vis[nx][ny] = 1;
		thief[i].x = nx;
		thief[i].y = ny;
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (board[i][j] < 0) continue;
			board[i][j] = vis[i][j];
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m >> h >> k;

	police = { n / 2, n / 2, 0, 1, true };
	pb[n / 2][n / 2] = 1;

	for (int i = 1; i <= m; i++) {
		int x, y, d; cin >> x >> y >> d;
		thief[i] = { x - 1, y - 1, d };
		board[x - 1][y - 1] = 1; // board가 1이면 도둑이 있으니까 누군지 찾아야 함
	}

	for (int i = 0; i < h; i++) {
		int x, y; cin >> x >> y;
		board[x - 1][y - 1] = -1; // board의 -1이면 나무니까 신경 무조건 안씀
	}

	for (turn = 1; turn <= k; turn++) {
		// 도망자 움직임
		thief_move();
		// 술래 움직임
		police.move();
	}

	cout << ans;
}