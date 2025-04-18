// 중복순열 구현 문제

#include <iostream>
#define endl "\n"

using namespace std;

int n, m;
int arr[10];

void repeated_permutation(int cnt) {
	if (cnt == m) {
		for(int i = 0; i < m; i++) {
			cout << arr[i] << " ";
		}
		cout << endl;
		return;
	}

	for(int i = 1; i <= n; i++) {
		arr[cnt] = i;
		repeated_permutation(cnt + 1);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	repeated_permutation(0);
}