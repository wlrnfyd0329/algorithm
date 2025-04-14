/* dp 풀이 
1. 테이블 정하기
2. 점화식 찾기
3. 초기값 구현하기
*/

#include <iostream>
#include <algorithm>

using namespace std;

int n, scd[20][2], dp[20], mx;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> scd[i][0] >> scd[i][1];
    }
    for (int i = 0; i <= n; i++)
    {
        dp[i] = max(mx, dp[i]);
        if (scd[i][0] + i <= n)
        {
            dp[scd[i][0] + i] = max(dp[scd[i][0] + i], dp[i] + scd[i][1]);
        }
        mx = max(mx, dp[i]);
    }
    cout << mx;
}