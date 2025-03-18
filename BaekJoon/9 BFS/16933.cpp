#include <iostream>
#include <queue>
#define X first
#define Y second

using namespace std;

int n, m, k;
struct Info {
    int broken;
    bool isNoon;
    int x;
    int y;
};
int board[1005][1005];
int vis[15][1005][1005];

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> k;
    for(int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        for(int j = 1; j <= m; j++) {
            board[i][j] = s[j-1] - '0';
        }
    }

    queue<Info> q;
    q.push({0, true, 1, 1});
    vis[0][1][1] = 1;

    while(!q.empty()) {
        auto cur = q.front(); q.pop();
        for(int dir = 0; dir < 4; dir++) {
            int nx = cur.x + dx[dir];
            int ny = cur.y + dy[dir];
            if (nx <= 0 || nx > n || ny <= 0 || ny > m) continue;
            if (board[nx][ny] == 1) {
                if (cur.broken == k) continue;
                if (cur.isNoon) {
                    if (vis[cur.broken + 1][nx][ny] == 0 || vis[cur.broken + 1][nx][ny] > vis[cur.broken][cur.x][cur.y] + 1) {
                        vis[cur.broken + 1][nx][ny] = vis[cur.broken][cur.x][cur.y] + 1;
                        q.push({cur.broken + 1, !cur.isNoon, nx, ny});
                    }
                }
                else {
                    if (vis[cur.broken + 1][nx][ny] == 0 || vis[cur.broken + 1][nx][ny] > vis[cur.broken][cur.x][cur.y] + 2) {
                        vis[cur.broken + 1][nx][ny] = vis[cur.broken][cur.x][cur.y] + 2;
                        q.push({cur.broken + 1, cur.isNoon, nx, ny});
                    }
                }
            }
            else {
                if (vis[cur.broken][nx][ny] == 0 || vis[cur.broken][nx][ny] > vis[cur.broken][cur.x][cur.y] + 1) {
                    vis[cur.broken][nx][ny] = vis[cur.broken][cur.x][cur.y] + 1;
                    q.push({cur.broken, !cur.isNoon, nx, ny});
                }
            }
        }
    }

    int cnt = 1234567891;
    for(int i = 0; i <= k; i++) {
        if (vis[i][n][m] == 0) continue;
        if (cnt > vis[i][n][m]) {
            cnt = vis[i][n][m];
        }
    }
    if (cnt == 1234567891) {
        cout << -1;
    }
    else {
        cout << cnt;
    }
}