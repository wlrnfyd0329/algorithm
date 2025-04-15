// DP문제인데, 3 ~ 5까지 잘 생각해보면 된다.
// 1은 | 이거 하나인데, 2는 ||, =, - 이렇게 3개다
// 그렇다면 3은? | 이거에 =, - 을 붙인 것과 ||, =, - 에 |를 붙인 것이다.
// 이는 i = (i - 1) + (i - 2) * 2 인 것을 알 수 있다.

#include <iostream>
#include <vector>
#define endl "\n"

using namespace std;

int n;
vector<int> v;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    v = vector<int> (n + 1);
    v[1] = 1;
    v[2] = 3;
    for(int i = 3; i <= n; i++) {
        v[i] += v[i - 1] + v[i - 2] * 2;
        v[i] %= 10007;
    }
    
    cout << v[n];
}