#include <iostream>
#include <vector>
#define endl "\n"

using namespace std;

int n, r, q;
vector<vector<int>> arr;
vector<int> sub;
vector<bool> vis;

void dfs(int cur) {

	sub[cur] = 1;

	for (auto nxt : arr[cur]) {
		if (vis[nxt]) continue;
		vis[nxt] = true;
		dfs(nxt);
		sub[cur] += sub[nxt];
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> r >> q;
	arr = vector<vector<int>>(n + 1);
	sub = vector<int>(n + 1, 0);
	vis = vector<bool>(n + 1, 0);
	for (int i = 1; i < n; i++) {
		int a, b;
		cin >> a >> b;
		arr[a].push_back(b);
		arr[b].push_back(a);
	}

	vis[r] = true;
	dfs(r);

	for (int i = 0; i < q; i++) {
		int num; cin >> num;
		cout << sub[num] << endl;
	}
}
