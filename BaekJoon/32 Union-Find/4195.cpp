#include <iostream>
#include <string>
#include <string.h>
#include <unordered_map>
#define endl "\n"

using namespace std;

int T, N, cnt;
int p[200'005];
unordered_map<string, int> table;

int find(int x) {
	if (p[x] < 0) return x;
	return p[x] = find(p[x]);
}

bool uni(int u, int v) {
	u = find(u);
	v = find(v);
	if (u == v) return false;
	if (p[u] < p[v]) swap(u, v);
	p[v] += p[u];
	p[u] = v;
	return true;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> N;
		cnt = 1;
		memset(p, -1, sizeof(p));
        table.clear();
		for (int i = 0; i < N; i++) {
			string s1, s2;
			cin >> s1 >> s2;
			if (table[s1] == 0) table[s1] = cnt++;
			if (table[s2] == 0) table[s2] = cnt++;
			uni(table[s1], table[s2]);
			cout << -p[find(table[s1])] << endl;
		}
	}
}