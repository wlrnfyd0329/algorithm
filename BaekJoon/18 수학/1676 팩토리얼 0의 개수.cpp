// 0의 개수는 2 * 5의 개수이니까 n!을 소인수 분해해서 생각해보면
// 5의 개수가 2의 개수보다 현저히 적은 것을 알 수 있다. 따라서 5의 개수를 세면 된다.

#include <iostream>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int ans = 0;

    int N;
    cin >> N;

    for (int i=5; i<=N; i*=5) {
        ans += N / i;
    }

    cout << ans << '\n';
}