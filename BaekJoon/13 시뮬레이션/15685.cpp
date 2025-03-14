#include <iostream>
#include <vector>

using namespace std;

struct info {
    int x;
    int y;
    int d;
};
int n, x, y, d, g;
int board[101][101];
vector<info> curve;

int dx[4] = {0, -1, 0, 1};
int dy[4] = {1, 0, -1, 0};

int check() {
    int result = 0;
    for(int i = 0; i < 100; i++) {
        for(int j = 0; j < 100; j++) {
            if(board[i][j] && board[i][j+1] && board[i+1][j] && board[i+1][j+1]) result++;
        }
    }
    return result;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    while(n--) {
        curve.clear();
        cin >> y >> x >> d >> g;
        board[x][y] = 2;
        int nx = x + dx[d];
        int ny = y + dy[d];
        if(nx >= 0 && nx < 101 & ny >= 0 && ny < 101) board[nx][ny] = 1;
        curve.push_back({nx, ny, (d + 1) % 4});
        for(int i = 0; i < g; i++) {
            int temp = curve.size();
            for(int j = temp - 1; j >= 0; j--) {
                nx += dx[curve[j].d];
                ny += dy[curve[j].d];
                if(nx >= 0 && nx < 101 & ny >= 0 && ny < 101) board[nx][ny] = 1;
                curve.push_back({nx, ny, (curve[j].d + 1) % 4});
            }
        }
    }

    cout << check();
}

/*
좌표가 100을 넘어도 커브는 계속 되야 된다.
직전 좌표에 방향을 저장하고 다음 방향은 그 방향에 + 1을 한다.
물론 직전 좌표로 돌아가는건 거꾸로 해야된다.
*/