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