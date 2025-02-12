#include <iostream>

using namespace std;

int board[305][305];
int dx[8] = {1, 1, 1, 0, 0, -1, -1, -1};
int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        int n;
        cin >> n;
        for(int i = 0; i < n; i++) {
            string s;
            cin >> s;
            for(int j = 0; j < n; j++) {
                if (s[j] == '*') board[i][j] = -1;
                else board[i][j] = 0;
            }
        }

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if (board[i][j] == -1) continue;
                int result = 0;
                for(int k = 0; k < 8; k++) {
                    int nx = i + dx[k];
                    int ny = i + dy[k];
                    if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
                    if (board[nx][ny] == -1) result++;
                }
                board[i][j] = result;
            }
        }

        

        cout << "#" << tc << " ";
    }
}