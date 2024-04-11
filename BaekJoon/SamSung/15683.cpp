#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m, result = 80;
int board[10][10];
int vis[10][10];
vector<pair<int, int>> v;

int dx[4] = {0, -1, 0, 1};
int dy[4] = {1, 0, -1, 0};

void func(int num) {
    if(num == v.size()) {
        int block = 0;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(!vis[i][j]) block++;
            }
        }
        if(result > block) result = block;
        return;
    }
    if(board[v[num].first][v[num].second] == 1) {
        for(int i = 0; i < 4; i++) {
            int nx = v[num].first;
            int ny = v[num].second;
            while(true) {   
                nx += dx[i];
                ny += dy[i];
                if(nx < 0 || nx >= n || ny < 0 || ny >= m) break;
                if(board[nx][ny] == 6) break;
                vis[nx][ny]++;
            }
            func(num + 1);
            nx = v[num].first;
            ny = v[num].second;
            while(true) {   
                nx += dx[i];
                ny += dy[i];
                if(nx < 0 || nx >= n || ny < 0 || ny >= m) break;
                if(board[nx][ny] == 6) break;
                vis[nx][ny]--;
            }
        }
    }
    else if (board[v[num].first][v[num].second] == 2)
    {
        for (int i = 0; i < 2; i++)
        {
            int nx = v[num].first;
            int ny = v[num].second;
            while (true)
            {
                nx += dx[i];
                ny += dy[i];
                if (nx < 0 || nx >= n || ny < 0 || ny >= m)
                    break;
                if (board[nx][ny] == 6)
                    break;
                vis[nx][ny]++;
            }
            nx = v[num].first;
            ny = v[num].second;
            while (true)
            {
                nx += dx[i + 2];
                ny += dy[i + 2];
                if (nx < 0 || nx >= n || ny < 0 || ny >= m)
                    break;
                if (board[nx][ny] == 6)
                    break;
                vis[nx][ny]++;
            }
            func(num + 1);
            nx = v[num].first;
            ny = v[num].second;
            while (true)
            {
                nx += dx[i];
                ny += dy[i];
                if (nx < 0 || nx >= n || ny < 0 || ny >= m)
                    break;
                if (board[nx][ny] == 6)
                    break;
                vis[nx][ny]--;
            }
            nx = v[num].first;
            ny = v[num].second;
            while (true)
            {
                nx += dx[i + 2];
                ny += dy[i + 2];
                if (nx < 0 || nx >= n || ny < 0 || ny >= m)
                    break;
                if (board[nx][ny] == 6)
                    break;
                vis[nx][ny]--;
            }
        }
    }
    else if (board[v[num].first][v[num].second] == 3)
    {
        for (int i = 0; i < 4; i++)
        {
            int nx = v[num].first;
            int ny = v[num].second;
            while (true)
            {
                nx += dx[i];
                ny += dy[i];
                if (nx < 0 || nx >= n || ny < 0 || ny >= m)
                    break;
                if (board[nx][ny] == 6)
                    break;
                vis[nx][ny]++;
            }
            nx = v[num].first;
            ny = v[num].second;
            while (true)
            {
                nx += dx[(i + 1) % 4];
                ny += dy[(i + 1) % 4];
                if (nx < 0 || nx >= n || ny < 0 || ny >= m)
                    break;
                if (board[nx][ny] == 6)
                    break;
                vis[nx][ny]++;
            }
            func(num + 1);
            nx = v[num].first;
            ny = v[num].second;
            while (true)
            {
                nx += dx[i];
                ny += dy[i];
                if (nx < 0 || nx >= n || ny < 0 || ny >= m)
                    break;
                if (board[nx][ny] == 6)
                    break;
                vis[nx][ny]--;
            }
            nx = v[num].first;
            ny = v[num].second;
            while (true)
            {
                nx += dx[(i + 1) % 4];
                ny += dy[(i + 1) % 4];
                if (nx < 0 || nx >= n || ny < 0 || ny >= m)
                    break;
                if (board[nx][ny] == 6)
                    break;
                vis[nx][ny]--;
            }
        }
    }
    else if (board[v[num].first][v[num].second] == 4)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int i = 0; i < 4; i++)
            {
                if(i == j) continue;
                int nx = v[num].first;
                int ny = v[num].second;
                while (true)
                {
                    nx += dx[i];
                    ny += dy[i];
                    if (nx < 0 || nx >= n || ny < 0 || ny >= m)
                        break;
                    if (board[nx][ny] == 6)
                        break;
                    vis[nx][ny]++;
                }
            }
            func(num + 1);
            for (int i = 0; i < 4; i++)
            {
                if(i == j) continue;
                int nx = v[num].first;
                int ny = v[num].second;
                while (true)
                {
                    nx += dx[i];
                    ny += dy[i];
                    if (nx < 0 || nx >= n || ny < 0 || ny >= m)
                        break;
                    if (board[nx][ny] == 6)
                        break;
                    vis[nx][ny]--;
                }
            }
        }
    }
    else if (board[v[num].first][v[num].second] == 5)
    {
        for (int i = 0; i < 4; i++)
        {
            int nx = v[num].first;
            int ny = v[num].second;
            while (true)
            {
                nx += dx[i];
                ny += dy[i];
                if (nx < 0 || nx >= n || ny < 0 || ny >= m)
                    break;
                if (board[nx][ny] == 6)
                    break;
                vis[nx][ny]++;
            }
        }
        func(num + 1);
        for (int i = 0; i < 4; i++)
        {
            int nx = v[num].first;
            int ny = v[num].second;
            while (true)
            {
                nx += dx[i];
                ny += dy[i];
                if (nx < 0 || nx >= n || ny < 0 || ny >= m)
                    break;
                if (board[nx][ny] == 6)
                    break;
                vis[nx][ny]--;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> board[i][j];
            if(board[i][j] != 0) vis[i][j] = 1;
            if(board[i][j] != 0 && board[i][j] != 6) {
                v.push_back({i, j});
            }
        }
    }
    func(0);
    cout << result;
}

/*
노다가 구현 문제인듯함.
*/