#include <iostream>
#include <vector>

using namespace std;

int r, c, t, result;
int a[55][55];
int tmp[55][55];
vector<pair<int, int>> v;
vector<int> clean;

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

void dust() {
    fill(tmp[0], tmp[54], 0);
    for(auto k : v) {
        int cnt = 0;
        for(int i = 0; i < 4; i++) {
            int nx = k.first + dx[i];
            int ny = k.second + dy[i];
            if(nx < 0 || nx >= r || ny < 0 || ny >= c) continue;
            if(a[nx][ny] == -1) continue;
            cnt++;
        }
        for(int i = 0; i < 4; i++) {
            int nx = k.first + dx[i];
            int ny = k.second + dy[i];
            if(nx < 0 || nx >= r || ny < 0 || ny >= c) continue;
            if(a[nx][ny] == -1) continue;
            tmp[nx][ny] += a[k.first][k.second] / 5;
        }
        tmp[k.first][k.second] += a[k.first][k.second] - (a[k.first][k.second] / 5) * cnt;
    }

    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            if(a[i][j] == -1) continue;
            a[i][j] = tmp[i][j];
        }
    }
}

void cleaning(int x, int dir) {
    if(dir == -1) {
        for(int i = x - 2; i >= 0; i--) {
            a[i+1][0] = a[i][0];
        }
        for(int i = 1; i < c; i++) {
            a[0][i - 1] = a[0][i];
        }
        for(int i = 1; i <= x; i++) {
            a[i - 1][c - 1] = a[i][c - 1];
        }
        for(int i = c - 2; i > 0; i--) {
            a[x][i + 1] = a[x][i];
        }
    }
    if(dir == 1) {
        for(int i = x + 2; i < r; i++) {
            a[i - 1][0] = a[i][0];
        }
        for(int i = 1; i < c; i++) {
            a[r - 1][i - 1] = a[r - 1][i];
        }
        for(int i = r - 2; i >= x; i--) {
            a[i + 1][c - 1] = a[i][c -1];
        }
        for(int i = c - 2; i > 0; i--) {
            a[x][i + 1] = a[x][i];
        }
    }
    a[x][1] = 0;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> r >> c >> t;
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            cin >> a[i][j];
            if(a[i][j] != 0 && a[i][j] != -1) v.push_back({i, j});
            if(a[i][j] == -1) clean.push_back(i);
        }
    }

    while(t--) {
        dust();
        cleaning(clean[0], -1);
        cleaning(clean[1], 1);
        v.clear();
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if(a[i][j] != 0 && a[i][j] != -1) v.push_back({i,j});
            }

        }
    }



    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            if(a[i][j] == -1) continue;
            result += a[i][j];
        }
    }

    cout << result;

}

/*
bfs 활용 문제 인듯하다
*/