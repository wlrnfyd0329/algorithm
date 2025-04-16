#include <iostream>
#include <vector>
#include <queue>
#define endl "\n"

using namespace std;

int n;
vector<int> v;
int cnt[10];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++) {
		int num; cin >> num;
		v.push_back(num);
	}

	int type = 1, ans = 0;
	int st = 0, en = 1;
	cnt[v[st]] = 1;
	while (en < n) {
		if (type <= 2) {
			if (!cnt[v[en]]) {
				type++;
				cnt[v[en]]++;
				continue;
			}
			en++;
		}
		else {
			ans = max(ans, en - st);
			if (--cnt[v[st]] == 0) type--;
			st++;
		}
	}

	cout << max(ans, en - st);
}