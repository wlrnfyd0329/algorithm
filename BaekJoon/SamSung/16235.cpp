#include <iostream>
#include <deque>

using namespace std;

int n, m, k, result;
int map[11][11];
int food[11][11];
deque<int> tree[11][11];
deque<int> dietree[11][11];

int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

void spring() {
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            int temp = 0;
            for(int l = 0; l < tree[i][j].size(); l++) {
                if(tree[i][j][l] <= map[i][j]) {
                    map[i][j] -= tree[i][j][l];
                    tree[i][j][l]++;
                }
                else temp++;
            }
            for(int l = 0; l < temp; l++) {
                dietree[i][j].push_back(tree[i][j].back());
                tree[i][j].pop_back();
            }
        }
    }
}

void summer() {
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            for(int l = 0; l < dietree[i][j].size(); l++) {
                map[i][j] += dietree[i][j][l] / 2;
            }
            dietree[i][j].clear();
        }
    }
}

void fall() {
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            for(int l = 0; l < tree[i][j].size(); l++) {
                if(tree[i][j][l] % 5 == 0) {
                    for(int k = 0; k < 8; k++) {
                        int nx = i + dx[k];
                        int ny = j + dy[k];
                        if(nx < 0 || nx > n || ny < 0 || ny > n) continue;
                        tree[nx][ny].push_front(1);
                    }
                }
            }
        }
    }
}

void winter() {
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            map[i][j] += food[i][j];
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> k;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> food[i][j];
            map[i][j] = 5;
        }
    }
    for(int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        tree[a][b].push_back(c);
    }

    while(k--) {
        spring();
        summer();
        fall();
        winter();
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            result += tree[i][j].size();
        }
    }

    cout << result;
}

/*
그냥 구현 문제인데 시간이 매우 짧다.
매번 sort하면 시간 초과가 발생할 것 같다.
*/