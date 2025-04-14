#include <iostream>
#include <queue>

using namespace std;

struct shark {
    int s;
    int d;
    int z;
} arr[105][105];

int r, c, m, result;
queue<pair<int, int>> shark_coordi;
int dx[5] = {0, -1, 1, 0, 0};
int dy[5] = {0, 0, 0, 1, -1};

void init() {
    for(int i = 1; i <= r; i++) {
        for(int j = 1; j <= c; j++) {
            arr[i][j] = {0, 0, 0};
        }
    }
    result = 0;
}

void catchShark(int index) {
    for(int i = 1; i <= r; i++) {
        if(arr[i][index].z > 0) {
            result += arr[i][index].z;
            arr[i][index] = {0, 0, 0};
            break;
        }
    }
}

void moveShark() {
    shark new_shark_arr[105][105];
    for(int i = 1; i <= r; i++) {
        for(int j = 1; j <= c; j++) {
            new_shark_arr[i][j] = {0, 0, 0};
        }
    }
    vector<pair<int, int>> new_shark_coordi;
    while(!shark_coordi.empty()) {
        auto cur = shark_coordi.front(); shark_coordi.pop();
        if (arr[cur.first][cur.second].z == 0) continue;
        int nx = cur.first;
        int ny = cur.second;
        int move = arr[cur.first][cur.second].s; 
        switch (arr[cur.first][cur.second].d)
        {
        case 1: // 위
            if (move < nx)
            {
                nx -= move;
            }
            else
            {
                move -= nx - 1;
                if (move % (r - 1) == 0) {
                    if (move / (r - 1) % 2 != 0) { // 0으로 나눠떨어지는데 홀수 => 1, 2, 3 => i + 1
                        nx = r;
                        arr[cur.first][cur.second].d = 2;
                    }
                    else { // 짝수 => 3, 2, 1 => r - i
                        nx = 1;
                    }
                }
                else {
                    if (move / (r - 1) % 2 == 0) { // 0으로 안나눠떨어지는데 짝수 => 1, 2, 3 => i + 1
                        nx = move % (r - 1) + 1;
                        arr[cur.first][cur.second].d = 2;
                    }
                    else { // 홀수 => 3, 2, 1 => r - i
                        nx = r - move % (r - 1);
                    }
                }
            }
            break;
        case 2: // 아래
            if (move < r - nx + 1)
            {
                nx += move;
            }
            else
            {
                move -= r - nx;
                if (move % (r - 1) == 0) {
                    if (move / (r - 1) % 2 != 0) { // 0으로 나눠떨어지는데 홀수 => 3, 2, 1 => r - i
                        nx = 1;
                        arr[cur.first][cur.second].d = 1;
                    }
                    else { // 짝수 => 1, 2, 3 => i + 1
                        nx = r;
                    }
                }
                else {
                    if (move / (r - 1) % 2 == 0) { // 0으로 안나눠떨어지는데 짝수 => 3, 2, 1 => r - i
                        nx = r - move % (r - 1);
                        arr[cur.first][cur.second].d = 1;
                    }
                    else { // 홀수 => 1, 2, 3 => i + 1
                        nx = move % (r - 1) + 1;
                    }
                }
            }
            break;
        case 3: // 오른쪽
            if (move < c - ny + 1)
            {
                ny += move;
            }
            else
            {
                move -= c - ny;
                if (move % (c - 1) == 0)
                {
                    if (move / (c - 1) % 2 != 0)
                    { // 0으로 나눠떨어지는데 홀수 => 3, 2, 1 => r - i
                        ny = 1;
                        arr[cur.first][cur.second].d = 4;
                    }
                    else
                    { // 짝수 => 1, 2, 3 => i + 1
                        ny = c;
                    }
                }
                else
                {
                    if (move / (c - 1) % 2 == 0)
                    { // 0으로 안나눠떨어지는데 짝수 => 3, 2, 1 => r - i
                        ny = c - move % (c - 1);
                        arr[cur.first][cur.second].d = 4;
                    }
                    else
                    { // 홀수 => 1, 2, 3 => i + 1
                        ny = move % (c - 1) + 1;
                    }
                }
            }
            break;
        case 4: // 왼쪽
            if (move < ny)
            {
                ny -= move;
            }
            else
            {
                move -= ny - 1;
                if (move % (c - 1) == 0)
                {
                    if (move / (c - 1) % 2 != 0)
                    { // 0으로 나눠떨어지는데 홀수 => 1, 2, 3 => i + 1
                        ny = c;
                        arr[cur.first][cur.second].d = 3;
                    }
                    else
                    { // 짝수 => 3, 2, 1 => r - i
                        ny = 1;
                    }
                }
                else
                {
                    if (move / (c - 1) % 2 == 0)
                    { // 0으로 안나눠떨어지는데 짝수 => 1, 2, 3 => i + 1
                        ny = move % (c - 1) + 1;
                        arr[cur.first][cur.second].d = 3;
                    }
                    else
                    { // 홀수 => 3, 2, 1 => r - i
                        ny = c - move % (c - 1);
                    }
                }
            }
            break;
        }
        if (new_shark_arr[nx][ny].z > 0) {
            if(new_shark_arr[nx][ny].z < arr[cur.first][cur.second].z) {
                new_shark_arr[nx][ny] = arr[cur.first][cur.second];
            }
        }
        else {
            new_shark_arr[nx][ny] = arr[cur.first][cur.second];
            new_shark_coordi.push_back({nx, ny});
        }
        arr[cur.first][cur.second] = {0, 0, 0};
    }

    for(auto k : new_shark_coordi) {
        arr[k.first][k.second] = new_shark_arr[k.first][k.second];
        shark_coordi.push({k.first, k.second});
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> r >> c >> m;
    init();
    for (int i = 0; i < m; i++) {
        int x, y, s, d, z;
        cin >> x >> y >> s >> d >> z;
        arr[x][y] = {s, d, z};
        shark_coordi.push({x, y});
    }
    for (int man = 1; man <= c; man++) {
        catchShark(man);
        moveShark();
    }

    cout << result;
}