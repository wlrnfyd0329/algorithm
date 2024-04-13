#include <iostream>
#include <algorithm>

using namespace std;

int n, result = 2100000000;
int board[25][25];
int part[25][25];

void split(int x, int y, int d1, int d2) {
    fill(part[0], part[24], 0);
    for(int i = 0; i <= d1; i++) {
        part[x + i][y - i] = 5;
    }
    for(int i = 0; i <= d2; i++) {
        part[x + i][y + i] = 5;
    }
    for(int i = 0; i <= d2; i++) {
        part[x + d1 + i][y - d1 + i] = 5;
    }
    for(int i = 0; i <= d1; i++) {
        part[x + d2 + i][y + d2 - i] = 5;
    }
    for(int i = 1; i <= n; i++) {
        bool five = false;
        int cnt = 0;
        for(int j = 1; j <= n; j++) {
            if(part[i][j] == 5) cnt++;
        }
        if(cnt == 2) {
            for(int j = 1; j <= n; j++) {
                if(part[i][j] == 5) {
                    five = !five;
                }
                if(five) {
                    part[i][j] = 5;
                }
            }
        } 
    }

    for(int r = 1; r < x + d1; r++) {
        for(int c = 1; c <= y; c++) {
            if(part[r][c] == 0) part[r][c] = 1;
        }
    }

    for(int r = 1; r <= x + d2; r++) {
        for(int c = y + 1; c <= n; c++) {
            if(part[r][c] == 0) part[r][c] = 2;
        }
    }

    for(int r = x + d1; r <= n; r++) {
        for(int c = 1; c < y - d1 + d2; c++) {
            if(part[r][c] == 0) part[r][c] = 3;
        }
    }

    for(int r = x + d2 + 1; r <= n; r++) {
        for(int c = y - d1 + d2; c <= n; c++) {
            if(part[r][c] == 0) part[r][c] = 4;
        }
    }
}


int cal() {
    int cnt[6] = {0, 0, 0, 0, 0, 0};
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cnt[part[i][j]] += board[i][j];
        }
    }
    int mx = cnt[1];
    int mn = cnt[1];
    for(int i = 2; i <= 5; i++) {
        mx = max(mx, cnt[i]);
        mn = min(mn, cnt[i]);
    }
    return mx - mn;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> board[i][j];
        }
    }

    for(int d1 = 1; d1 <= n - 2; d1++) {
        for(int d2 = 1; d2 <= n - 2; d2++) {
            for(int x = 1; x <= n - d1 - d2; x++) {
                for(int y = d1 + 1; y <= n - d2; y++) {
                    split(x, y, d1, d2);
                    result = min(result, cal());
                }
            }
        }
    }
    cout << result;
}

/*
그냥 구현 열심히 하면 된다.
*/