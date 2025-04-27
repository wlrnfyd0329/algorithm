#include <iostream>
#include <vector>
#define endl "\n"

using namespace std;

int n;
vector<int> lis;

int lower_bound(int target) {
	int lf = 0, rg = lis.size() - 1;
	while(lf <= rg) {
		int mid = (lf + rg) >> 1;
		if (lis[mid] < target) {
			lf = mid + 1;
		}
		else {
			rg = mid - 1;
		}
	}
	return lf;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for(int i = 0; i < n; i++) {
        int num; cin >> num;
		int idx = lower_bound(num);
		if (idx == lis.size()) {
			lis.push_back(num);
		}
		else {
			lis[idx] = num;
		}
	}
	cout << lis.size();
}