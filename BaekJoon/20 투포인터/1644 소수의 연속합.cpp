// 연속합 문제를 읽어보면 투포인터를 사용할 것임을 알 수 있다.
// 이때, index 범위 조절을 조심해야 한다.

#include <iostream>
#include <algorithm>
#include <vector>
#define endl "\n"

using namespace std;

int N, ans, sum;
vector<bool> isPrime;
vector<int> prime;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    ans = sum = 0;
    isPrime = vector<bool> (N + 1, 1);
    for(int i = 2; i <= N; i++) {
        if (isPrime[i]) prime.push_back(i);
        for(int j = i * 2; j <= N; j += i) {
            isPrime[j] = false;
        }
    }

    int lf = 0, rg = 0;
    while(rg < prime.size()) { // <= 로 해서 틀렸다. 사실 rg는 size()와 같아지면 안되는데, 왜 그랬는지 모름;;
        sum += prime[rg++];
        while(sum >= N) {
            if (sum == N) ans++;
            sum -= prime[lf++];
        }
    }

    cout << ans;
}