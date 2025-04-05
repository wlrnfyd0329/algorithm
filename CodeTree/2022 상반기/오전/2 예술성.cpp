// 회전이 중요한 문제였다.

#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
#define X first
#define Y second

using namespace std;

int n, ans = 0;
int board[30][30];
int vis[30][30];

int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };

struct Group
{
    int cnt;
    int num;
    vector<int> line;
};
vector<Group> group;

void init() {
    group.clear();
    for (int i = 0; i < n; i++) {
        memset(vis[i], 0, sizeof(int) * n);
    }
}

void spilt_group() {
    int group_num = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (vis[i][j]) continue;
            queue<pair<int, int>> q;
            int cnt = 1;
            q.push({ i, j });
            vis[i][j] = group_num++;
            while (!q.empty()) {
                auto cur = q.front(); q.pop();
                for (int dir = 0; dir < 4; dir++) {
                    int nx = cur.X + dx[dir];
                    int ny = cur.Y + dy[dir];
                    if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
                    if (vis[nx][ny] || board[nx][ny] != board[cur.X][cur.Y]) continue;
                    vis[nx][ny] = vis[cur.X][cur.Y];
                    cnt++;
                    q.push({ nx, ny });
                }
            }
            group.push_back({ cnt, board[i][j] });
        }
    }

    for (int i = 0; i < group.size(); i++) {
        group[i].line = vector<int>(group.size(), 0);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int dir = 0; dir < 4; dir++) {
                int nx = i + dx[dir];
                int ny = j + dy[dir];
                if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
                if (vis[nx][ny] == vis[i][j]) continue;
                group[vis[i][j] - 1].line[vis[nx][ny] - 1]++;
            }
        }
    }
}

int caluate_group() {
    int score = 0;
    for (int i = 0; i < group.size(); i++) {
        for (int j = i + 1; j < group.size(); j++) {
            score += (group[i].cnt + group[j].cnt) * group[i].num * group[j].num * group[i].line[j];
        }
    }
    return score;
}

void rotation() {
    int temp[30][30];

    for (int i = 0; i < n; i++) {
        temp[n / 2][i] = board[i][n / 2];
    }
    for (int i = 0; i < n; i++) {
        temp[n - i - 1][n / 2] = board[n / 2][i];
    }

    for (int i = 0; i < n / 2; i++) {
        for (int j = 0; j < n / 2; j++) {
            temp[j][n / 2 - i - 1] = board[i][j];
        }
    }
    for (int i = 0; i < n / 2; i++) {
        for (int j = n / 2 + 1; j < n; j++) {
            temp[j - n / 2 - 1][n - i - 1] = board[i][j];
        }
    }
    for (int i = n / 2 + 1; i < n; i++) {
        for (int j = 0; j < n / 2; j++) {
            temp[j + n / 2 + 1][n - i - 1] = board[i][j];
        }
    }
    for (int i = n / 2 + 1; i < n; i++) {
        for (int j = n / 2 + 1; j < n; j++) {
            temp[j][n + n / 2 - i] = board[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            board[i][j] = temp[i][j];
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> board[i][j];
        }
    }

    for(int i = 0; i < 4; i++) {
        init();
        spilt_group();
        ans += caluate_group();
        rotation();
    }

    cout << ans;
}