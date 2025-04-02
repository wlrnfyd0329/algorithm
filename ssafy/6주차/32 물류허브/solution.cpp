// 자신에게 돌아오는 건 역방향 그래프로 다익스트라 하면 된다.

#include <vector>
#include <queue>
#include <unordered_map>
#define X first
#define Y second

using namespace std;

const int INF = 0x3f3f3f3f;
vector<vector<pair<int, int>>> fgraph, bgraph;
vector<int> fdist, bdist;
int city_cnt;
unordered_map<int, int> table;

vector<int> djikstra(vector<vector<pair<int, int>>> &graph, int st) {
	vector<int> dist(city_cnt, INF);
	priority_queue<pair<int, int>, vector< pair<int, int>>, greater< pair<int, int>>> pq;
	dist[st] = 0;
	pq.push({ dist[st], st });

	while (!pq.empty()) {
		auto cur = pq.top(); pq.pop();

		if (dist[cur.Y] != cur.X) continue;
		for (auto nxt : graph[cur.Y]) {
			if (dist[nxt.Y] <= nxt.X + dist[cur.Y]) continue;
			dist[nxt.Y] = nxt.X + dist[cur.Y];
			pq.push({ dist[nxt.Y], nxt.Y });
		}
	}

	return dist;
}

int init(int N, int sCity[], int eCity[], int mCost[]) {
	city_cnt = 1;
	table.clear();
	fgraph = vector<vector<pair<int, int>>>(605);
	bgraph = vector<vector<pair<int, int>>>(605);
	for (int i = 0; i < N; i++) {
		if (table[sCity[i]] == 0) table[sCity[i]] = city_cnt++;
		if (table[eCity[i]] == 0) table[eCity[i]] = city_cnt++;
		fgraph[table[sCity[i]]].push_back({ mCost[i], table[eCity[i]]});
		bgraph[table[eCity[i]]].push_back({ mCost[i], table[sCity[i]] });
	}

	return city_cnt - 1;
}

void add(int sCity, int eCity, int mCost) {
	fgraph[table[sCity]].push_back({ mCost, table[eCity] });
	bgraph[table[eCity]].push_back({ mCost, table[sCity] });
}

int cost(int mHub) {
	int ans = 0, hub = table[mHub];
	vector<int> fdist = djikstra(fgraph, hub);
	vector<int> bdist = djikstra(bgraph, hub);
	for (int i = 1; i < city_cnt; i++) {
		ans += fdist[i];
		ans += bdist[i];
	}
	return ans;
}