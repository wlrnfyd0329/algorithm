#include <iostream>
#include <queue>
#include <vector>
#define endl "\n"

using namespace std;

int N, M, F, turn = 0; // turn은 시작하면 1 증가하고 이동

int board[25][25];
int vis[25][25];
int cube[5][15][15]; // 0:동, 1:서, 2:남, 3:북, 4:윗면
int cube_vis[5][15][15];
pair<int, int> cube_escape[4][15]; // 큐브에서 탈출시 좌표 0:동, 1:서, 2:남, 3:북

struct Human {
    int x;
    int y;
    int status; // 0:동, 1:서, 2:남, 3:북, 4:윗면, 5: 바닥
};
queue<Human> q;

struct Fire {
    int x;
    int y;
    int dir;
    int period;
    int now;
    bool isDo = true;
};

vector<Fire> fire;
int fire_vis[25][25];
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };

void input() {
    cin >> N >> M >> F;
    int cube_status = 0;
    int cube_x = 0;
    int cube_y = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> board[i][j];
            vis[i][j] = -1;
            fire_vis[i][j] = -1;
            if (board[i][j] == 3) {
                if (cube_status == 0) {
                    cube_escape[3][M - 1 - cube_y] = { i - 1, j };
                    if (cube_y == 0) {
                        cube_escape[1][0] = { i, j - 1 };
                    }

                    if (cube_y != M - 1) {
                        cube_y++;
                    }
                    else {
                        cube_escape[0][M - 1] = { i, j + 1 };
                        cube_status = 1;
                        cube_x++;
                        cube_y = 0;
                    }
                }
                else {
                    if (cube_y == 0) {
                        cube_escape[1][cube_x] = { i, j - 1 };
                    }
                    if (cube_x == M - 1) {
                        cube_escape[2][cube_y] = { i + 1, j };
                    }
                    if (cube_y == M - 1) {
                        cube_escape[0][M - 1 - cube_x] = { i, j + 1 };
                        cube_x++;
                        cube_y = -1;
                    }
                    cube_y++;
                }
            }
        }
    }

    for (int k = 0; k < 5; k++) {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < M; j++) {
                cin >> cube[k][i][j];
                cube_vis[k][i][j] = -1;
                if (cube[k][i][j] == 2) {
                    q.push({ i, j, k });
                    cube_vis[k][i][j] = 0;
                }
            }
        }
    }

    for (int i = 0; i < F; i++) {
        int x, y, dir, period;
        cin >> x >> y >> dir >> period;
        fire_vis[x][y] = 0;
        fire.push_back({ x, y, dir, period, 0 });
    }
}

void fire_move() {
    for (int i = 0; i < fire.size(); i++) {
        if (!fire[i].isDo) continue;
        int nx = fire[i].x + dx[fire[i].dir];
        int ny = fire[i].y + dy[fire[i].dir];
        if (nx < 0 || nx >= N || ny < 0 || ny >= N || board[nx][ny] == 1 || board[nx][ny] == 3 || board[nx][ny] == 4) {
            fire[i].isDo = false;
            continue;
        }
        fire[i].now += fire[i].period;
        if (fire_vis[nx][ny] < 0 || fire_vis[nx][ny] > fire[i].now) {
            fire_vis[nx][ny] = fire[i].now;
        }
        fire[i].x = nx;
        fire[i].y = ny;
    }
}

