#include <iostream>
#include <vector>

using namespace std;

int n;
int board[15][15];
vector<pair<int, int>> v;
int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };
pair<int, int> result;

void init() {
	result = { 0, 0 };
	v.clear();
}

int create_line(int x, int y, int dir) {
	int cnt = 0;
    int nx = x;
    int ny = y;
    while(true) {
        nx += dx[dir];
		ny += dy[dir];
        if (nx < 0 || nx >= n || ny < 0 || ny >= n) break;
        if (board[nx][ny] != 0) return -1;
    }
    nx = x;
    ny = y;
	while (true) {
		nx += dx[dir];
		ny += dy[dir];
		if (nx < 0 || nx >= n || ny < 0 || ny >= n) {
			return cnt;
		}
		board[nx][ny] = 2;
		cnt++;
	}
}

void delete_line(int x, int y, int dir, int cnt) {
	for (int i = 0; i < cnt; i++) {
		x += dx[dir];
		y += dy[dir];
		board[x][y] = 0;
	}
}

void backtracking(int index, int core, int line) {
    if (core > result.first) {
        result.first = core;
        result.second = line;
    }
    else if (core == result.first) {
        result.second = min(line, result.second);
    }
	if (index == v.size()) {
		return;
	}

	auto cur = v[index];
	int nx = cur.first;
	int ny = cur.second;
    // 중복이 있기 때문에 이 부분이 잘못됐음
    // 잘못된 방향이 있으면 정답 코드는 그냥 스킵하는데
    // 나는 그걸 무시하고 아무 연락도 없이 다음 코드로 가기 때문에 중복이 생길 수 밖에 없다
    // 중복되면 무시해야 되는 것이 맞다. 어차피 모든 경우를 비교하기 때문에
    // 만약에 앞이 겹쳐서 안된다고 하면 되는 경우도 있을 것이고 없는 경우에 아무것도 안하는 경우와
    // 다를 것이 없기 때문에 중복이 생길 수 밖에 없다
    // for (int i = 0; i < 5; i++) {
	// 	int line_result = create_line(nx, ny, i);
	// 	if (line_result >= 0) {
	// 		backtracking(index + 1, core + 1, line + line_result);
	// 		delete_line(nx, ny, i, line_result);
	// 	}
	// 	else {
	// 		backtracking(index + 1, core, line);
	// 	}
	// }
    for (int i = 0; i < 4; i++) {
		int line_result = create_line(nx, ny, i);
		if (line_result == -1) {
			continue;
		}
		backtracking(index + 1, core + 1, line + line_result);
        delete_line(nx, ny, i, line_result);
	}

    backtracking(index + 1, core, line);
}

bool isConnect(int x, int y) {
    return x < 1 || x >= n-1 || y < 1 || y >= n-1;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		cin >> n;
		init();
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> board[i][j];
				if (board[i][j] == 1) {
                    if (!isConnect(i, j)) {
                        v.push_back({ i, j });
                    }
				}
			}
		}

		backtracking(0, 0, 0);

		cout << "#" << tc << " " << result.second << "\n";
	}
}