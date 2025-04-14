#include <iostream>
#include <algorithm>

using namespace std;

int n, m, min_cnt = 15;
int board[11][15][15];
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
pair<int, int> red[11];
pair<int, int> blue[11];
bool in_red = false;
bool in_blue = false;

void reset(int index) {
    in_red = false;
    in_blue = false;
    red[index] = red[index-1];
    blue[index] = blue[index-1];
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            board[index][i][j] = board[index-1][i][j];
        }
    }
}

bool tilt(int x, int y, int dir, int index, bool isRed) {
    int nx = x;
    int ny = y;
    while(true) {
        nx += dx[dir];
        ny += dy[dir];
        if (board[index][nx][ny] != 0) break;
        board[index][nx - dx[dir]][ny - dy[dir]] = 0;
        if (isRed) {
            board[index][nx][ny] = 1;
            red[index] = {nx, ny};
        }
        else {
            board[index][nx][ny] = 2;
            blue[index] = {nx, ny};
        }
    }
    if (board[index][nx][ny] == 5) {
        board[index][nx - dx[dir]][ny - dy[dir]] = 0;
        return true;
    }
    else {
        return false;
    }
}

void print(int index) {
    cout << index << " " << in_red << " " << in_blue << "\n";
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if (board[index][i][j] == -1) {
                cout << '#';
            }
            else if (board[index][i][j] == 1) {
                cout << 'R';
            } 
            else if (board[index][i][j] == 2) {
                cout << 'B';
            } 
            else if (board[index][i][j] == 5) {
                cout << 'O';
            } 
            else {
                cout << '.';
            }
        }
        cout << "\n";
    }
    cout << "\n";
}

void func(int index) {
    if (index == 11) {
        return;
    }
    for(int i = 0; i < 4; i++) {
        reset(index);
        int rx = red[index].first;
        int ry = red[index].second;
        int bx = blue[index].first;
        int by = blue[index].second;
        switch (i)
        {
        case 0: // down
            if (ry == by) {
                if (rx < bx) {
                    in_blue = tilt(bx, by, i, index, false);
                    in_red = tilt(rx, ry, i, index, true);
                }
                else {
                    in_red = tilt(rx, ry, i, index, true);
                    in_blue = tilt(bx, by, i, index, false);
                }
            }
            else {
                in_blue = tilt(bx, by, i, index, false);
                in_red = tilt(rx, ry, i, index, true);
            }
            break;
        case 1: // right
            if (rx == bx) {
                if (ry < by) {
                    in_blue = tilt(bx, by, i, index, false);
                    in_red = tilt(rx, ry, i, index, true);
                }
                else {
                    in_red = tilt(rx, ry, i, index, true);
                    in_blue = tilt(bx, by, i, index, false);
                }
            }
            else {
                in_blue = tilt(bx, by, i, index, false);
                in_red = tilt(rx, ry, i, index, true);
            }
            break;
        case 2: // up
            if (ry == by) {
                if (rx < bx) {
                    in_red = tilt(rx, ry, i, index, true);
                    in_blue = tilt(bx, by, i, index, false);
                }
                else {
                    in_blue = tilt(bx, by, i, index, false);
                    in_red = tilt(rx, ry, i, index, true);
                }
            }
            else {
                in_blue = tilt(bx, by, i, index, false);
                in_red = tilt(rx, ry, i, index, true);
            }
            break;
        case 3: // left
            if (rx == bx) {
                if (ry < by) {
                    in_red = tilt(rx, ry, i, index, true);
                    in_blue = tilt(bx, by, i, index, false);
                }
                else {
                    in_blue = tilt(bx, by, i, index, false);
                    in_red = tilt(rx, ry, i, index, true);
                }
            }
            else {
                in_blue = tilt(bx, by, i, index, false);
                in_red = tilt(rx, ry, i, index, true);
            }
            break;
        }
        if (in_blue) {
            continue;
        }
        else if (in_red) {
            if (min_cnt > index) {
                min_cnt = index;
            }
            continue;
        }
        else {
            func(index+1);
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for(int j = 0; j < m; j++) {
            if (s[j] == '#') {
                board[0][i][j] = -1;
            }
            else if (s[j] == 'R') {
                board[0][i][j] = 1;
                red[0] = {i, j};
            } 
            else if (s[j] == 'B') {
                board[0][i][j] = 2;
                blue[0] = {i, j};
            } 
            else if (s[j] == 'O') {
                board[0][i][j] = 5;
            } 
        }
    }

    func(1);
    cout << ((min_cnt == 15) ? -1 : min_cnt);
}