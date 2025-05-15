#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <cstring>
#define X first
#define Y second
#define endl "\n"

using namespace std;

int n, m;
int board[1005][1005];
int vis[1005][1005];
vector<int> vis_cnt;
queue<pair<int, int>> q;

int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        for (int j = 0; j < m; j++) {
            board[i][j] = s[j] - '0';
        }
    }

    memset(vis, -1, sizeof(vis));
    int area = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (board[i][j] || vis[i][j] >= 0) continue;
            q.push({ i, j });
            vis[i][j] = area;
            int cnt = 1;
            while (!q.empty()) {
                auto cur = q.front(); q.pop();

                for (int dir = 0; dir < 4; dir++) {
                    int nx = cur.X + dx[dir];
                    int ny = cur.Y + dy[dir];
                    if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                    if (board[nx][ny] || vis[nx][ny] >= 0) continue;
                    cnt++;
                    vis[nx][ny] = area;
                    q.push({ nx, ny });
                }
            }

            vis_cnt.push_back(cnt);
            area++;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!board[i][j]) {
                cout << 0;
                continue;
            }
            int cnt = 1;
            
            set<int> s;
            for (int dir = 0; dir < 4; dir++) {
                int nx = i + dx[dir];
                int ny = j + dy[dir];
                if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                if (vis[nx][ny] < 0) continue;
                s.insert(vis[nx][ny]);
            }

            for(auto k : s) {
                cnt += vis_cnt[k];
            }
            cout << cnt % 10;
        }
        cout << endl;
    }
}