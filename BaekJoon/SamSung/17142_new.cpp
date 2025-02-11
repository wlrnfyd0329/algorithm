// 0.25초면 25,000,000번 연산 가능
// 최악의 경우 50 * 50 = 2500번을 10,000번 남아서 그냥 구현해도 문제 없다.
// 근데 bfs 진행을 할때, 끝났을 때, 

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int n, m, result = 3000;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
int board[55][55];
int vis[55][55];
int choose[10];
vector<pair<int, int>> v;
queue<pair<int, int>> q;

int bfs() {
    int time = 0;
    while(!q.empty()) {
        auto cur = q.front(); q.pop();
        if (board[cur.first][cur.second] != 2) time = vis[cur.first][cur.second];
        for (int i = 0; i < 4; i++) {
            int nx = cur.first + dx[i];
            int ny = cur.second + dy[i];
            if(nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
            if(board[nx][ny] == 1 || vis[nx][ny] != 0) continue;
            vis[nx][ny] = vis[cur.first][cur.second] + 1;
            q.push({nx, ny});
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (vis[i][j] == 0 && board[i][j] == 0) {
                return -1;
            }
        }
    }

    if (time == 0) return 0;
    else return time - 1;
}

void func(int cnt, int depth) {
    if (cnt == m || depth == v.size()) {
        if (cnt == m) {
            fill(vis[0], vis[54], 0);
            for (int i = 0; i < v.size(); i++) {
                if (choose[i]) {
                    vis[v[i].first][v[i].second] = 1;
                    q.push(v[i]);
                }
            }
            int tmp = bfs();
            if (tmp >= 0) {
                result = min(result, tmp);
            }
        }
        return; 
    }
    choose[depth] = 1;
    func(cnt + 1, depth + 1);
    choose[depth] = 0;
    func(cnt, depth + 1);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> board[i][j];
            if (board[i][j] == 2) {
                v.push_back({i, j});
            }
        }
    }

    func(0, 0);
    cout << ((result==3000)?-1:result);
}