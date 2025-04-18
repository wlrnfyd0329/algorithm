// 중복조합 구현 문제

#include <iostream>
#define endl "\n"

using namespace std;

int n, m;
int arr[10];

void solve(int now, int cnt) {
	if (cnt == m) {
		for(int i = 0; i < m; i++) {
			cout << arr[i] << " ";
		}
		cout << endl;
		return;
	}

	for(int i = now; i <= n; i++) {
		arr[cnt] = i;
		solve(i, cnt + 1);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	solve(1, 0);
}