void boundary_check(int nx, int ny, int status, int cnt) { // 경계에서 좌표와 상태를 바꿔주고 갈 수 있는지 확인한 후, 가능하면 큐에 넣기
    switch (status) {
    case 0: // 동
        if (nx < 0) { // 윗쪽으로
            nx = M - 1 - ny;
            ny = M - 1;
            if (cube[4][nx][ny] == 0 && cube_vis[4][nx][ny] < 0) {
                cube_vis[4][nx][ny] = cnt + 1;
                q.push({ nx, ny, 4 });
            }
        }
        else if (nx >= M) { // 바닥으로 탈출
            nx = cube_escape[status][ny].first;
            ny = cube_escape[status][ny].second;
            if (board[nx][ny] == 0 && (fire_vis[nx][ny] < 0 || fire_vis[nx][ny] > cnt + 1)) {
                vis[nx][ny] = cnt + 1;
                q.push({ nx, ny, 5 });
            }
        }
        else if (ny < 0) { // 남쪽으로
            ny = M - 1;
            if (cube[2][nx][ny] == 0 && cube_vis[2][nx][ny] < 0) {
                cube_vis[2][nx][ny] = cnt + 1;
                q.push({ nx, ny, 2 });
            }
        }
        else if (ny >= M) { // 북쪽으로
            ny = 0;
            if (cube[3][nx][ny] == 0 && cube_vis[3][nx][ny] < 0) {
                cube_vis[3][nx][ny] = cnt + 1;
                q.push({ nx, ny, 3 });
            }
        }
        break;
    case 1: // 서
        if (nx < 0) { // 윗쪽으로
            nx = ny;
            ny = 0;
            if (cube[4][nx][ny] == 0 && cube_vis[4][nx][ny] < 0) {
                cube_vis[4][nx][ny] = cnt + 1;
                q.push({ nx, ny, 4 });
            }
        }
        else if (nx >= M) { // 바닥으로 탈출
            nx = cube_escape[status][ny].first;
            ny = cube_escape[status][ny].second;
            if (board[nx][ny] == 0 && (fire_vis[nx][ny] < 0 || fire_vis[nx][ny] > cnt + 1)) {
                vis[nx][ny] = cnt + 1;
                q.push({ nx, ny, 5 });
            }
        }
        else if (ny < 0) { // 북쪽으로
            ny = M - 1;
            if (cube[3][nx][ny] == 0 && cube_vis[3][nx][ny] < 0) {
                cube_vis[3][nx][ny] = cnt + 1;
                q.push({ nx, ny, 3 });
            }
        }
        else if (ny >= M) { // 남쪽으로
            ny = 0;
            if (cube[2][nx][ny] == 0 && cube_vis[2][nx][ny] < 0) {
                cube_vis[2][nx][ny] = cnt + 1;
                q.push({ nx, ny, 2 });
            }
        }
        break;
    case 2: // 남
        if (nx < 0) { // 윗쪽으로
            nx = M - 1;
            if (cube[4][nx][ny] == 0 && cube_vis[4][nx][ny] < 0) {
                cube_vis[4][nx][ny] = cnt + 1;
                q.push({ nx, ny, 4 });
            }
        }
        else if (nx >= M) { // 바닥으로 탈출
            nx = cube_escape[status][ny].first;
            ny = cube_escape[status][ny].second;
            if (board[nx][ny] == 0 && (fire_vis[nx][ny] < 0 || fire_vis[nx][ny] > cnt + 1)) {
                vis[nx][ny] = cnt + 1;
                q.push({ nx, ny, 5 });
            }
        }
        else if (ny < 0) { // 서쪽으로
            ny = M - 1;
            if (cube[1][nx][ny] == 0 && cube_vis[1][nx][ny] < 0) {
                cube_vis[1][nx][ny] = cnt + 1;
                q.push({ nx, ny, 1 });
            }
        }
        else if (ny >= M) { // 동쪽으로
            ny = 0;
            if (cube[0][nx][ny] == 0 && cube_vis[0][nx][ny] < 0) {
                cube_vis[0][nx][ny] = cnt + 1;
                q.push({ nx, ny, 0 });
            }
        }
        break;
    case 3: // 북
        if (nx < 0) { // 윗쪽으로
            nx = 0;
            ny = M - 1 - ny;
            if (cube[4][nx][ny] == 0 && cube_vis[4][nx][ny] < 0) {
                cube_vis[4][nx][ny] = cnt + 1;
                q.push({ nx, ny, 4 });
            }
        }
        else if (nx >= M) { // 바닥으로 탈출
            nx = cube_escape[status][ny].first;
            ny = cube_escape[status][ny].second;
            if (board[nx][ny] == 0 && (fire_vis[nx][ny] < 0 || fire_vis[nx][ny] > cnt + 1)) {
                vis[nx][ny] = cnt + 1;
                q.push({ nx, ny, 5 });
            }
        }
        else if (ny < 0) { // 동쪽으로
            ny = M - 1;
            if (cube[0][nx][ny] == 0 && cube_vis[0][nx][ny] < 0) {
                cube_vis[0][nx][ny] = cnt + 1;
                q.push({ nx, ny, 0 });
            }
        }
        else if (ny >= M) { // 서쪽으로
            ny = 0;
            if (cube[1][nx][ny] == 0 && cube_vis[1][nx][ny] < 0) {
                cube_vis[1][nx][ny] = cnt + 1;
                q.push({ nx, ny, 1 });
            }
        }
        break;
    case 4: // 윗면
        if (nx < 0) { // 북쪽으로
            ny = M - 1 - ny;
            nx = 0;
            if (cube[3][nx][ny] == 0 && cube_vis[3][nx][ny] < 0) {
                cube_vis[3][nx][ny] = cnt + 1;
                q.push({ nx, ny, 3 });
            }
        }
        else if (nx >= M) { // 남쪽으로
            nx = 0;
            if (cube[2][nx][ny] == 0 && cube_vis[2][nx][ny] < 0) {
                cube_vis[2][nx][ny] = cnt + 1;
                q.push({ nx, ny, 2 });
            }
        }
        else if (ny < 0) { // 서쪽으로
            ny = nx;
            nx = 0;
            if (cube[1][nx][ny] == 0 && cube_vis[1][nx][ny] < 0) {
                cube_vis[1][nx][ny] = cnt + 1;
                q.push({ nx, ny, 1 });
            }
        }
        else if (ny >= M) { // 동쪽으로
            ny = M - 1 - nx;
            nx = 0;
            if (cube[0][nx][ny] == 0 && cube_vis[0][nx][ny] < 0) {
                cube_vis[0][nx][ny] = cnt + 1;
                q.push({ nx, ny, 0 });
            }
        }
        break;
    }
}

int move() {
    while (!q.empty()) {
        fire_move();
        auto cur = q.front(); q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];
            if (cur.status == 5) {
                if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
                if (board[nx][ny] == 1 || board[nx][ny] == 3 || (fire_vis[nx][ny] >= 0 && fire_vis[nx][ny] <= vis[cur.x][cur.y] + 1) || vis[nx][ny] >= 0) continue;
                vis[nx][ny] = vis[cur.x][cur.y] + 1;
                if (board[nx][ny] == 4) return vis[nx][ny];
                q.push({ nx, ny, 5 });
            }
            else {
                if (nx < 0 || nx >= M || ny < 0 || ny >= M) {
                    boundary_check(nx, ny, cur.status, cube_vis[cur.status][cur.x][cur.y]);
                    continue;
                }
                if (cube[cur.status][nx][ny] == 1 || cube_vis[cur.status][nx][ny] >= 0) continue;
                cube_vis[cur.status][nx][ny] = cube_vis[cur.status][cur.x][cur.y] + 1;
                q.push({ nx, ny, cur.status });
            }

        }
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    input();
    cout << move();
}