#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int r, c, k, n = 3, m = 3, timer;
int board[101][101];
int cboard[101][101];
int num[101];
vector<pair<int, int>> v;

void cal() {
    fill(cboard[0], cboard[100], 0);
    if(n >= m) {
        for(int i = 1; i <= n; i++) {
            v.clear();
            fill(num, num + 101, 0);
            for(int j = 1; j <= m; j++) {
                num[board[i][j]]++;
            }
            for(int j = 1; j < 101; j++) {
                if(!num[j]) continue;
                v.push_back({num[j], j});
            }
            sort(v.begin(), v.end());
            int temp = 0;
            for(int j = 0; j < v.size(); j++) {
                if (temp >= 100) break;
                cboard[i][++temp] = v[j].second;
                cboard[i][++temp] = v[j].first;
            }
            m = max(m, temp);
        }
    }
    else {
        for(int i = 1; i <= m; i++) {
            v.clear();
            fill(num, num + 101, 0);
            for(int j = 1; j <= n; j++) {
                num[board[j][i]]++;
            }
            for(int j = 1; j < 101; j++) {
                if(!num[j]) continue;
                v.push_back({num[j], j});
            }
            sort(v.begin(), v.end());
            int temp = 0;
            for(int j = 0; j < v.size(); j++) {
                if (temp >= 100) break;
                cboard[++temp][i] = v[j].second;
                cboard[++temp][i] = v[j].first;
            }
            n = max(n, temp);
        }
    }
    for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                board[i][j] = cboard[i][j];
            }
        }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> r >> c >> k;
    for(int i = 1; i <= 3; i++) {
        for(int j = 1; j <= 3; j++) {
            cin >> board[i][j];
        }
    }

    while(board[r][c] != k) {
        if(timer > 100) {
            timer = -1;
            break;
        }
        timer++;
        cal();
    }

    cout << timer;
}

/*
pair<int, int> 를 sort하면
first 오름차순, first가 같으면 second 오름차순으로 정렬한다.

순서를 원하는 대로 하고 싶다면 compare 함수를 만든다

다음은 내림차순이다.
bool compare(pair<int, int> a, pair<int, int> b) {
    if(a.first == b.first) reutrn a.second > b.second;
    return a.first > b.first;
}

fill 1차원 배열은 (시작, 시작+개수(끝은 포함하지 않음), 0)
fill 2차원 배열은 a[n][n] 일때 (a[0], a[n-1], 0)
*/