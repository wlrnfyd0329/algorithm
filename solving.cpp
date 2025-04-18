#include <iostream>
#include <vector>
#define endl "\n"

using namespace std;

int n;
int arr[1005];
vector<int> lis;

int lower_bound(int target) {
	int lf = 0, rg = lis.size() - 1;
	while(lf <= rg) {
		int mid = (lf + rg) >> 1;
		if (mid < target) {
			lf = mid + 1;
		}
		else {
			rg = mid - 1;
		}
	}
	return lf;
}

int solve() {
	for(int i = 0; i < n; i++) {
		int idx = lower_bound(arr[i]);
		if (idx == lis.size()) {
			lis.push_back(arr[i]);
		}
		else {
			lis[idx] = arr[i];
		}
	}

	return lis.size();
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for(int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	cout << solve();
}