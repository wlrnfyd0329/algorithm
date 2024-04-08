#include <iostream>

using namespace std;

int n, m, result;
int board[505][505];
int vis[505][505];

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

void dfs(int x, int y, int cnt, int sum) {
    sum += board[x][y];
    vis[x][y] = 1;
    if(cnt == 4) {
        if(result < sum) result = sum;
        vis[x][y] = 0;
        return;
    }
    for(int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
        if(vis[nx][ny]) continue;
        dfs(nx, ny, cnt + 1, sum);
    }
    vis[x][y] = 0;
}

void mcross(int x, int y) {
    for(int i = 0; i < 4; i++) {
        int sum = board[x][y]; // sum은 매번 초기화 되야 한다.
        for(int j = 0; j < 4; j++) {
            if(j == i) continue;
            int nx = x + dx[j];
            int ny = y + dy[j];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) break;
            sum += board[nx][ny];
        }
        if(result < sum) result = sum;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> board[i][j];
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            dfs(i, j, 1, 0);
            mcross(i, j);
        }
    }
    
    cout << result;
}

/*
처음에는 bfs로 greedy하게 풀려고 했다. 하지만
4 5
5 5 5 5 5
5 100 1 1 100
5 5 5 5 5
5 5 5 5 5
이런 반례에 막혔다.

반드시 dfs로 4번 탐색을 함으로써 테트로미노의 모양을 살리고
십자가는 dx, dy 움직임에서 하나를 제외하는 방법으로 문제를 해결한다.
*/