#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int n, m, result = 2100000000;
vector<int> vir;
vector<pair<int, int>> pvir;
queue<pair<int, int>> Q;
int board[55][55];
int vis[55][55];

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

int bfs() {
    int timer = 0;
    while(!Q.empty()){
        auto cur = Q.front(); Q.pop();
        if (board[cur.first][cur.second] != 2) timer = vis[cur.first][cur.second];
        for(int i = 0; i < 4; i++) {
            int nx = cur.first + dx[i];
            int ny = cur.second + dy[i];
            if(nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
            if(board[nx][ny] == 1 || vis[nx][ny]) continue;
            vis[nx][ny] = vis[cur.first][cur.second] + 1;
            Q.push({nx, ny});
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(vis[i][j] == 0 && board[i][j] == 0) {
                fill(vis[0], vis[54], 0);
                return -1;
            }
        }
    }

    fill(vis[0], vis[54], 0);
    if(timer == 0) return 0;
    else return timer - 1;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> board[i][j];
            if(board[i][j] == 2) {
                pvir.push_back({i, j});
                vir.push_back(1);
            }
        }
    }
    for(int i = 0; i < m; i++) {
        vir[i] = 0;
    }

    do {
        for(int i = 0; i < vir.size(); i++) {
            if(vir[i] == 0) {
                Q.push({pvir[i].first, pvir[i].second});
                vis[pvir[i].first][pvir[i].second] = 1;
            }
        }
        int temp = bfs();
        if(temp >= 0) {
            result = min(result, temp);
        }
    } while(next_permutation(vir.begin(), vir.end()));

    if(result == 2100000000) cout << -1;
    else cout << result;
}

/*
독이 전부 퍼지지 않았을 경우와
바이러스가 마지막에 존재하면 시간은 기록할 필요가 없는것을
잘 생각하고 해결해야 한다.
*/