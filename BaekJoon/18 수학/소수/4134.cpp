#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;
typedef long long ll;

bool isPrime(ll n)
{
	if (n < 2) return false;
	int sqrtN = sqrt(n);
	for (ll i = 2; i <= sqrtN ; i++)
		if (n % i == 0) return false;
	return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    long long t, n;
    cin >> t;
    for (int i = 0; i < t; i++) {
        cin >> n;
        while (!isPrime(n)) {
            n++;
        }
        cout << n << '\n';
    }
}

// 소수 판별시 끝까지 할 필요가 없이 루트 n까지만 해보면 알 수 있다.