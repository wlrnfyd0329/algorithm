#include <iostream>
#include <vector>

using namespace std;

int n, m, h, cnt = 5;
int board[35][30];  // h, n
int ladderCnt[30];
vector<pair<int, int>> v;

bool check_ladder() {
    bool isComplete = true;
    for (int i = 0; i < n; i++) {
        int point = 2 * i + 1;
        for (int j = 1; j <= h; j++) {
            if (board[j][point + 1] != 0) {
                point += 2;
            }
            else if (board[j][point - 1] != 0) {
                point -= 2;
            }
        }
        if (point != 2 * i + 1) {
            return false;
        }
    }
    return true;
}

void select_ladder(int index) {
    if (cnt == index || index == 4) {
        return;
    }
    for (int i = 1; i < n; i++) {
        int point = 2 * i;
        for (int j = 1; j <= h; j++) {
            if (board[j][point] != 0) continue;
            if (board[j][point + 2] == 0 && board[j][point - 2] == 0) {
                board[j][point] = 1;
            }
            if (check_ladder()) {
                if (cnt > index) {
                    cnt = index;
                }
            }
            select_ladder(index + 1);
            board[j][point] = 0;
        }
    }

    return;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> h;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        board[a][2 * b] = 1;
        ladderCnt[2 * b]++;
    }

    int isOdd = 0;
    for (int i = 1; i < n; i++) {
        if (ladderCnt[2 * i] % 2 != 0) isOdd++;
    }

    if (isOdd > 3) {
        cout << -1;
    }
    else {
        if (check_ladder()) {
            cout << 0;
        }
        else {
            select_ladder(1);
            cout << ((cnt == 5)?-1:cnt);
        }
    }

    
}