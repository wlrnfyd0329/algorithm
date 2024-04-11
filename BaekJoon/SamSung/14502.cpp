#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int n, m, result;
int board[10][10];
int vis[10][10];
int vvis[10][10];
queue<pair<int, int>> Q, cQ;
vector<pair<int, int>> v;
vector<int> cv;

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

void reset() {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            vvis[i][j] = vis[i][j];
        }
    }
    cQ = Q;
}

int bfs() {
    int cnt = 0;
    while(!cQ.empty()) {
        auto cur = cQ.front(); cQ.pop();
        for(int i = 0; i < 4; i++) {
            int nx = cur.first + dx[i];
            int ny = cur.second + dy[i];
            if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if(board[nx][ny] == 1 || vvis[nx][ny]) continue;
            vvis[nx][ny] = 2;
            cQ.push({nx, ny});
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(vvis[i][j] == 0) cnt++;
        }
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> board[i][j];
            if(board[i][j] == 2) {
                Q.push({i, j});
                vis[i][j] = 2;
            }
            else if(board[i][j] == 1) {
                vis[i][j] = 1;
            }
            else {
                v.push_back({i, j});
                cv.push_back(1);
            }
        }
    }
    cv[0] = 0;
    cv[1] = 0;
    cv[2] = 0;
    do {
        reset();
        for(int i = 0; i < cv.size(); i++) {
            if(cv[i] == 0) vvis[v[i].first][v[i].second] = 1;
        }
        result = max(result, bfs());
    } while(next_permutation(cv.begin(), cv.end()));

    cout << result;
}

/*
백트레킹과 bfs를 적절히 사용하는 문제였다.
cQ = Q에서 알 수 있듯이 깊은 복사다.
*/