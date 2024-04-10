#include <iostream>
#include <algorithm>

using namespace std;

int n, m, x, y, dir, result;
int board[55][55];
int vis[55][55];

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> x >> y >> dir;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> board[i][j];
            if(board[i][j] == 1) vis[i][j] = 5;
        }
    }
    do {
        if (!vis[x][y])
        {
            vis[x][y] = dir + 1;
            result++;
        }

        bool dirty = false;
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (board[nx][ny] || vis[nx][ny])
                continue;
            dirty = true;
        }
        if (dirty)
        {
            dir = (dir + 3) % 4;
            if (!board[x + dx[dir]][y + dy[dir]] && !vis[x + dx[dir]][y + dy[dir]]) {
                x += dx[dir];
                y += dy[dir];
            }
        }
        else
        {
            x -= dx[dir];
            y -= dy[dir];
        }
    } while (!board[x][y]);

    cout << result;
}

/*
뒤로 돌아간다고 하길래 dfs 문제인줄 알았다
하지만 dfs는 그전의 좌표로 돌아가기 때문에
문제에서 계속 뒤로 가는 상황과 맞지 않는다.
조건에 맞게 계속 진행하는 것이 방법이었다.
*/