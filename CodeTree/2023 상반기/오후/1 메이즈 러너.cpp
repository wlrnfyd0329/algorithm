// 사람이 겹친 것을 따로 표기를 안해줘서 틀렸다
// 나는 겹친 걸 비트로 표현했는데, unordered_set으로 할 수 잇음

#include <iostream>
#include <cmath>
#include <queue>
#include <vector>
#include <tuple>
#define endl "\n"
#define X first
#define Y second

using namespace std;

int N, M, K, ans;
pair<int, int> arrive;
int board[15][15]; // 0은 빈칸, 양수는 사람, -10은 출구, -1 ~ -9 나머지는 벽
struct Person {
	int x;
	int y;
	bool isEscape;
};
vector<Person> person;

int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };

inline int cal_dist(int x1, int y1, int x2, int y2) {
	return abs(x1 - x2) + abs(y1 - y2);
}

inline int cal_len(int x1, int y1, int x2, int y2) {
	return max(abs(x1 - x2), abs(y1 - y2));
}

pair<int, int> cal_position(int x1, int y1, int x2, int y2, int len) {
	int x, y;
	if (x1 < x2) {
		if (y1 < y2) {
			x = x2;
			y = y2;
		}
		else {
			x = x2;
			y = y1;
		}
	}
	else {
		if (y1 < y2) {
			x = x1;
			y = y2;
		}
		else {
			x = x1;
			y = y1;
		}
	}

	x -= len;
	y -= len;
	if (x <= 0) x = 1;
	if (y <= 0) y = 1;
	return { x, y };
}

void rotate(int x, int y, int len) {
	int temp[15][15];

	for (int i = 0; i <= len; i++) {
		for (int j = 0; j <= len; j++) {
			temp[i][j] = board[x + len - j][y + i];
			if (temp[i][j] < 0) {
				if (temp[i][j] == -10) arrive = { x + i, y + j };
				else temp[i][j]++;
			}
			if (temp[i][j] > 0) {
				for (int k = 0; k < person.size(); k++) {
					if (person[k].isEscape) continue;
					if ((temp[i][j] & (1 << k)) > 0) {
						person[k] = { x + i, y + j, false };
					}
				}
			}
		}
	}


	for (int i = 0; i <= len; i++) {
		for (int j = 0; j <= len; j++) {
			board[x + i][y + j] = temp[i][j];
		}
	}
}

void move() {
	int r = 15, c = 15, dist = 200;
	for (int i = 0; i < person.size(); i++) {
		if (person[i].isEscape) continue;
		for (int dir = 0; dir < 4; dir++) {
			int nx = person[i].x + dx[dir];
			int ny = person[i].y + dy[dir];
			if (nx <= 0 || nx > N || ny <= 0 || ny > N) continue;
			if (board[nx][ny] == -10) {
				person[i].isEscape = true;
				ans++;
				board[person[i].x][person[i].y] ^= (1 << i);
				if (--M == 0) return;
				break;
			}
			if (board[nx][ny] < 0) continue;
			if (cal_dist(nx, ny, arrive.X, arrive.Y) < cal_dist(person[i].x, person[i].y, arrive.X, arrive.Y)) {
				board[person[i].x][person[i].y] ^= (1 << i);
				board[nx][ny] |= (1 << i);
				person[i].x = nx;
				person[i].y = ny;
				ans++;
				break;
			}
		}

		if (person[i].isEscape) continue;

		if (cal_len(person[i].x, person[i].y, arrive.X, arrive.Y) < dist) {
			dist = cal_len(person[i].x, person[i].y, arrive.X, arrive.Y);
			tie(r, c) = cal_position(person[i].x, person[i].y, arrive.X, arrive.Y, dist);
		}
		else if (cal_len(person[i].x, person[i].y, arrive.X, arrive.Y) == dist) {
			pair<int, int> tposition = cal_position(person[i].x, person[i].y, arrive.X, arrive.Y, dist);
			if (tposition.X < r) {
				tie(r, c) = tposition;
			}
			else if (tposition.X == r) {
				if (tposition.Y < c) {
					c = tposition.Y;
				}
			}
		}
	}
	rotate(r, c, dist);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> board[i][j];
			if (board[i][j] != 0) board[i][j] = -board[i][j];
		}
	}

	person = vector<Person>(M);
	for (int i = 0; i < M; i++) {
		int x, y;
		cin >> x >> y;
		board[x][y] |= (1<<i);
		person[i] = { x, y, false };
	}

	int x, y;
	cin >> x >> y;
	board[x][y] = -10;
	arrive = { x, y };

	while (K--) {
		move();
		if (M == 0) break;
	}

	cout << ans << endl << arrive.X << " " << arrive.Y;
}