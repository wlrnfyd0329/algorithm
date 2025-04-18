#include <iostream>
#include <queue>
#define endl "\n"

typedef long long ll;
using namespace std;

ll a, b;
struct Node {
	ll v;
	int cnt;
};

ll bfs(ll a, ll b) {
	queue<Node> q;
	q.push({a, 1});
	while(!q.empty()) {
		Node cur = q.front(); q.pop();

		if (cur.v == b) {
			return cur.cnt;
		}
		
		if (cur.v * 2 <= b) {
			q.push({cur.v * 2, cur.cnt + 1});
		}

		if (cur.v * 10 + 1 <= b) {
			q.push({cur.v * 10 + 1, cur.cnt + 1});
		}
	}

	return -1;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> a >> b;
	cout << bfs(a, b);
}