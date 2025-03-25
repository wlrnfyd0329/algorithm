#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int L, N, Q, score = 0;
int board[45][45];
int shield[45][45];
int tshield[45][45];
int health[35];
int thealth[35];
int vis[35];

struct Knight {
	int r;
	int c;
	int h;
	int w;
	int k;
};
vector<Knight> knight;

int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

bool move(int n, int dir) {
	if (knight[n].k <= health[n] || vis[n]) return true;
	int trap = 0;
	bool isMove = true;
	vis[n] = 1;
	for (int i = 0; i < knight[n].h; i++) {
		for (int j = 0; j < knight[n].w; j++) {
			int nx = knight[n].r + i + dx[dir];
			int ny = knight[n].c + j + dy[dir];
			if (nx <= 0 || nx > L || ny <= 0 || ny > L || board[nx][ny] == 2) return false;
			if (board[nx][ny] == 1) trap++;
			if (shield[nx][ny] != 0 && !vis[shield[nx][ny]]) isMove = move(shield[nx][ny], dir);
			if (!isMove) return false;
			tshield[nx][ny] = n;
		}
	}

	thealth[n] += trap;

	return true;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> L >> N >> Q;
	for (int i = 1; i <= L; i++) {
		for (int j = 1; j <= L; j++) {
			cin >> board[i][j];
		}
	}

	knight = vector<Knight>(N+1);
	for (int n = 1; n <= N; n++) {
		int r, c, h, w, k;
		cin >> r >> c >> h >> w >> k;
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				shield[r + i][c + j] = n;
			}
		}
		knight[n] = { r, c, h, w, k };
	}

	for (int n = 0; n < Q; n++) {
		int num, d;
		cin >> num >> d;
		if (knight[num].k <= health[num]) continue;
		for (int i = 1; i <= L; i++) {
			for (int j = 1; j <= L; j++) {
				tshield[i][j] = 0;
			}
		}
		for (int i = 1; i <= N; i++) {
			vis[i] = 0;
			thealth[i] = 0;
		}

		if (move(num, d)) {
			for (int i = 1; i <= L; i++) {
				for (int j = 1; j <= L; j++) {
					if (shield[i][j] != 0 && !vis[shield[i][j]]) continue; // 옮길때, tshield에 표시는 안되있지만 살아있는 전사도 잘 표시해야 한다.
					shield[i][j] = tshield[i][j]; 
				}
			}
			for (int i = 1; i <= N; i++) {
				// 세로로 된 전사를 가로로 옮길 때, 전사 둘이 있는데, 
				// 둘 중 하나라도 못움직인다면 아예 움직일 수 없으니 체력 감소도 나중에 한번에 적용해야 한다.
				if (vis[i]) {
					if (i != num) health[i] += thealth[i];
					knight[i].r += dx[d];
					knight[i].c += dy[d];
				}
			}
		}
	}

	for (int i = 1; i <= N; i++) {
		if (health[i] < knight[i].k) {
			score += health[i];
		}
	}

	cout << score;
}