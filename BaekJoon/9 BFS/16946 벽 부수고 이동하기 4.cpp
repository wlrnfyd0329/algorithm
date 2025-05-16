// 처음엔 bfs 하면서 또 bfs를 하니까 O(NM * NM) 이라서 시간초과가 났다.
// 그래서 각 vis에 최댓값을 저장하는 방식으로 하니까 
// 그래도 vector 새로 업데이트해야할 최댓값을 저장하고 업데이트 하는 과정이 오래걸려서 시간초과가 났고
// 영역을 표시하고 각 영역의 최댓값을 캐싱하는 방식으로 진행하였다.
// 또한 벽일때, 4방향의 빈칸의 최댓값을 더하는 데, 같은 영역이라면 중복해서 더하면 안되니까
// vector를 이용해서 체크하고 초기화하는 것을 반복했더니 시간초과가 났고 
// set을 이용해서 중복되는 값을 걸렸더니 해결할 수 있었다.

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