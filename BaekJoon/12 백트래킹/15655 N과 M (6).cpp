// 조합 구현 문제

#include <iostream>
#include <algorithm>
#define endl "\n"

using namespace std;

int n, m;
int arr[10];
int ans[10];

void combination(int now, int cnt) {
	if (cnt == m) {
		for(int i = 0; i < m; i++) {
			cout << ans[i] << " ";
		}
		cout << endl;
		return;
	}

	for(int i = now; i < n; i++) {
		ans[cnt] = arr[i];
		combination(i + 1, cnt + 1);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	for(int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	sort(arr, arr + n);
	combination(0, 0);
}