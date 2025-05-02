// 시작점을 다르게 하여 최솟값을 DP하여 찾아낸 후, 끝점을 가려내도록 하면 된다.
// RGB거리 문제는 끝점을 선택하는 것이 없어서 그냥 시작점을 신경안쓰고 진행해도 된다.
// DFS로 내려가면서 전부를 탐색하는 방법도 있지만 이는 2^1000 이라 말도 안된다.

#include <iostream>
#include <algorithm>
#include <vector>
#define X first
#define Y second
#define endl "\n"

using namespace std;

int n, ans = 0x3f3f3f3f;
int cost[1005][3];
int sum[1005][3];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < 3; j++) {
            cin >> cost[i][j];
        }
    }

    for(int color = 0; color < 3; color++) {
        fill(sum[0], sum[1000], 0x3f3f3f3f);
        sum[1][color] = cost[1][color];

        for(int i = 2; i <= n; i++) {
            for(int j = 0; j < 3; j++) {
                sum[i][j] = cost[i][j] + min(sum[i - 1][(j - 1 < 0 ? 2 : j - 1)], sum[i - 1][(j + 1 >= 3 ? 0 : j + 1)]);
            }
        }

        ans = min({ans, sum[n][(color - 1 < 0 ? 2 : color - 1)], sum[n][(color + 1 >= 3 ? 0 : color + 1)]});
    }

    cout << ans;
}