#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
int board[105][105];
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, -1, 0, 1};

void inCoordi(int x, int y) {
    if (x >= 0 && x <= 100 && y >= 0 && y <= 100) {
        board[x][y] = 1;
    }
}

void dragon(int x, int y, int d, int g) {
    inCoordi(x, y);
    int nx = x + dx[d];
    int ny = y + dy[d];
    inCoordi(nx, ny);
    vector<int> vdir;
    vdir.push_back(d);
    for(int i = 1; i <= g; i++) {
        for(int j = vdir.size() - 1; j >= 0; j--) {
            int dir = (vdir[j] + 1) % 4;
            nx += dx[dir];
            ny += dy[dir];
            inCoordi(nx, ny);
            vdir.push_back(dir);
        }
    }
}

int check() {
    int result = 0;
    for(int i = 0; i < 100; i++) {
        for(int j = 0; j < 100; j++) {
            if (board[i][j] && board[i + 1][j] && board[i][j + 1] && board[i + 1][j + 1]) {
                result++;
            }
        }
    }
    return result;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y, d, g;
        cin >> x >> y >> d >> g;
        dragon(x, y, d, g);
    }

    cout << check();
}