#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int vis[10][10][10];
int check[10][10];
vector<pair<int, int>> cctv;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
int min_value = 100;
int n, m;

void check_and_reset() {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (vis[cctv.size()][i][j] == 0) {
                cnt++;
            }
        }
    }

    if (min_value > cnt) {
        min_value = cnt;
    }
}

void vischeck_reset() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            check[i][j] = 0;
        }
    }
}

void func(int index) {
    if (index == (int)cctv.size()) {
        check_and_reset();
        return;
    }
    int x = cctv[index].first;
    int y = cctv[index].second;

    if (vis[0][x][y] == 1) {
        for(int i = 0; i < 4; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < m; k++) {
                    vis[index+1][j][k] = vis[index][j][k];
                }
            }
            int curx = x;
            int cury = y;
            vischeck_reset();
            check[curx][cury] = -1;
            while(true) {
                curx += dx[i];
                cury += dy[i];
                if (curx < 0 || curx >= n || cury < 0 || cury >= m) break;
                if (vis[0][curx][cury] == 6 || check[curx][cury] == -1) break;
                if (vis[0][curx][cury] == 0) vis[index + 1][curx][cury] = 7;
                check[curx][cury] = -1;
            }
            func(index+1);
        }
    }
    else if (vis[0][x][y] == 2) {
        for(int i = 0; i < 2; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < m; k++) {
                    vis[index+1][j][k] = vis[index][j][k];
                }
            }
            for (int j = i; j < i + 3; j += 2) {
                int curx = x;
                int cury = y;
                vischeck_reset();
                check[curx][cury] = -1;
                while(true) {
                    curx += dx[j];
                    cury += dy[j];
                    if (curx < 0 || curx >= n || cury < 0 || cury >= m) break;
                    if (vis[0][curx][cury] == 6 || check[curx][cury] == -1) break;
                    if (vis[0][curx][cury] == 0) vis[index + 1][curx][cury] = 7;
                    check[curx][cury] = -1;
                }
            }
            func(index+1);
        }
    }
    else if (vis[0][x][y] == 3) {
        for(int i = 0; i < 4; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < m; k++) {
                    vis[index+1][j][k] = vis[index][j][k];
                }
            }
            for (int j = i; j < i + 2; j++) {
                int curx = x;
                int cury = y;
                vischeck_reset();
                check[curx][cury] = -1;
                while(true) {
                    curx += dx[j % 4];
                    cury += dy[j % 4];
                    if (curx < 0 || curx >= n || cury < 0 || cury >= m) break;
                    if (vis[0][curx][cury] == 6 || check[curx][cury] == -1) break;
                    if (vis[0][curx][cury] == 0) vis[index + 1][curx][cury] = 7;
                    check[curx][cury] = -1;
                }
            }
            func(index+1);
        }
    }
    else if (vis[0][x][y] == 4) {
        for(int i = 0; i < 4; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < m; k++) {
                    vis[index+1][j][k] = vis[index][j][k];
                }
            }
            for (int j = i; j < i + 3; j++) {
                int curx = x;
                int cury = y;
                vischeck_reset();
                check[curx][cury] = -1;
                while(true) {
                    curx += dx[j % 4];
                    cury += dy[j % 4];
                    if (curx < 0 || curx >= n || cury < 0 || cury >= m) break;
                    if (vis[0][curx][cury] == 6 || check[curx][cury] == -1) break;
                    if (vis[0][curx][cury] == 0) vis[index + 1][curx][cury] = 7;
                    check[curx][cury] = -1;
                }
            }
            func(index+1);
        }
    }
    else if (vis[0][x][y] == 5) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                vis[index+1][i][j] = vis[index][i][j];
            }
        }
        for(int i = 0; i < 4; i++) {
           int curx = x;
            int cury = y;
            vischeck_reset();
            check[curx][cury] = -1;
            while(true) {
                curx += dx[i];
                cury += dy[i];
                if (curx < 0 || curx >= n || cury < 0 || cury >= m) break;
                if (vis[0][curx][cury] == 6 || check[curx][cury] == -1) break;
                if (vis[0][curx][cury] == 0) vis[index + 1][curx][cury] = 7;
                check[curx][cury] = -1;
            }
        }
        func(index+1);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> vis[0][i][j];
            if (vis[0][i][j] != 0 && vis[0][i][j] != 6) {
                cctv.push_back({i, j});
            }
        }
    }
    func(0);

    cout << min_value;
}