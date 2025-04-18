// 최소공배수가 멸망의 날인 것은 확실하다.
// 이후 다른 날을 찾아야 하는데, 먼저 x부터 시작해서 m씩 증가시키면
// x는 항상 고정된 것이다. 이때, y와 비교를 하면 된다.
// 해당하는 날을 n으로 나누면 y날의 값이 나오는데, 그 값이 y와 일치하면 정답이지만
// 0나오면 y가 최대인 것이니까 ny를 y로 바꿔준다.

#include <iostream>
#include <vector>
#include <string>
#define endl "\n"

using namespace std;

int T;

int gcd(int a, int b) {
	int r = a % b;
	if (r == 0)
		return b;
	else
		return gcd(b, r);
}

int lcm(int a, int b) {
    return a * b / gcd(a, b);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> T;
	for(int t = 0; t < T; t++) {
		int m, n, x, y;
		int result = -1;
		cin >> m >> n >> x >> y;
		int end = lcm(m, n);
		for(int i = x; i <= end; i+=m) {
			int ny = i % n;
			if (ny == 0) {
				ny = n;
			}

			if (ny == y) {
				result = i;
				break;
			}
		}
		cout << result << endl;
	}
}