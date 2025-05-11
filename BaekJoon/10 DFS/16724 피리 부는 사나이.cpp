// 깊이 우선 탐색을 하며 사이클의 개수를 찾으면 되는 문제였다.
// 이때, 사이클의 번호를 붙이며 탐색을 하는데, 
// 다른 사이클에 합류 될때는 사이클의 개수에 포함하면 안된다.

#include <iostream>
#include <string>
#include <vector>
#define X first
#define Y second
#define endl "\n"

using namespace std;

int n, m, ans;
int board[1005][1005];
int vis[1005][1005];

int dx[4] = {1, 0, -1, 0}; // D, R, U, L
int dy[4] = {0, 1, 0, -1};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for(int j = 0; j < m; j++) {
            if (s[j] == 'D') {
                board[i][j] = 0;
            }
            else if (s[j] == 'R') {
                board[i][j] = 1;
            }
            else if (s[j] == 'U') {
                board[i][j] = 2;
            }
            else {
                board[i][j] = 3;
            }
        }
    }

    int flag = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if (vis[i][j]) continue;
            flag++;
            pair<int, int> cur = {i, j};
            while(1) {
                if (vis[cur.X][cur.Y]) {
                    if (vis[cur.X][cur.Y] == flag) ans++;
                    break;
                }
                vis[cur.X][cur.Y] = flag;
                int dir = board[cur.X][cur.Y];
                cur.X += dx[dir];
                cur.Y += dy[dir];
            }
        }
    }

    cout << ans;
}