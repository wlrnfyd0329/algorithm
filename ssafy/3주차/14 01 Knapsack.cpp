// knapsack은 유명한 dp 문제다. 해당 가방의 무게가 m 일 때, i번째 물건을 넣을 것인가 안넣을 것인가를 모두 계산해보면 된다.
// dp 점화식을 처음부터 잘 생각해보자. 현재 가방의 무게에서 최대의 가치를 생각해보면 편하다.
// 이후, 모든 가방의 무게를 조사하면서 가지고 있는 물건을 넣을지 안넣을지를 결정하면 된다.

#include <iostream>

using namespace std;

int n, k;
int dp[105][1005];
int item[105][2];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;

    for(int tc = 1; tc <= T; tc++) {
        cin >> n >> k;
        for(int i = 1; i <= n; i++) {
            int v, c;
            cin >> v >> c;
            item[i][0] = v; // 부피
            item[i][1] = c; // 가치
        }

        for(int i = 1; i <= n; i++) { // i번째 물건
            for (int j = 1; j <= k; j++) { // 무게
                if (item[i][0] <= j) {
                    dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - item[i][0]] + item[i][1]);
                }
                else { // 가방에 안들어갈 때
                    dp[i][j] = dp[i-1][j];
                }
            }
        }
        cout << "#" << tc << " " << dp[n][k] << endl;
    }

    return 0;
}