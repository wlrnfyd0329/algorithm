#include <iostream>
#include <set>

using namespace std;

int r, c, k, cnt;
int row = 3, col = 3;
int arr[101][101];
int num[101];

struct number
{
    int num;
    int cnt;

    bool operator<(const number &other) const {
        if (cnt == other.cnt) {
            return num < other.num;
        }
        return cnt < other.cnt;
    }
};

void cal_row() { // 행 연산
    int max_col = 0;
    for (int i = 1; i <= row; i++) { // 하나의 열을 골라 행 연산하고 열을 내려감
        int index = 1;
        set<number> s;
        for(int i = 0; i <= 100; i++) { // 숫자 개수 배열 초기화
            num[i] = 0;
        }

        for(int j = 1; j <= col; j++) { // 개수 세기
            num[arr[i][j]]++;
            arr[i][j] = 0;
        }

        for(int j = 1; j <= 100; j++) { // 정렬 하기
            if(num[j] != 0) {
                s.insert({j, num[j]});
            }
        }
        for(auto k : s) { // 출력하기
            arr[i][index++] = k.num;
            arr[i][index++] = k.cnt;
            if (index > 100) break;
        }

        if (max_col < index - 1) { // 제일 큰 열 개수 저장
            max_col = index - 1;
        }
    }
    col = max_col;
}

void cal_col() { // 열 연산
    int max_row = 0;
    for (int j = 1; j <= col; j++) { // 하나의 행을 골라 열 연산하고 열을 내려감
        int index = 1;
        set<number> s;
        for(int i = 0; i <= 100; i++) { // 숫자 개수 배열 초기화
            num[i] = 0;
        }

        for(int i = 1; i <= row; i++) { // 개수 세기
            num[arr[i][j]]++;
            arr[i][j] = 0;
        }

        for(int i = 1; i <= 100; i++) { // 정렬 하기
            if(num[i] != 0) {
                s.insert({i, num[i]});
            }
        }
        for(auto k : s) { // 출력하기
            arr[index++][j] = k.num;
            arr[index++][j] = k.cnt;
            if (index > 100) break;
        }

        if (max_row < index - 1) { // 제일 큰 열 개수 저장
            max_row = index - 1;
        }
    }
    row = max_row;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> r >> c >> k;
    for(int i = 1; i <= 3; i++) {
        for(int j = 1; j <= 3; j++) {
            cin >> arr[i][j];
        }
    }
    for(cnt = 0; cnt <= 100; cnt++) { // 최대 4,000,000번
        if (arr[r][c] == k) {
            break;
        }

        if (row >= col) {
            cal_row(); // 최대 40,000번
        }
        else {
            cal_col(); // 최대 40,000번
        }
    }

    if (cnt == 101) {
        cout << -1;
    }
    else {
        cout << cnt;
    }
}