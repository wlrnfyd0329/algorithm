// 그리디하게 제일 빨리 끝나는 시간을 순으로 정렬해서 찾으면 된다.

#include <iostream>
#include <vector>
#include <algorithm>
#define X first
#define Y second
#define endl "\n"

using namespace std;

int N, ans = 0;
vector<pair<int, int>> v;

bool cmp(const pair<int, int> &a, const pair<int, int> &b) {
	if (a.Y == b.Y) return a.X < b.X;
	return a.Y < b.Y;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> N;
	for(int i = 0; i < N; i++) {
		int a, b; cin >> a >> b;
		v.push_back({a, b});
	}
	sort(v.begin(), v.end(), cmp);
	int end = 0;
	for(int i = 0; i < N; i++) {
		if (end <= v[i].X) {
			ans++;
			end = v[i].Y;
		}
	}

	cout << ans;
}