#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int n, res = 0;
vector<int> v[405];
int arr[25][25];

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    for(int i = 0; i < n * n; i++) {
        int student;
        cin >> student;
        v[0].push_back(student);
        for(int j = 0; j < 4; j++) {
            int x;
            cin >> x;
            v[student].push_back(x);
        }
    }

    for(auto student : v[0]) {
        int like_person = -1;
        int empty_person = -1;
        pair<int, int> position;
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if (arr[i][j] != 0) continue;
                int empty_cnt = 0;
                int like_cnt = 0;
                for(int dir = 0; dir < 4; dir++) {
                    int nx = i + dx[dir];
                    int ny = j + dy[dir];
                    if (nx < 1 || nx > n || ny < 1 || ny > n) continue;
                    if (arr[nx][ny] == 0) empty_cnt++;
                    else {
                        if (find(v[student].begin(), v[student].end(), arr[nx][ny]) != v[student].end()) {
                            like_cnt++;
                        }
                    }
                }
                if (like_person < like_cnt) {
                    like_person = like_cnt;
                    empty_person = empty_cnt;
                    position = {i, j};
                }
                else if (like_person == like_cnt){
                    if(empty_person < empty_cnt) {
                        empty_person = empty_cnt;
                        position = {i, j};
                    }
                }
            }
        }
        arr[position.first][position.second] = student;
    }
    
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            int cnt = 0;
            for(int dir = 0; dir < 4; dir++) {
                int nx = i + dx[dir];
                int ny = j + dy[dir];
                if (nx < 1 || nx > n || ny < 1 || ny > n) continue;
                if (find(v[arr[i][j]].begin(), v[arr[i][j]].end(), arr[nx][ny]) != v[arr[i][j]].end()) {
                    cnt++;
                }
            }
            if (cnt != 0) {
                res += pow(10, cnt - 1);
            }
        }
    }

    cout << res;
}