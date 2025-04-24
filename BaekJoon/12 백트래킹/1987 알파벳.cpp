#include <iostream>
#include <algorithm>
#include <string>
#define endl "\n"

using namespace std;

int R, C, ans;
int board[25][25];
bool vis[25][25];
bool vis_alpha[26];

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

inline int c2i(char c) {
    return c - 'A';
}

void dfs(int x, int y, int dist) {
    ans = max(ans, dist);

    for(int dir = 0; dir < 4; dir++) {
        int nx = x + dx[dir];
        int ny = y + dy[dir];
        if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue;
        if (vis[nx][ny] || vis_alpha[board[nx][ny]]) continue;
        vis_alpha[board[nx][ny]] = 1;
        dfs(nx, ny, dist + 1);
        vis_alpha[board[nx][ny]] = 0;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ans = 0;
    cin >> R >> C;
    for(int r = 0; r < R; r++) {
        string s; cin >> s;
        for(int c = 0; c < C; c++) {
            board[r][c] = c2i(s[c]);
        }
    }

    vis_alpha[board[0][0]] = 1;
    dfs(0, 0, 1);

    cout << ans;
}   