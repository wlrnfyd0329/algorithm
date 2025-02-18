// LCS 최장 공통 부분 수열을 모르면 못푼다.
// LCS는 Longest Common Substring(최장 공통 문자열), Longest Common Subsequence(최장 공통 부분수열) 을 의미한다
// 1. 문자열은 한번에 이어져있는 문자열을 의미하고 2. 부분수열은 따로 떨어져 있어도 가능하다.
// DP로 공통된 부분을 미리 찾을 수 있다. 구현시 차이점이 있는데, 문자열은 서로 다르다면 0을 넣고
// 부분수열은 다르다면 상, 좌에서 max인 부분을 넣는다. 이때, DP로 구한 최댓값이 최장 공통의 길이다.
// 문자열은 최댓값이 i, j라면 i-1, j-1로 0이 나올때까지 올라가면 되고 부분부열은 상, 좌에서 max인 부분을 넣기 때문에
// DP의 마지막 값이 최댓값이 되고 거기부터 같은 값이 있으면 좌, 상쪽으로 이동하고 다른 값이 나와서 이동할때,
// 해당 문자열을 넣으면서 0이 될때까지 올라가면 최장 공통 부분 수열을 구할 수 있다

#include <iostream>
#include <algorithm>

using namespace std;

int dp[1005][1005];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        string a, b;
        cin >> a >> b;
        for(int i = 1; i <= a.length(); i++) {
            for(int j = 1; j <= b.length(); j++) {
                if (a[i-1] == b[j-1]) {
                    dp[i][j] = dp[i-1][j-1] + 1;
                }
                else {
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }

        cout << "#" << tc << " " << dp[a.length()][b.length()] << "\n";
    }

    return 0;
}