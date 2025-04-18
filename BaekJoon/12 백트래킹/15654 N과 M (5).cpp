// 순열 구현 문제

#include <iostream>
#include <algorithm>
#define endl "\n"

using namespace std;

int n, m;
int arr[10];
int ans[10];

void permutation(int cnt, int status) {
	if (cnt == m) {
		for(int i = 0; i < m; i++) {
			cout << ans[i] << " ";
		}
		cout << endl;
		return;
	}

	for(int i = 0; i < n; i++) {
		if ((status & (1 << i)) > 0) continue;
		ans[cnt] = arr[i];
		permutation(cnt + 1, status | (1 << i));
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
	permutation(0, 0);
}