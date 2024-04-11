#include <iostream>
#include <algorithm>

using namespace std;

int n, stud, like[500][4];
int board[25][25];
pair<int, int> vis[25][25];

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0 ,1};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for(int i = 0; i < n * n; i++) {
        cin >> stud;
        for(int j = 0; j < 4; j++) {
            cin >> like[stud][j];
        }
        fill(vis[0], vis[24], make_pair(0, 0));

        for(int j = 0; j < n; j++) {
            for(int l = 0; l < n; l++) {
                if(!board[j][l]) { // 인접한 좋아하는 사람 first, 인접한 빈칸 second
                    for(int k = 0; k < 4; k++) {
                        int nx = j + dx[k];
                        int ny = l + dy[k];
                        if(nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
                        if(board[nx][ny]) {
                            for(int p = 0; p < 4; p++) {
                                if(board[nx][ny] == like[stud][p]) {
                                    vis[j][l].first += 1;
                                }
                            }
                        }
                        else {
                            vis[j][l].second += 1;
                        }
                    }
                }
            }
        }
        int mx_x = -1; // 0 이면 자꾸 마지막에 00일때 가장 앞이 값이 덮어 쓰여진다.
        int mx_y = -1;
        int mx_like = 0;
        int mx_empty = 0;
        for(int j = 0; j < n; j++) {
            for(int l = 0; l < n; l++) {
                if(board[j][l]) continue; // 이미 앉은 학생 자리
                if(mx_like < vis[j][l].first) {
                    mx_x = j;
                    mx_y = l;
                    mx_like = vis[j][l].first;
                    mx_empty = vis[j][l].second;
                }
                else if(mx_like == vis[j][l].first){
                    if(mx_empty < vis[j][l].second) {
                        mx_x = j;
                        mx_y = l;
                        mx_empty = vis[j][l].second;
                    }
                    else if(mx_empty == vis[j][l].second) {
                        if(mx_x == -1 || mx_y == -1) { // 자리를 할당 받지도 못했을 때
                            mx_x = j;
                            mx_y = l;
                            continue;
                        }
                        if(mx_x < j) continue;
                        if(mx_y < l) continue;
                        mx_x = j;
                        mx_y = l;
                        mx_empty = vis[j][l].second;
                    }

                }
            }
        }

        board[mx_x][mx_y] = stud;
    }
    int result = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int like_cnt = 0;
            for(int l = 0; l < 4; l++) {
                int nx = i + dx[l];
                int ny = j + dy[l];
                if(nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
                for(int k = 0; k < 4; k++) {
                    if(board[nx][ny] == like[board[i][j]][k]) like_cnt++;
                }
            }   
            if(like_cnt == 4) result += 1000;
            else if(like_cnt == 3) result += 100;
            else if(like_cnt == 2) result += 10;
            else if(like_cnt == 1) result += 1;
        }
    }
    cout << result;
}

/*
그냥 구현 노가다 문제인듯함
*/