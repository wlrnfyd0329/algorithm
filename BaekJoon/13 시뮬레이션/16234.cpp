#include <iostream>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

int n, l, r, cnt;
queue<pair<int,int>> Q, cQ;
int board[55][55];
int vis[55][55];
int vvis[55][55];

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

bool check()
{
    fill(vis[0], vis[54], 0);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                int nx = i + dx[k];
                int ny = j + dy[k];
                if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
                if(vis[nx][ny]) continue;
                int temp = abs(board[i][j] - board[nx][ny]);
                if (temp < l || temp > r) continue;
                vis[nx][ny] = 1;
                Q.push({nx, ny});
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (vis[i][j])
                return true;
        }
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> l >> r;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> board[i][j];
        }
    }

    while(check()) {
        cnt++;
        int temp = 0;
        fill(vvis[0], vvis[54], 0);
        while(!Q.empty()) {
            auto cur = Q.front(); Q.pop();
            if(vvis[cur.first][cur.second]) continue;
            temp++;
            cQ.push(cur);
            while(!cQ.empty()) {
                auto ccur = cQ.front(); cQ.pop();
                for(int i = 0; i < 4; i++) {
                    int nx = ccur.first + dx[i];
                    int ny = ccur.second + dy[i];
                    if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
                    if (vvis[nx][ny] || vis[nx][ny] == 0) continue;
                    int cal = abs(board[ccur.first][ccur.second] - board[nx][ny]);
                    if (cal < l || cal > r)
                        continue;
                    vvis[nx][ny] = temp;
                    cQ.push({nx, ny});
                }
            }
        }
        while(temp) {
            int sum = 0;
            int sum_cnt = 0;
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++) {
                    if(vvis[i][j] == temp) {
                        sum += board[i][j];
                        sum_cnt++;
                    }
                }
            }
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++) {
                    if(vvis[i][j] == temp) {
                        board[i][j] = sum / sum_cnt;
                    }
                }
            }
            temp--;
        }
    }
    cout << cnt;
}

/*
bfs 활용
실패한 반례
3 3 4
6 8 5
10 7 2
9 10 1
처음으로 국경을 허물때 1로 다 표시하니까 국경을 허물면 안될때도
같이 허물기 때문에 오류가 남
국경을 허문 것들 끼리 bfs할때 옆의 국경 확인하면 됨

처음 국경 체크할때 한번에 경계도 나누려고 했는데
이는 확인하지 않아도 되는 경우에도 계속 bfs를 시도하기 때문에
시간초과가 난다.

fill 2차원 사용법 잊지 않기
*/