#include <iostream>
#include <string>
#include <queue>
#define endl "\n"

using namespace std;

int n, m;
int board[606][606];
int vis[606][606];
queue<pair<int, int>> q;

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        for(int j = 0; j < m; j++) {
            if (s[j] == 'I') {
                q.push({i, j});
                vis[i][j] = 1;
            }
            else if (s[j] == 'X') {
                board[i][j] = -1;
            }
            else if (s[j] == 'P') {
                board[i][j] = 1;
            }
        }
    }

    int cnt = 0;
    while(!q.empty()) {
        auto cur = q.front(); q.pop();
        for(int dir = 0; dir < 4; dir++) {
            int nx = cur.first + dx[dir];
            int ny = cur.second + dy[dir];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if (vis[nx][ny] || board[nx][ny] < 0) continue;
            if (board[nx][ny] > 0) cnt++;
            vis[nx][ny] = 1;
            q.push({nx, ny});
        }
    }

    if (cnt == 0) cout << "TT";
    else cout << cnt;
}