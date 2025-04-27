#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#define endl "\n"

using namespace std;

int n, k;
char board[10000][10000];

inline int cal(int num) {
    return 3 * pow(2, num);
}

void print() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2 * n - 1; j++) {
            if (board[i][j]) cout << board[i][j];
            else cout << " ";
        }
        cout << endl;
    }
}

void print_star(int x, int y) {
    board[x - 2][y] = '*';
    board[x - 1][y - 1] = board[x - 1][y + 1] = '*';
    for (int i = -2; i <= 2; i++) board[x][y + i] = '*';
}

void star(int x, int y, int cnt) {
    if (cnt == 0) {
        print_star(x, y);
        return;
    }

    star(x - cal(cnt - 1), y, cnt - 1);
    star(x, y - cal(cnt - 1), cnt - 1);
    star(x, y + cal(cnt - 1), cnt - 1);
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    k = log2(n / 3);
    star(n - 1, n - 1, k);
    print();
}