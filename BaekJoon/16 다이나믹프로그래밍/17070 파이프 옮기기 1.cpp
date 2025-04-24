#include <iostream>
#include <vector>
#define endl "\n"

using namespace std;

int N;
int board[20][20];
int vis[3][20][20];

void go_right(int x, int y, int k) {
    int ny = y + 1;
    if (x < 0 || x >= N || ny < 0 || ny >= N) return;
    if (board[x][ny] == 0) {
        vis[0][x][ny] += vis[k][x][y];
    }
}

void go_cross(int x, int y, int k) {
    int dx[3] = {0, 1, 1};
    int dy[3] = {1, 0, 1};
    for(int i = 0; i < 3; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < 0 || nx >= N || ny < 0 || ny >= N) return;
        if (board[nx][ny] == 1) return;
    }
    vis[1][x + dx[2]][y + dy[2]] += vis[k][x][y];
}

void go_down(int x, int y, int k) {
    int nx = x + 1;
    if (nx < 0 || nx >= N || y < 0 || y >= N) return;
    if (board[nx][y] == 0) {
        vis[2][nx][y] += vis[k][x][y];
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> board[i][j];
        }
    }

    vis[0][0][1] = 1;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            for(int k = 0; k < 3; k++) {
                if (vis[k][i][j] > 0) {
                    if (k == 0) {
                        go_right(i, j, k);
                        go_cross(i, j, k);
                    }
                    else if (k == 1) {
                        go_right(i, j, k);
                        go_cross(i, j, k);
                        go_down(i, j, k);
                    }
                    else if (k == 2) {
                        go_down(i, j, k);
                        go_cross(i, j, k);
                    }
                }
            }
        }
    }

    cout << vis[0][N - 1][N - 1] + vis[1][N - 1][N - 1] + vis[2][N - 1][N - 1];
}