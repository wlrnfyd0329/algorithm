#include <iostream>
#include <algorithm>

using namespace std;

int a[305], s[305][3], n;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for(int i = 1; i<=n; i++) {
        cin >> a[i];
    }
    if (n == 1) {
        cout << a[1];
        return 0;
    }
    s[1][1] = a[1];
    s[1][2] = 0;
    s[2][1] = a[2];
    s[2][2] = a[1] + a[2];
    for(int i = 3; i <= n; i++) {
        s[i][1] = max(s[i-2][1], s[i-2][2]) + a[i];
        s[i][2] = s[i-1][1] + a[i];
    }
    cout << max(s[n][1], s[n][2]);
}

/*
포인트는 2차원 배열을 사용하는 것이다.
점화식을 
D[k][1] = max(D[k-2][1], D[k-2][2]) + S[k]
D[k][2] = D[k-1][1] + S[k] 으로 세울 수 있다.
추가로 테이블을 밟지 않았을때의 최솟값을 구하는 방법도 존재한다..
D[k] = min(D[k-2], D[k-3]) + S[k]
*/