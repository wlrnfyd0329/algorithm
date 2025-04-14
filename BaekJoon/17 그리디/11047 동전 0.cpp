// 동전 A의 가치가 항상 배수로 올라가기 때문에 그리디 알고리즘으로 해결할 수 있다.
// 왜냐면 큰 가치를 가진 동전은 항상 작은 동전의 가치의 배수이기에 무조건 적으로 이득이기 때문이다.

#include <iostream>
#include <vector>
#define endl "\n"

using namespace std;

int N, K, ans;
vector<int> coin;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> K;
    ans = 0;
    for(int i = 0; i < N; i++) {
        int num; cin >> num;
        coin.push_back(num);
    }

    for(int i = coin.size() - 1; i >= 0; i--) {
        if (K == 0) break;
        if (coin[i] > K) continue;
        ans += K / coin[i];
        K %= coin[i];
    }
    cout << ans;
}