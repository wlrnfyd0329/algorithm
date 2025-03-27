#include <iostream>
#include <queue>
#include <string.h>
#define X first
#define Y second

using namespace std;

int N, M, K, turn;
int board[15][15];
int shoot[15][15];
int damaged[15][15];
pair<int, int> weak;
pair<int, int> strong;
int dx[8] = { 0, 1, 0, -1, 1, 1, -1, -1 };
int dy[8] = { 1, 0, -1, 0, 1, -1, 1, -1 };

void select_weak() {
    int damage = 1234567891;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (board[i][j] == 0) continue;
            if (damage > board[i][j]) {
                damage = board[i][j];
                weak = { i, j };
            }
            else if (damage == board[i][j]) {
                if (shoot[weak.X][weak.Y] < shoot[i][j]) {
                    weak = { i, j };
                }
                else if (shoot[weak.X][weak.Y] == shoot[i][j]) {
                    if (weak.X + weak.Y < i + j) {
                        weak = { i,j };
                    }
                    else if (weak.X + weak.Y == i + j) {
                        if (weak.Y < j) {
                            weak = { i, j };
                        }
                    }
                }
            }
        }
    }

    damaged[weak.X][weak.Y]++;
    shoot[weak.X][weak.Y] = turn;
    board[weak.X][weak.Y] += N + M;
}

void select_strong() {
    int damage = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (board[i][j] == 0 || weak.X == i && weak.Y == j) continue;
            if (damage < board[i][j]) {
                damage = board[i][j];
                strong = { i, j };
            }
            else if (damage == board[i][j]) {
                if (shoot[strong.X][strong.Y] > shoot[i][j]) {
                    strong = { i, j };
                }
                else if (shoot[strong.X][strong.Y] == shoot[i][j]) {
                    if (strong.X + strong.Y > i + j) {
                        strong = { i,j };
                    }
                    else if (strong.X + strong.Y == i + j) {
                        if (strong.Y > j) {
                            strong = { i, j };
                        }
                    }
                }
            }
        }
    }

    damaged[strong.X][strong.Y]++;
}

void attack() {
    int damage = board[weak.X][weak.Y];
    bool isLaser = false;
    pair<int, int> path[15][15];
    queue<pair<int, int>> q;
    int vis[15][15];
    for (int i = 0; i < N; i++) {
        memset(vis[i], 0, sizeof(int) * M);
    }
    vis[weak.X][weak.Y] = 1;
    q.push({ weak.X, weak.Y });
    while (!q.empty()) {
        auto cur = q.front(); q.pop();
        if (cur.X == strong.X && cur.Y == strong.Y) {
            isLaser = true;
            break;
        }
        for (int dir = 0; dir < 4; dir++) {
            int nx = cur.X + dx[dir];
            int ny = cur.Y + dy[dir];
            if (nx < 0) nx = N - 1;
            if (nx >= N) nx = 0;
            if (ny < 0) ny = M - 1;
            if (ny >= M) ny = 0;
            if (!board[nx][ny] || vis[nx][ny]) continue;
            vis[nx][ny] = 1;
            path[nx][ny] = { cur.X, cur.Y };
            q.push({ nx, ny });
        }
    }

    if (isLaser) {
        board[strong.X][strong.Y] -= damage;
        strong = path[strong.X][strong.Y];
        while (!(strong.X == weak.X && strong.Y == weak.Y)) {
            board[strong.X][strong.Y] -= damage / 2;
            damaged[strong.X][strong.Y]++;
            strong = path[strong.X][strong.Y];
        }
    }
    else {
        board[strong.X][strong.Y] -= damage;
        for (int dir = 0; dir < 8; dir++) {
            int nx = strong.X + dx[dir];
            int ny = strong.Y + dy[dir];
            if (nx < 0) nx = N - 1;
            if (nx >= N) nx = 0;
            if (ny < 0) ny = M - 1;
            if (ny >= M) ny = 0;
            if (!board[nx][ny] || (nx == weak.X && ny == weak.Y)) continue;
            board[nx][ny] -= damage / 2;
            damaged[nx][ny]++;
        }
    }
}

void maintenance() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (board[i][j] <= 0) board[i][j] = 0;
            if (damaged[i][j] == 0 && board[i][j] != 0) board[i][j]++;
            damaged[i][j] = 0;
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M >> K;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> board[i][j];
        }
    }
    
    int ans;
    for (turn = 1; turn <= K; turn++) {
        ans = 0;
        select_weak();
        select_strong();
        attack();
        maintenance();
        int cnt = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (board[i][j]) {
                    cnt++;
                    ans = max(ans, board[i][j]);
                }
            }
        }
        if (cnt == 1) break;
    }
    
    cout << ans;
}