#include <iostream>
#include <queue>
#define X first
#define Y second

using namespace std;

int n, m, k;
struct Info {
    int broken;
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
    q.push({0, 1, 1});
    vis[0][1][1] = 1;

    while(!q.empty()) {
        auto cur = q.front(); q.pop();
        if (cur.x == n && cur.y == m) {
            cout << vis[cur.broken][cur.x][cur.y];
            return 0;
        }
        for(int dir = 0; dir < 4; dir++) {
            int nx = cur.x + dx[dir];
            int ny = cur.y + dy[dir];
            if (nx <= 0 || nx > n || ny <= 0 || ny > m) continue;
            if (vis[cur.broken][nx][ny] > 0) continue;
            if (board[nx][ny] == 1) {
                if (cur.broken == k) continue;
                if (vis[cur.broken + 1][nx][ny] == 0 || vis[cur.broken + 1][nx][ny] > vis[cur.broken][cur.x][cur.y] + 1) {
                    vis[cur.broken + 1][nx][ny] = vis[cur.broken][cur.x][cur.y] + 1;
                    q.push({cur.broken + 1, nx, ny});
                }
            }
            else {
                vis[cur.broken][nx][ny] = vis[cur.broken][cur.x][cur.y] + 1;
                q.push({cur.broken, nx, ny});
            }
        }
    }

    cout << -1;
}