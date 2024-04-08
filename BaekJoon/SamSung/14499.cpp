#include <iostream>

using namespace std;

int n, m, x, y, k, dir, temp;
int dice[3][3];
int map[25][25];

int dx[5] = {0, 0, 0, -1, 1};
int dy[5] = {0, 1, -1, 0, 0};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> x >> y >> k;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> map[i][j];
        }
    }
    for(int i = 0; i < k; i++) {
        cin >> dir;
        x += dx[dir];
        y += dy[dir];

        if(x < 0 || x >= n || y < 0 || y >= m) {
            x -= dx[dir];
            y -= dy[dir];
            continue;
        }

        temp = dice[0][0];
        if (dir == 1)
        {
            dice[0][0] = dice[1][0];
            dice[1][0] = dice[1][1];
            dice[1][1] = dice[1][2];
            dice[1][2] = temp;
        }
        else if (dir == 2)
        {
            dice[0][0] = dice[1][2];
            dice[1][2] = dice[1][1];
            dice[1][1] = dice[1][0];
            dice[1][0] = temp;
        }
        else if (dir == 3)
        {
            dice[0][0] = dice[2][1];
            dice[2][1] = dice[1][1];
            dice[1][1] = dice[0][1];
            dice[0][1] = temp;
        }
        else
        {
            dice[0][0] = dice[0][1];
            dice[0][1] = dice[1][1];
            dice[1][1] = dice[2][1];
            dice[2][1] = temp;
        }

        if(map[x][y] == 0) 
        {
            map[x][y] = dice[1][1];
        }
        else{
            dice[1][1] = map[x][y];
            map[x][y] = 0;
        }

        cout << dice[0][0] << "\n";
    }

}

/*
bfs 문제인 듯한
주사위의 움직임을 잘 파악하면 굉장히 쉬운 문제다.
주사위의 가장 윗부분을 dice[0][0]으로 설정했다.
*/