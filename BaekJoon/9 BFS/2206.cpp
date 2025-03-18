// bfs는 항상 최단거리로 이동하기 때문에 vis가 있다는 건 나중에 도착했다는 의미다.

#include <iostream>
#include <queue>
#define X first
#define Y second
#define endl "\n"

using namespace std;

int board[1005][1005];
int vis[2][1005][1005];

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
    {
        string s;
        cin >> s;
        for (int j = 1; j <= m; j++)
        {
            board[i][j] = s[j - 1] - '0';
            vis[0][i][j] = 0;
            vis[1][i][j] = 0;
        }
    }

    queue<pair<int, pair<int, int>>> q;
    q.push({0, {1, 1}});
    vis[0][1][1] = 1;
    while (!q.empty())
    {
        auto cur = q.front();
        q.pop();
        for (int dir = 0; dir < 4; dir++)
        {
            int nx = cur.Y.X + dx[dir];
            int ny = cur.Y.Y + dy[dir];
            if (nx <= 0 || nx > n || ny <= 0 || ny > m)
                continue;
            if (vis[cur.X][nx][ny] > 0)
                continue;
            if (board[nx][ny] == 1)
            {
                if (cur.X == 1)
                    continue;
                if (vis[1][nx][ny] == 0 || vis[1][nx][ny] > vis[0][nx][ny] + 1)
                {
                    vis[1][nx][ny] = vis[0][cur.Y.X][cur.Y.Y] + 1;
                    q.push({1, {nx, ny}});
                    continue;
                }
            }
            vis[cur.X][nx][ny] = vis[cur.X][cur.Y.X][cur.Y.Y] + 1;
            q.push({cur.X, {nx, ny}});
        }
    }

    if (vis[0][n][m] != 0 && vis[1][n][m] != 0)
    {
        cout << min(vis[0][n][m], vis[1][n][m]);
    }
    else if (vis[0][n][m] != 0)
    {
        cout << vis[0][n][m];
    }
    else if (vis[1][n][m] != 0)
    {
        cout << vis[1][n][m];
    }
    else
    {
        cout << -1;
    }
}