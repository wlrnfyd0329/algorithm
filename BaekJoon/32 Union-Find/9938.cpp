#include <iostream>
#include <string.h>
#include <vector>
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

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

void reset() {
    memset(board, -1, sizeof(board));
}

void isOut(Robot &o) {
    if (o.r == 0 || o.r == 1 || o.r == 2) reset();
}

bool go_down(Robot &o) {
    int ddx[3] = {1, 1, 2};
    int ddy[3] = {-1, 1, 0};
    for(int i = 0; i < 3; i++) {
        int nx = o.r + ddx[i];
        int ny = o.c + ddy[i];
        if (nx >= R || ny < 0 || ny >= C) return false;
        if (board[nx][ny] >= 0) return false;
    }
    o.r += 1;
    return true;
}

bool go_left(Robot &o) {
    int ddx[5] = {-1, 1, 0, 1, 2};
    int ddy[5] = {-1, -1, -2, -2, -1};
    for(int i = 0; i < 5; i++) {
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

bool go_right(Robot &o) {
    int ddx[5] = {-1, 1, 0, 1, 2};
    int ddy[5] = {1, 1, 2, 2, 1};
    for(int i = 0; i < 5; i++) {
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

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    reset();
    cin >> R >> C >> K;
    R += 2;
    for(int i = 1; i <= K; i++) {
        int c, d;
        cin >> c >> d;
        robot.push_back({0, c, d, i});
    }
}