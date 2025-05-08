// dfs + 가지치기를 하면 최솟값을 찾게 될때까지 중복 연산이 많다.
// 따라서 Top-Down DP를 통해서 메모이제이션을 잘 활용해야 한다.

#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#define endl "\n"

using namespace std;

vector<int> arr;
int table[5][5][100'005]; // 0, 0, 0 에서의 힘의 최솟값

int cal(int from, int to) {
    if (from == 0) return 2;
    if (from == to) return 1;
    if (from - to == 2 || from - to == -2) return 4;
    return 3;
}

// Top-down
int func(int lf, int rg, int turn) {
    if (turn == arr.size()) return 0;
    if (table[lf][rg][turn] != -1) return table[lf][rg][turn];

    int left = func(arr[turn], rg, turn + 1) + cal(lf, arr[turn]);
    int right = func(lf, arr[turn], turn + 1) + cal(rg, arr[turn]);

    return table[lf][rg][turn] = min(left, right);
}

// int ans = 1234567891;
// void wrong_func(int lf, int rg, int val, int turn) {
//     if (turn == arr.size()) {
//         ans = min(ans, val);
//         return;
//     }
//     if (table[lf][rg][turn] != -1 && table[lf][rg][turn] <= val) {
//         return;
//     }

//     table[lf][rg][turn] = val;

//     if (arr[turn] != rg) func(arr[turn], rg, val + cal(lf, arr[turn]), turn + 1);
//     if (arr[turn] != lf) func(lf, arr[turn], val + cal(rg, arr[turn]), turn + 1);
// }

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    memset(table, -1, sizeof(table));
    while(1) {
        int num; cin >> num;
        if (num == 0) break;
        else {
            arr.push_back(num);
        }
    }

    // // bottom-up
    // // 반복문으로 채우기
    // n = arr.size();
    // // 초기화
    // for (int i = 0; i <= n; ++i)
    //     for (int l = 0; l < 5; ++l)
    //         for (int r = 0; r < 5; ++r)
    //             dp[i][l][r] = INF;
    // dp[0][0][0] = 0; // 처음에는 두 발 다 중앙(0)에 있음
    // for (int i = 0; i < n; ++i) {
    //     int next = arr[i];
    //     for (int l = 0; l < 5; ++l) {
    //         for (int r = 0; r < 5; ++r) {
    //             int cost = dp[i][l][r];
    //             if (cost == INF) continue;
    //             // 왼발을 움직이는 경우
    //             dp[i + 1][next][r] = min(dp[i + 1][next][r], cost + cal(l, next));
    //             // 오른발을 움직이는 경우
    //             dp[i + 1][l][next] = min(dp[i + 1][l][next], cost + cal(r, next));
    //         }
    //     }
    // }
    // // 결과 찾기: 마지막 단계에서 가장 작은 값 찾기
    // int answer = INF;
    // for (int l = 0; l < 5; ++l) {
    //     for (int r = 0; r < 5; ++r) {
    //         answer = min(answer, dp[n][l][r]);
    //     }
    // }

    cout << func(0, 0, 0);
}