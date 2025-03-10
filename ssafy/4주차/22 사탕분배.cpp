// A와 B의 크기 차이로 인한 값을 비교하면
// A > B => A - B, A < B => 2A이다.
// A + B = sum 이라고 하면 A - B = 2A - sum이다.
// 이를 모듈러 연산을 하게 되면 다음과 같다.
// 2A % sum = (2A - sum) % sum = 2A % sum - sum % sum = 2A % sum
// 즉 값이 어떻게 되든 같게 된다. 그렇다면 A' = 2A % sum으로 볼 수 있다.
// 이는 연산 1번 진행한 것이고 2번 진행했을 때를 생각해보자
// 2(2A % sum) % sum = 2^2 * A % sum, 3번은 2^3 * A % sum임을 알 수 있다.

#include <iostream>
#define endl "\n"

typedef long long ll;
using namespace std;

ll a, b, k, sum;

ll recur_solve(ll num) {
    if (num == 1) return 2 % sum;

    ll tmp = recur_solve(num / 2);

    if (num % 2 == 0) {
        return (tmp * tmp) % sum;
    }
    else {
        return ((tmp * tmp) % sum * 2) % sum;
    }
}

ll non_recur_solve(ll num) {
    ll ans = 1;
    ll tmp = 2; 
    while (num > 0) {
        if (num % 2 == 1) ans = (ans * tmp) % sum;

        tmp = (tmp * tmp) % sum;
        num /= 2;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    
    for(int tc = 1; tc <= T; tc++) {
        cin >> a >> b >> k;
        sum = a + b;
        a = non_recur_solve(k) * a % sum;
        b = sum - a;
        cout << "#" << tc << " " << min(a, b) << endl;
    }
}
