// bfs는 항상 vis 안되어 있으면 최단이다.

#include <iostream>
#include <queue>
#define X first
#define Y second

using namespace std;

int n, m, k;
struct Info {
    int broken;
    bool isNoon;
    int dist;
    int x;
    int y;
};
int board[1005][1005];
bool vis[15][1005][1005];

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
    q.push({0, true, 1, 1, 1});
    vis[0][1][1] = true;

    while(!q.empty()) {
        auto cur = q.front(); q.pop();
        if (cur.x == n && cur.y == m) {
            cout << cur.dist;
            return 0;
        }
        for(int dir = 0; dir < 4; dir++) {
            int nx = cur.x + dx[dir];
            int ny = cur.y + dy[dir];
            if (nx <= 0 || nx > n || ny <= 0 || ny > m) continue;
            if (board[nx][ny] == 1) {
                if (cur.broken == k) continue;
                if (vis[cur.broken + 1][nx][ny]) continue;
                if (cur.isNoon) {
                    vis[cur.broken + 1][nx][ny] = true;
                    q.push({cur.broken + 1, !cur.isNoon, cur.dist + 1, nx, ny});
                }
                else {
                    q.push({cur.broken, !cur.isNoon, cur.dist + 1, cur.x, cur.y});
                }
            }
            else {
                if (vis[cur.broken][nx][ny]) continue;
                vis[cur.broken][nx][ny] = true;
                q.push({cur.broken, !cur.isNoon, cur.dist + 1, nx, ny});
            }
        }
    }

    cout << -1;
}