#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#define endl "\n"

using namespace std;

int N, M, n;
int arr[10];
int ans[10];
set<vector<int>> s;

void repeated_combination(int now, int cnt) {
	if (cnt == M) {
		vector<int> v;
		for(int i = 0; i < M; i++) {
			v.push_back(ans[i]);
		}
		s.insert(v);
		return;
	}

	for(int i = now; i < N; i++) {
		ans[cnt] = arr[i];
		repeated_combination(i, cnt + 1);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> M;
	for(int i = 0; i < N; i++) {
		cin >> arr[i];
	}
	sort(arr, arr + N);
	repeated_combination(0, 0);
	for(auto v : s) {
		for(auto k : v) {
			cout << k << " ";
		}
		cout << endl;
	}
}