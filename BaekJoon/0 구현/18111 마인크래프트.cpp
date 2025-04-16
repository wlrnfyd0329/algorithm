#include <iostream>
#include <vector>
#define endl "\n"

using namespace std;

int n, m, b;
int board[505][505];
int h[257];
int min_h = 1234567891, max_h = -1;
int ans_time = 1234567891, ans_h = -1;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> b;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int num; cin >> num;
            board[i][j] = num;
            h[num]++;
            min_h = min(min_h, num);
            max_h = max(max_h, num);
        }
    }

    for(int k = min_h; k <= max_h; k++) {
        int cnt = 0, temp_time = 0;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if (board[i][j] < k) {
                    cnt += (k - board[i][j]);
                    temp_time += (k - board[i][j]);
                }
                else if (board[i][j] > k) {
                    cnt -= (board[i][j] - k);
                    temp_time += 2 * (board[i][j] - k);
                }
            }
        }
        if (cnt <= b) {
            if (ans_time > temp_time) {
                ans_time = temp_time;
                ans_h = k;
            }
            else if (ans_time == temp_time) {
                if (ans_h < k) {
                    ans_h = k;
                }
            }
        }
    }
    cout << ans_time << " " << ans_h;
}