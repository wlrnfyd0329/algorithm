#include <iostream>
#include <deque>
#include <algorithm>

using namespace std;

int n, m, year;
int board[15][15];
int bplus[15][15];
deque<int> live[15][15];
deque<int> dead[15][15];
int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

void spring_summer_winter() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < live[i][j].size(); k++) {
                if (board[i][j] - live[i][j][k] >= 0) {
                    board[i][j] -= live[i][j][k]++;
                }
                else {
                    dead[i][j].push_back(live[i][j][k]);
                }
            }

            for (int k = 0; k < dead[i][j].size(); k++) {
                board[i][j] += dead[i][j][k] / 2;
                live[i][j].pop_back();
            }
            dead[i][j].clear();

            board[i][j] += bplus[i][j];
        }
    }
}

void fall() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < live[i][j].size(); k++) {
                if (live[i][j][k] % 5 == 0) {
                    for(int d = 0; d < 8; d++) {
                        int x = i + dx[d];
                        int y = j + dy[d];
                        if (x < 0 || x >= n || y < 0 || y >= n) continue;
                        live[x][y].push_front(1);
                    }
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> year;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> bplus[i][j];
            board[i][j] = 5;
        }
    }

    for(int i = 0; i < m; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        live[x-1][y-1].push_front(z);
    }

    for (int i = 0; i < year; i++) {
        spring_summer_winter();
        fall();
    }

    int result = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result += live[i][j].size();
        }
    }

    cout << result;
}