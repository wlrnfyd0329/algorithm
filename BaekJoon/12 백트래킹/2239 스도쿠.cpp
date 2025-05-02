// 내가 넣은 값이 다음 값에 영향을 끼쳐서 뒤로 돌아가서 바꿔줘야 하는 경우는 보통 백트래킹 문제다.

#include <iostream>
#include <string>
#include <vector>
#define endl "\n"

using namespace std;

int board[9][9];

bool backtracking(int x, int y) {
    if (x == 9) return true;
    if (board[x][y] != 0) {
        if (++y / 9) {
            x++;
            y = 0;
        }
        return backtracking(x, y);
    }

    bool chk[10] = {0, };

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            chk[board[(x / 3) * 3 + i][(y / 3) * 3 + j]] = true;
        }
    }

    for(int i = 0; i < 9; i++) chk[board[i][y]] = true;
    for(int i = 0; i < 9; i++) chk[board[x][i]] = true;

    for(int i = 1; i <= 9; i++) {
        if (!chk[i]) {
            board[x][y] = i;
            int nx = x;
            int ny = y;
            if (++ny / 9) {
                nx++;
                ny = 0;
            }
            if (backtracking(nx, ny)) {
                return true;
            }
            board[x][y] = 0;
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for(int i = 0; i < 9; i++) {
        string s; cin >> s;
        for(int j = 0; j < 9; j++) {
            board[i][j] = s[j] - '0';
        }
    }

    backtracking(0, 0);

    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            cout << board[i][j];
        }
        cout << endl;
    }
}