#include <iostream>
#include <queue>

using namespace std;

struct shark {
    int s;
    int d;
    int z;
} arr[105][105];

int r, c, m, result;
queue<pair<int, int>> shark_coordi;
int dx[5] = {0, -1, 1, 0, 0};
int dy[5] = {0, 0, 0, 1, -1};

void init() {
    for(int i = 1; i <= r; i++) {
        for(int j = 1; j <= c; j++) {
            arr[i][j] = {0, 0, 0};
        }
    }
    result = 0;
}

void catchShark(int index) {
    for(int i = 1; i <= r; i++) {
        if(arr[i][index].z > 0) {
            result += arr[i][index].z;
            arr[i][index] = {0, 0, 0};
            break;
        }
    }
}

void moveShark() {
    shark new_shark_arr[105][105];
    for(int i = 1; i <= r; i++) {
        for(int j = 1; j <= c; j++) {
            new_shark_arr[i][j] = {0, 0, 0};
        }
    }
    vector<pair<int, int>> new_shark_coordi;
    while(!shark_coordi.empty()) {
        auto cur = shark_coordi.front(); shark_coordi.pop();
        if (arr[cur.first][cur.second].z == 0) continue;
        int nx = cur.first;
        int ny = cur.second;
        if (arr[cur.first][cur.second].s / c == 0) {
            nx += dx[arr[cur.first][cur.second].d] * arr[cur.first][cur.second].s;
            ny += dy[arr[cur.first][cur.second].d] * arr[cur.first][cur.second].s;
        }
        else {
            if (arr[cur.first][cur.second].s / c % 2 == 0) { // 짝수
                nx += dx[arr[cur.first][cur.second].d] * arr[cur.first][cur.second].s;
                ny += dy[arr[cur.first][cur.second].d] * arr[cur.first][cur.second].s;
            }
            else { // 홀수
                nx -= dx[arr[cur.first][cur.second].d] * arr[cur.first][cur.second].s;
                ny -= dy[arr[cur.first][cur.second].d] * arr[cur.first][cur.second].s;  
            }
        }
        for (int i = 0; i < arr[cur.first][cur.second].s; i++) {
            nx += dx[arr[cur.first][cur.second].d];
            ny += dy[arr[cur.first][cur.second].d];
            if (nx < 1 || nx > r) {
                nx -= dx[arr[cur.first][cur.second].d] * 2;
                ny -= dy[arr[cur.first][cur.second].d] * 2;
                if (arr[cur.first][cur.second].d == 1) {
                    arr[cur.first][cur.second].d = 2;
                }
                else {
                    arr[cur.first][cur.second].d = 1;
                }
            }
            if (ny < 1 || ny > c) {
                nx -= dx[arr[cur.first][cur.second].d] * 2;
                ny -= dy[arr[cur.first][cur.second].d] * 2;
                if (arr[cur.first][cur.second].d == 3) {
                    arr[cur.first][cur.second].d = 4;
                }
                else {
                    arr[cur.first][cur.second].d = 3;
                }
            }
        } 
        if (new_shark_arr[nx][ny].z > 0) {
            if(new_shark_arr[nx][ny].z < arr[cur.first][cur.second].z) {
                new_shark_arr[nx][ny] = arr[cur.first][cur.second];
            }
        }
        else {
            new_shark_arr[nx][ny] = arr[cur.first][cur.second];
            new_shark_coordi.push_back({nx, ny});
        }
        arr[cur.first][cur.second] = {0, 0, 0};
    }

    for(auto k : new_shark_coordi) {
        arr[k.first][k.second] = new_shark_arr[k.first][k.second];
        shark_coordi.push({k.first, k.second});
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> r >> c >> m;
    init();
    for (int i = 0; i < m; i++) {
        int x, y, s, d, z;
        cin >> x >> y >> s >> d >> z;
        arr[x][y] = {s, d, z};
        shark_coordi.push({x, y});
    }
    for (int man = 1; man <= c; man++) {
        catchShark(man);
        moveShark();
    }

    cout << result;
}