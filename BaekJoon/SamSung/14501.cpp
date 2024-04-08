/*
dfs 식 풀이
재귀를 이용하여 풀었다.
정해진 일수를 초과하는 날은 0을 return하며 최대값에 저장되지 못하도록 하였다.
*/

#include <iostream>

using namespace std;

int n, scd[20][2];

int func(int day, int result) {
    int mx = result;
    if (day > n) {
        return 0;
    }

    for (int i = day; i < n; i++)
    {
        int temp = func(scd[i][0], result + scd[i][1]);
        if (mx < temp)
            mx = temp;
    }
    return mx;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> scd[i][0] >> scd[i][1];
        scd[i][0] += i;
    }
    cout << func(0, 0);
}

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