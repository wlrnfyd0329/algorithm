// 취소된 물건을 lazy하게 잘 처리해야 한다
// 비어 있는 큐를 항상 고려 해야 한다
// 우선순위 큐를 사용할 때는 그리디 하게 진행되는 것을 잊으면 안된다

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#define X first
#define Y second
#define endl "\n"

using namespace std;

const int INF = 0x3f3f3f3f;
int N, M;
vector<vector<pair<int, int>>> graph;
vector<int> dist;
struct Product {
	int revenue;
	int dest;
	bool isCancel = false;
};
unordered_map<int, Product> table;

struct cmp {
	bool operator() (const pair<int, int>& a, const pair<int, int>& b) const {
		if (a.X == b.X) return a.Y > b.Y;
		return a.X < b.X;
	}
};
priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> product;

void change(int start) {
	dist = vector<int>(N, INF);
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

	dist[start] = 0;
	pq.push({ dist[start], start });

	while (!pq.empty()) {
		auto cur = pq.top(); pq.pop();

		if (dist[cur.Y] != cur.X) continue;
		for (auto nxt : graph[cur.Y]) {
			if (dist[nxt.Y] <= nxt.X + dist[cur.Y]) continue;
			dist[nxt.Y] = nxt.X + dist[cur.Y];
			pq.push({ dist[nxt.Y], nxt.Y });
		}
	}

	queue<pair<int, int>> q;
	while (!product.empty()) {
		auto cur = product.top(); product.pop();
		if (table[cur.Y].isCancel) continue;
		q.push({ table[cur.Y].revenue - dist[table[cur.Y].dest], cur.Y });
	}

	while (!q.empty()) {
		product.push(q.front()); q.pop();
	}
}

void init() {
	cin >> N >> M;
	graph = vector<vector<pair<int, int>>>(N);
	for (int i = 0; i < M; i++) {
		int v, u, w;
		cin >> v >> u >> w;
		graph[v].push_back({ w, u });
		graph[u].push_back({ w, v });
	}
	change(0);
}

void insert() {
	int id, revenue, dest;
	cin >> id >> revenue >> dest;
	table[id] = { revenue, dest, false };
	product.push({ revenue - dist[dest], id });
}

void cancel() {
	int id; cin >> id;
	table[id].isCancel = true;
}

void sell() {
	while (!product.empty()) {
		if (table[product.top().Y].isCancel) {
			product.pop();
		}
		else break;
	}
	if (product.empty()) {
		cout << -1 << endl;
		return;
	}
	auto cur = product.top();
	if (cur.X < 0) cout << -1 << endl;
	else {
		product.pop();
		cout << cur.Y << endl;
		table[cur.Y].isCancel = true;
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int Q; cin >> Q;
	for (int tc = 1; tc <= Q; tc++) {
		int cmd; cin >> cmd;
		switch (cmd)
		{
		case 100:
			init();
			break;
		case 200:
			insert();
			break;
		case 300:
			cancel();
			break;
		case 400:
			sell();
			break;
		case 500:
			int s; cin >> s;
			change(s);
			break;
		}
	}
}