#include <iostream>
#include <queue>
#include <vector>
#define X first
#define Y second
#define endl "\n"

using namespace std;

int n, m, ans = 0;
int board[105][105];

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

void func() {
    queue<pair<int, int>> q;
    int vis[105][105] = {0, };
    vis[0][0] = 1;
    q.push({0, 0});
    while(!q.empty()) {
        auto cur = q.front(); q.pop();
        for(int dir = 0; dir < 4; dir++) {
            int nx = cur.X + dx[dir];
            int ny = cur.Y + dy[dir];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if (board[nx][ny] == 1) {
                vis[nx][ny]++;
                continue;
            }
            else if (vis[nx][ny]) continue;
            vis[nx][ny] = 1;
            q.push({nx, ny});
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if (vis[i][j] > 1) {
                board[i][j] = 0;
            }
        }
    }
}

bool isDone() {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if (board[i][j] == 1) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> board[i][j];
        }
    }

    while(!isDone()) {
        ans++;
        func();
    }
    
    cout << ans;
}