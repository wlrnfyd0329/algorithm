#include <iostream>
#include <algorithm>

using namespace std;

int n, max_value = 0;
pair<int, int> board[10][25][25];
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

void reset(int index) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            board[index][i][j] = {board[index - 1][i][j].first, 0};

        }
    }
}

void check() {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if (max_value < board[5][i][j].first) {
                max_value = board[5][i][j].first;
            }
        }
    }
}

void print(int index) {
    cout << index << "\n";
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << board[index][i][j].first << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void slide(int x, int y, int index, int dir) {
    int nx = x;
    int ny = y;
    while(true) {
        nx += dx[dir];
        ny += dy[dir];
        if (nx < 0 || nx >= n || ny < 0 || ny >= n) break;
        if (board[index][nx][ny] == make_pair(0, 0)) {
            board[index][nx][ny] = board[index][nx - dx[dir]][ny - dy[dir]];
            board[index][nx - dx[dir]][ny - dy[dir]] = {0, 0};
            continue;
        }
        if (board[index][nx][ny] == board[index][nx - dx[dir]][ny - dy[dir]]) {
            board[index][nx][ny].first += board[index][nx - dx[dir]][ny - dy[dir]].first;
            board[index][nx][ny].second = 1;
            board[index][nx - dx[dir]][ny - dy[dir]] = {0, 0};
        }
        break;
    }
}


void func(int index) {
    if (index == 6) {
        check();
        return;
    }
    for (int dir = 0; dir < 4; dir++) {
        reset(index);
        switch (dir)
        {
        case 0: // down
            for(int j = 0; j < n; j++) {
                for(int i = n - 1; i >= 0; i--) {
                    slide(i, j, index, dir);
                }
            }
            break;
        case 1: // right
            for(int i = 0; i < n; i++) {
                for(int j = n - 1; j >= 0; j--) {
                    slide(i, j, index, dir);
                }
            }
            break;
        case 2: // up
            for(int j = 0; j < n; j++) {
                for(int i = 0; i < n; i++) {
                    slide(i, j, index, dir);
                }  
            }

            break;
        case 3: // left
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < n; j++) {
                    slide(i, j, index, dir);
                }
            }
            break;
        }
        func(index + 1);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int tmp;
            cin >> tmp;
            board[0][i][j] = {tmp, 0};
        }
    }

    func(1);
    cout << max_value;
}