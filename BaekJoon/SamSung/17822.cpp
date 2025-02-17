#include <iostream>
#include <set>
#include <deque>

using namespace std;

int n, m, t, node_cnt = 0;

deque<int> dq[55];

void print() {
    cout << "\n";
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < dq[i].size(); j++) {
            cout << dq[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void rotate(int idx, int dir) {
    if (dir == 0) { // 시계 
        int data = dq[idx].back();
        dq[idx].pop_back();
        dq[idx].push_front(data);
    }
    else { // 반시계 
        int data = dq[idx].front();
        dq[idx].pop_front();
        dq[idx].push_back(data);
    }
}

void check() {
    bool isSame = false;
    int sum = 0, cnt = 0;
    set<pair<int, int>> s;
    for(int i = 1; i <= n; i++) { // 원판 index 
        dq[i].push_front(dq[i].back()); // 슬라이딩 윈도우 느낌을 살리기 위해서 넣기기
        dq[i].push_back(dq[i][1]);
        for(int j = 1; j <= m; j++) {
            int num = dq[i][j];
            if (num == 0) continue; // 이미 수가 사라진거 건너뛰기 
            if (num == dq[i][j-1]) { // 왼쪽과 같은지 확인
                isSame = true;
                s.insert({i, j-1});
                if (j == 1) {
                    s.insert({i, m-1});
                }
                else {
                    s.insert({i, j-2});
                }
            }
            if (num == dq[i][j+1]) { // 오른쪽과 같은지 확인
                isSame = true;
                s.insert({i, j-1});
                if (j == m) {
                    s.insert({i, 0});
                }
                else {
                    s.insert({i, j});
                }
            }
            if (i == 1 || i != n) { // 위쪽과 같은지 확인
                if (num == dq[i+1][j-1]) {
                    isSame = true;
                    s.insert({i, j - 1});
                    s.insert({i + 1, j - 1});
                }
            }
            if (i == n || i != 1) { // 아래쪽과 같은지 확인
                if (num == dq[i-1][j-1]) {
                    isSame = true;
                    s.insert({i, j - 1});
                    s.insert({i - 1, j - 1});
                }
            }
            if (!isSame) {
                sum += num;
                cnt++;
            }
        } 
        dq[i][m] = dq[i][0];
        dq[i][1] = dq[i][m + 1];
        dq[i].pop_back();
        dq[i].pop_front();
    }

    if (!isSame) { // 평균 계산 
        double avg = (double) sum / cnt;
        for(int i = 1; i <= n; i++) {
            for(int j = 0; j < m; j++) {
                if (dq[i][j] != 0) {
                    if (dq[i][j] > avg) {
                        dq[i][j]--;
                    }
                    else if (dq[i][j] < avg) {
                        dq[i][j]++;
                    }
                }
            }
        }
    }
    else {
        for(auto cur : s) {
            dq[cur.first][cur.second] = 0;
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> t;
    for(int i = 1; i <= n; i++) { // 입력
        for(int j = 0; j < m; j++) {
            int num;
            cin >> num;
            dq[i].push_back(num);
        }
    }

    for(int i = 0; i < t; i++) { // 회전
        int x, d, k;
        cin >> x >> d >> k;
        int j = 1;
        while(true) {
            int idx = x * j++;
            if (idx > n) break;
            for(int cnt = 0; cnt < k % m; cnt++) {
                rotate(idx, d);
            }
        }
        check();
    }

    int result = 0; // 합계 
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < dq[i].size(); j++) {
            result += dq[i][j];
        }
    }
    cout << result;
}