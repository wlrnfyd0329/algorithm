#include <iostream>
#include <queue>
#include <algorithm>
#define X first
#define Y second

using namespace std;

int n, result;
queue<pair<int, int>> q;
int board[305][305];
int vis[305][305];
int dx[8] = {1, 1, 1, 0, 0, -1, -1, -1};
int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

void init() {
    fill(vis[0], vis[304], 0);
    result = 0;
}

void input() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for(int j = 0; j < n; j++) {
            if (s[j] == '*') board[i][j] = -1;
            else {
                result++;
                board[i][j] = 0;
            }
        }
    }
}

void check_mine() {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if (board[i][j] == -1) continue;
            int cnt = 0;
            for(int k = 0; k < 8; k++) {
                int nx = i + dx[k];
                int ny = j + dy[k];
                if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
                if (board[nx][ny] == -1) cnt++;
            }
            board[i][j] = cnt;
            if (cnt == 0) q.push({i, j});
        }
    }
}

void decide_result() {
    while(!q.empty()) {
        auto cur = q.front(); q.pop();
        if (vis[cur.X][cur.Y]) continue;
        queue<pair<int, int>> tq;
        tq.push({cur.X, cur.Y});
        vis[cur.X][cur.Y] = 1;
        while(!tq.empty()) {
            auto tcur = tq.front(); tq.pop();
            for(int k = 0; k < 8; k++) {
                int nx = tcur.X + dx[k];
                int ny = tcur.Y + dy[k];
                if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
                if (vis[nx][ny] || board[nx][ny] == -1) continue;
                if (board[nx][ny] == 0) {
                    tq.push({nx, ny});
                } 
                vis[nx][ny] = 1;
                result--;
            }
        }
    }
}

void print() {
    cout << "\n";
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";

    cout << "\n";
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << vis[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        init();
        input();
        check_mine();
        decide_result();
        cout << "#" << tc << " " << result << "\n";
    }
}