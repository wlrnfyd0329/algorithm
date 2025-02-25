#include <iostream>
#include <queue>

using namespace std;

int n, m, k;
int shark[20][20];
pair<int, int> shark_position[405];
priority_queue<int> shark_id;
int shark_dir[405];
int shark_priority[405][4][4];

pair<int, int> smell[20][20]; // 상어의 숫자, 남은 냄새

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

void print() {
    cout << endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << shark[i][j] << "|" << shark_dir[shark[i][j]] << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << smell[i][j].first << "|" << smell[i][j].second << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void reduce_smell() {
    // n이 20 밖에 안되서 굳이 냄새 좌표를 저장해야 할 필요가 없을 거 같다.
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if (shark[i][j]) {
                smell[i][j] = {shark[i][j], k};
                shark_id.push(shark[i][j]);
                continue;
            }
            if (smell[i][j].second <= 1) {
                smell[i][j].first = 0;
                smell[i][j].second = 0;
            }
            else {
                smell[i][j].second--;
            }
        }
    }
}

void move_shark() {
    // 상어가 움직이기 전에 생각해야 될 부분
    // 상어의 id가 작은 친구부터 진행하면 상어가 있을 때를 비어 있다고 생각하고 진행할 수 있다.
    // 현재 방향을 보고 우선 순위 방향을 선택하고고
    // 다음 목적지에 비어 있는지, 상어가 있는지 확인 -> 냄새가 있는지를 확인한다
    // 비어 있는 부분이 여러개면 우선순위에 맞게 움직이고 비어있는 부분이 한개있다면 그 쪽으로 움직인다
    // 비어 있는 부분이 없다면 자기 냄새가 나는 곳을 확인하고 
    // 여러 개라면 우선순위에 맞게 상어를 이동시키고 하나라면 이동한다
    
    while(!shark_id.empty()) {
        int id = shark_id.top(); shark_id.pop();
        bool isSmell = true;
        int x = shark_position[id].first;
        int y = shark_position[id].second;
        for(int dir = 0; dir < 4; dir++) {
            int nx = x + dx[shark_priority[id][shark_dir[id]][dir]];
            int ny = y + dy[shark_priority[id][shark_dir[id]][dir]];
            if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
            if (smell[nx][ny].second != 0) continue;
            shark[nx][ny] = id;
            shark[x][y] = 0;
            shark_dir[id] = shark_priority[id][shark_dir[id]][dir];
            shark_position[id] = {nx, ny};
            isSmell = false;
            break;
        }

        if (isSmell) {
            for(int dir = 0; dir < 4; dir++) {
                int nx = x + dx[shark_priority[id][shark_dir[id]][dir]];
                int ny = y + dy[shark_priority[id][shark_dir[id]][dir]];
                if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
                if (smell[nx][ny].first != id) continue;
                shark[nx][ny] = id;
                shark[x][y] = 0;
                shark_dir[id] = shark_priority[id][shark_dir[id]][dir];
                shark_position[id] = {nx, ny};
                break;
            }
        }
    }

    reduce_smell();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> k;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> shark[i][j];
            if(shark[i][j]) {
                shark_position[shark[i][j]] = {i, j};
                shark_id.push(shark[i][j]);
                smell[i][j] = {shark[i][j], k};
            }
        }
    }
    for(int i = 1; i <= m; i++) {
        cin >> shark_dir[i];
        shark_dir[i]--;
    }

    for(int i = 1; i <= m; i++) {
        for(int j = 0; j < 4; j++) {
            for(int k = 0; k < 4; k++) {
                cin >> shark_priority[i][j][k];
                shark_priority[i][j][k]--;
            }
        }
    }

    for(int i = 1; i <= 1000; i++) {
        move_shark();
        if (shark_id.size() == 1) {
            cout << i;
            return 0;
        }
    }

    cout << -1;
    return 0;
}