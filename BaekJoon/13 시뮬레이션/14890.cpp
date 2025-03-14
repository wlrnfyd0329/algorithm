#include <iostream>

using namespace std;

int n, l, result;
int map[105][105];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> l;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> map[i][j];
        }
    }

    for(int i = 0; i < n; i++) {
        bool check = true;
        int cnt = 1;
        int now = map[i][0];
        for(int j = 1; j < n; j++) {
            if(abs(now-map[i][j]) >= 2) {
                check = false;
                break;
            }
            if(now < map[i][j]) {
                if(cnt < l) {
                    check = false;
                    break;
                }
                else {
                    now = map[i][j];
                    cnt = 1;
                }
            }
            else if(now == map[i][j]) {
                cnt++;
            }
            else {
                if(cnt < 0) {
                    check = false;
                    break;
                }
                now = map[i][j];
                cnt = 1-l;
            }
        }
        if(cnt < 0 || !check) {
            continue;
        }
        else {
            result++;
        }
    }

    for(int i = 0; i < n; i++) {
        bool check = true;
        int cnt = 1;
        int now = map[0][i];
        for(int j = 1; j < n; j++) {
            if(abs(now-map[j][i]) >= 2) {
                check = false;
                break;
            }
            if(now < map[j][i]) {
                if(cnt < l) {
                    check = false;
                    break;
                }
                else {
                    now = map[j][i];
                    cnt = 1;
                }
            }
            else if(now == map[j][i]) {
                cnt++;
            }
            else {
                if(cnt < 0) {
                    check = false;
                    break;
                }
                now = map[j][i];
                cnt = 1-l;
            }
        }
        if(cnt < 0 || !check) continue;
        else {
            result++;
        }
    }
    cout << result;
}

/*
경사로 2이상은 안된다는 걸 까먹어서 틀렸다.
*/