#include <iostream>
#include <deque>
#include <algorithm>

using namespace std;

int n, timer, ssize = 2, eat = 2;
bool isEat = false;
int board[25][25];
int vis[25][25];
deque<pair<int, int>> DQ, Q;

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

void dist() {
    fill(vis[0], vis[24], 0);
    int tmp = -1;
    vis[Q.front().first][Q.front().second] = 1;
    while(!Q.empty()) {
        auto cur = Q.front(); Q.pop_front();
        if(vis[cur.first][cur.second] == tmp) break;
        for(int i = 0; i < 4; i++) {
            int nx = cur.first + dx[i];
            int ny = cur.second + dy[i];
            if(nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
            if(vis[nx][ny] || board[nx][ny] > ssize) continue;
            if(board[nx][ny] > 0 && board[nx][ny] < ssize) {
                DQ.push_back({nx, ny});
                tmp = vis[cur.first][cur.second] + 1;
            }
            vis[nx][ny] = vis[cur.first][cur.second] + 1;
            Q.push_back({nx, ny});
        }
    }
    Q.clear();
    sort(DQ.begin(), DQ.end());
}

void check() {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(board[i][j] != 0 && board[i][j] != 9 && board[i][j] <= ssize) {
                DQ.push_back({i, j});
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> board[i][j];
            if(board[i][j] == 9) {
                board[i][j] = 0;
                Q.push_back({i, j});
            }
        }
    }

    while(true) {
        dist();
        if(DQ.size() == 0) break;
        board[DQ.front().first][DQ.front().second] = 0;
        Q.push_back({DQ.front().first, DQ.front().second});
        eat--;
        if(eat == 0) {
            ssize++;
            eat = ssize;
        }
        timer += vis[DQ.front().first][DQ.front().second] - 1;
        DQ.clear();
    }

    cout << timer;
}

/*
bfs 활용 문제다.
문제를 잘 따라가면 이상 없다.
*/