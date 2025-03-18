#include <iostream>
#include <vector>
#include <queue>
#define X first
#define Y second
#define endl "\n"

using namespace std;

int n;
int board[55][55];
int vis[2][55][55];

int dx[8] = {-1, 1, 0, 0, -1, -1, 1, 1};
int dy[8] = {0, 0, -1, 1, -1, 1, -1, 1};

struct Info {
    int status; // 가로면 0, 세로면 1
    int x;
    int y;
};

queue<Info> q;
vector<pair<int, int>> b;
vector<pair<int, int>> e;
Info end_point;

void init() {
    if (e[0].X == e[1].X) { // 가로인가
        end_point.status = 0;
        end_point.x = e[1].X;
        end_point.y = e[1].Y;
    }
    else { // 세로인가
        end_point.status = 1;
        end_point.x = e[1].X;
        end_point.y = e[1].Y;
    }
    if (b[0].X == b[1].X) { // 가로인가
        q.push({0, b[1].X, b[1].Y});
        vis[0][b[1].X][b[1].Y] = 1;
    }
    else { // 세로인가
        q.push({1, b[1].X, b[1].Y});
        vis[1][b[1].X][b[1].Y] = 1;
    }
}

bool move(int dir, int stat, int x, int y) {
    int xx[3];
    int yy[3];
    if (stat == 0) {
        for(int i = 0; i < 3; i++) {
            xx[i] = x;
        }
        yy[0] = y - 1;
        yy[1] = y;
        yy[2] = y + 1;
    }
    else {
        xx[0] = x - 1;
        xx[1] = x;
        xx[2] = x + 1;
        for (int i = 0; i < 3; i++)
        {
            yy[i] = y;
        }
    }

    for(int i = 0; i < 3; i++) {
        int nx = xx[i] + dx[dir];
        int ny = yy[i] + dy[dir];
        if (nx < 0 || nx >= n || ny < 0 || ny >= n) return false;
        if (board[nx][ny] == 1) return false;
        if (i == 1 && vis[stat][nx][ny]) return false;
    }

    return true;
}

bool rotate(int stat, int x, int y) {
    if (vis[1^stat][x][y]) return false;
    for(int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < 0 || nx >= n || ny < 0 || ny >= n) return false;
        if (board[nx][ny] == 1) return false;
    }

    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for(int j = 0; j < n; j++) {
            if (s[j] == 'B') {
                b.push_back({i, j});
            }
            if (s[j] == 'E') {
                e.push_back({i, j});
            }
            if (s[j] == '1') {
                board[i][j] = 1;
            }
            if (s[j] == '0') {
                board[i][j] = 0;
            }
        }
    }

    init();

    while(!q.empty()) {
        auto cur = q.front(); q.pop();
        if (cur.status == end_point.status && cur.x == end_point.x && cur.y == end_point.y) {
            cout << vis[cur.status][cur.x][cur.y] - 1;
            return 0;
        }
        for(int dir = 0; dir < 4; dir++) {
            if (move(dir, cur.status, cur.x, cur.y)) {
                vis[cur.status][cur.x + dx[dir]][cur.y + dy[dir]] = vis[cur.status][cur.x][cur.y] + 1;
                q.push({cur.status, cur.x + dx[dir], cur.y + dy[dir]});
            }
        }
        if (rotate(cur.status, cur.x, cur.y)) {
            vis[1^cur.status][cur.x][cur.y] = vis[cur.status][cur.x][cur.y] + 1;
            q.push({1^cur.status, cur.x, cur.y});
        }
    }

    cout << 0;
    return 0;
}