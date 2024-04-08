#include <iostream>
#include <algorithm>

using namespace std;

int n, k, l, timer, length = 1;
int board[105][105];
int apple[105][105];
int dir[10005];
pair<int, int> rot[105];
pair<int, int> head;
pair<int, int> tail;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

int func(int dir, int var) {
    if(var > 0) {
        if(dir + var >= 4) return 0;
        else return dir + var;
    }
    else {
        if(dir + var < 0) return 3;
        else return dir + var;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    board[0][0] = 1;
    head = {0, 0};
    tail = {0, 0};
    cin >> k;
    for(int i = 0; i < k; i++) {
        int a, b;
        cin >> a >> b;
        apple[a - 1][b - 1] = 1;
    }
    cin >> l;
    rot[0] = {0, 0};
    int rot_idx = 1;
    for (int i = 1; i <= l; i++) {
        int a;
        char b;
        cin >> a >> b;
        if(b == 'D') rot[i] = {a, func(rot[i - 1].second, 1)};
        else rot[i] = {a, func(rot[i - 1].second, -1)};
    }
    while(true) {
        if(timer == rot[rot_idx].first) {
            rot_idx++;
        }
        timer++;
        dir[timer] = rot[rot_idx - 1].second;
        head = {head.first + dx[rot[rot_idx - 1].second], head.second + dy[rot[rot_idx - 1].second]};
        if(head.first < 0 || head.first >= n || head.second < 0 || head.second >= n) break;
        if (board[head.first][head.second] == 1) break;
        board[head.first][head.second] = 1;

        if(!apple[head.first][head.second]) {
            board[tail.first][tail.second] = 0;
            tail = {tail.first + dx[dir[timer - length + 1]], tail.second + dy[dir[timer - length + 1]]};
            board[tail.first][tail.second] = 1;
        }
        else {
            apple[head.first][head.second] = 0;
            length++;
        }

    }

    cout << timer;
}

/*
bfs 문제다
머리와 꼬리의 움직임에 집중해야 하며
먹은 사과를 없애야 한다.

움직임을 함수로할 필요없이 %4를 이용하면 더욱 명료해질거 같다.
rot 변수에서 차라리 방향을 나타내는 부분을 밖으로 빼면 좀더 보기 편할까 싶지만
별차이 없어 보인다.
*/