// k번 전파 되는 조건을 빼먹어서 틀렸다...

#include <iostream>
#include <vector>
#define X first
#define Y second

using namespace std;

int n, m, k, c, ans;
int board[25][25];
int dead[25][25];

int dx[8] = { 1, 0, -1, 0, 1, 1, -1, -1 };
int dy[8] = { 0, 1, 0, -1, -1, 1, -1, 1 };

struct Tree {
	int x;
	int y;
	vector<int> dir;
};

void grow() {
	vector<Tree> trees;
	for (int i = 0; i < n; i++) { // 성장
		for (int j = 0; j < n; j++) {
			if (board[i][j] > 0) {
				int cnt = 0;
				vector<int> d;
				for (int dir = 0; dir < 4; dir++) { // 근처에 있는 나무 개수 만큼 성장
					int nx = i + dx[dir];
					int ny = j + dy[dir];
					if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
					if (board[nx][ny] > 0) cnt++; // 근처의 나무 개수
					else if (board[nx][ny] == 0 && dead[nx][ny] == 0) d.push_back(dir); // 벽, 다른 나무, 제조체 없으면 비어 있다고 판단
				}
				board[i][j] += cnt;
				trees.push_back({ i, j, d });
			}
		}
	}

	for (auto tree : trees) { // 번식
		if (tree.dir.empty()) continue;
		int child_tree = board[tree.x][tree.y] / tree.dir.size(); // 번식 가능한 수 확인
		for (int dir : tree.dir) {
			int nx = tree.x + dx[dir];
			int ny = tree.y + dy[dir];
			board[nx][ny] += child_tree;
		}
	}
}

void spray() { // 제초제 뿌리기
	pair<int, int> max_pos = { 0, 0 };
	int max_v = 0;

	for (int i = 0; i < n; i++) { // 제초제 뿌릴 곳 찾기
		for (int j = 0; j < n; j++) {
			if (board[i][j] > 0) { // 나무가 아니면 어차피 전파가 안됨
				int cnt = board[i][j];
				for (int dir = 4; dir < 8; dir++) {
					int nx = i;
					int ny = j;
					int dist = k;
					while (dist--) { // k칸 만큼 전파 된다.
						nx += dx[dir];
						ny += dy[dir];
						if (nx < 0 || nx >= n || ny < 0 || ny >= n) break;
						if (board[nx][ny] > 0) {
							cnt += board[nx][ny];
						}
						else {
							break;
						}
					}
				}

				if (max_v < cnt) { // 같으면 행이 작은 순서 -> 열이 작은 순서
					max_v = cnt;
					max_pos = { i, j };
				}
			}
		}
	}

	for (int i = 0; i < n; i++) { // 제초제 지속시간 줄이기 감소 시키기
		for (int j = 0; j < n; j++) {
			if (dead[i][j] > 0) dead[i][j]--;
		}
	}

	// 제초제 뿌리기
	board[max_pos.X][max_pos.Y] = 0;
	dead[max_pos.X][max_pos.Y] = c;
	for (int dir = 4; dir < 8; dir++) {
		int nx = max_pos.X;
		int ny = max_pos.Y;
		int dist = k;
		while (dist--) {
			nx += dx[dir];
			ny += dy[dir];
			if (nx < 0 || nx >= n || ny < 0 || ny >= n) break;
			dead[nx][ny] = c;
			if (board[nx][ny] > 0) {
				board[nx][ny] = 0;
			}
			else {
				break;
			}
		}
	}

	ans += max_v;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m >> k >> c;
	ans = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> board[i][j];
		}
	}

	while (m--) {
		grow();
		spray();
	}

	cout << ans;
}