#include <iostream>
#include <stack>

using namespace std;

struct chess {
    int x;
    int y;
    int dir;
};

int n, k;
int info[15][15];
stack<int> board[15][15];
chess horse[15];
int dx[4] = {0, 0, -1, 1};
int dy[4] = {1, -1, 0, 0};

bool isFinish(int nx, int ny) {
    if (board[nx][ny].size() >= 4) return true;
    return false;
}

bool white(int index) {
    stack<int> s;
    int nx = horse[index].x;
    int ny = horse[index].y;
    while(true) {
        s.push(board[nx][ny].top());
        board[nx][ny].pop();
        if(s.top() == index) break;
    }
    nx += dx[horse[index].dir];
    ny += dy[horse[index].dir];
    while(!s.empty()) {
        int tmp = s.top();
        s.pop();
        horse[tmp].x = nx;
        horse[tmp].y = ny;
        board[nx][ny].push(tmp);
    }
    return isFinish(nx, ny);
}

bool red(int index)
{
    int x = horse[index].x;
    int y = horse[index].y;
    int nx = x + dx[horse[index].dir];
    int ny = y + dy[horse[index].dir];
    while (true)
    {
        int tmp = board[x][y].top();
        board[x][y].pop();
        horse[tmp].x = nx;
        horse[tmp].y = ny;
        board[nx][ny].push(tmp);
        if (board[nx][ny].top() == index)
            break;
    }
    return isFinish(nx, ny);
}

bool blue(int index)
{
    switch (horse[index].dir)
    {
    case 0:
        horse[index].dir = 1;
        break;
    case 1:
        horse[index].dir = 0;
        break;
    case 2:
        horse[index].dir = 3;
        break;
    case 3:
        horse[index].dir = 2;
        break;
    }
    int nx = horse[index].x + dx[horse[index].dir];
    int ny = horse[index].y + dy[horse[index].dir];
    if (nx < 1 || nx > n || ny < 1 || ny > n || info[nx][ny] == 2) return false;
    else if (info[nx][ny] == 1)
        return red(index);
    else
        return white(index);
}

int turn() {
    int turn_cnt = 1;
    bool finish_trigger = false;
    while (turn_cnt <= 1000)
    {
        for (int i = 1; i <= k; i++)
        {
            int nx = horse[i].x + dx[horse[i].dir];
            int ny = horse[i].y + dy[horse[i].dir];
            if (nx < 1 || nx > n || ny < 1 || ny > n || info[nx][ny] == 2)
                finish_trigger = blue(i);
            else if (info[nx][ny] == 1)
                finish_trigger = red(i);
            else
                finish_trigger = white(i);
            if (finish_trigger) return turn_cnt;
        }
        turn_cnt++;
    }

    return turn_cnt;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> info[i][j];
        }
    }

    for(int i = 1; i <= k; i++) {
        int x, y, d;
        cin >> x >> y >> d;
        board[x][y].push(i);
        horse[i] = {x, y, d - 1};
    }

    int result = turn();
    cout << ((result == 1001)?-1:result);
}