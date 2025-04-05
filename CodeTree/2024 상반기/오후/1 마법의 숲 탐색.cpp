// 오기 부리지 말고 문제에서 주어진 조건을 항상 다 담을 수 있도록 구현하자
// 3칸이 필요한데 2칸만 주었다가 틀렸다
// => 시작하자마자 움직일 수 없는 경우에는 옆으로 가는걸 검사해야 하는데 2칸이면 윗칸을 검사할 수 없다

#include <iostream>
#include <string.h>
#include <vector>
#include <queue>
#define X first
#define Y second

using namespace std;

int R, C, K, ans = 0;
int board[75][75];
struct Robot {
    int r;
    int c;
    int d;
    int id;
};
vector<Robot> robot;

int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

void reset() {
    memset(board, -1, sizeof(board));
}

bool isOut(Robot& o) {
    if (o.r == 1 || o.r == 2 || o.r == 3) {
        reset();
        return true;
    }
    return false;
}

bool go_down(Robot& o) {
    int ddx[3] = { 1, 1, 2 };
    int ddy[3] = { -1, 1, 0 };
    for (int i = 0; i < 3; i++) {
        int nx = o.r + ddx[i];
        int ny = o.c + ddy[i];
        if (nx >= R || ny < 0 || ny >= C) return false;
        if (board[nx][ny] >= 0) return false;
    }
    o.r += 1;
    return true;
}

bool go_left(Robot& o) {
    int ddx[5] = { -1, 1, 0, 1, 2 };
    int ddy[5] = { -1, -1, -2, -2, -1 };
    for (int i = 0; i < 5; i++) {
        int nx = o.r + ddx[i];
        int ny = o.c + ddy[i];
        if (nx >= R || ny < 0 || ny >= C) return false;
        if (board[nx][ny] >= 0) return false;
    }
    o.r += 1;
    o.c -= 1;
    if (--o.d < 0) o.d = 3;
    return true;
}

bool go_right(Robot& o) {
    int ddx[5] = { -1, 1, 0, 1, 2 };
    int ddy[5] = { 1, 1, 2, 2, 1 };
    for (int i = 0; i < 5; i++) {
        int nx = o.r + ddx[i];
        int ny = o.c + ddy[i];
        if (nx >= R || ny < 0 || ny >= C) return false;
        if (board[nx][ny] >= 0) return false;
    }
    o.r += 1;
    o.c += 1;
    if (++o.d > 3) o.d = 0;
    return true;
}

void arrive(Robot& o) {
    board[o.r][o.c] = o.id;
    for (int dir = 0; dir < 4; dir++) {
        board[o.r + dx[dir]][o.c + dy[dir]] = o.id;
    }
}

void move(Robot& o) {
    int vis[75][75] = { 0, };
    int res = 0;
    queue<pair<int, int>> q;
    q.push({o.r, o.c});
    vis[o.r][o.c] = 1;
    while (!q.empty()) {
        auto cur = q.front(); q.pop();
        res = max(res, cur.X);
        int id = board[cur.X][cur.Y];
        int ex = robot[id].r + dx[robot[id].d];
        int ey = robot[id].c + dy[robot[id].d];
        for (int dir = 0; dir < 4; dir++) {
            int nx = cur.X + dx[dir];
            int ny = cur.Y + dy[dir];
            if (nx < 3 || nx >= R || ny < 0 || ny >= C) continue;
            if (vis[nx][ny] || board[nx][ny] < 0) continue;
            if (board[nx][ny] != id && !(cur.X == ex && cur.Y == ey))  continue;
            vis[nx][ny] = 1;
            q.push({ nx, ny });            
        }
    }

    ans += res - 2;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    reset();
    cin >> R >> C >> K;
    R += 3;
    for (int i = 0; i < K; i++) {
        int c, d;
        cin >> c >> d;
        robot.push_back({ 1, c - 1, d, i });
    }

    for (int i = 0; i < K; i++) {
        while (1) {
            if (!go_down(robot[i]))
                if (!go_left(robot[i]))
                    if (!go_right(robot[i]))
                        break;
        }
        arrive(robot[i]);
        if(!isOut(robot[i]))
            move(robot[i]);
    }

    cout << ans;
}
