// lazy하게 색깔을 처리해주는 것이 중요한 포인트였다.
// update 시간을 지정해줌으로써 각자의 색깔이 언제 업데이트 되었는지 확인하는 것이 중요했다.
// for문을 돌릴 때, 영향을 끼치는 값과 아닌 값을 구분해야 한다.

#include <iostream>
#include <vector>
#define endl "\n"

using namespace std;

struct Node {
	int m_id;
	int p_id;
	int color;
	int max_depth;
	int last_update;
	vector<int> child;
} node[100'005];

int update_time = 0;
int sum = 0;

vector<int> roots;

void add_node() {
	int m_id, p_id, color, max_depth;
	cin >> m_id >> p_id >> color >> max_depth;
	int p = p_id;
	int depth = 1;
	while (p > 0) {
		if (node[p].max_depth <= depth++) return;
		p = node[p].p_id;
	}
	if (p_id == -1) roots.push_back(m_id);
	else node[p_id].child.push_back(m_id);
	node[m_id] = { m_id, p_id, color, max_depth, update_time++ };
}

void change_color() {
	int m_id, color; cin >> m_id >> color;
	node[m_id].color = color;
	node[m_id].last_update = update_time++;
}

void query_color() {
	int m_id; cin >> m_id;
	int p = node[m_id].p_id;
	int color = node[m_id].color;
	int last_update = node[m_id].last_update;
	while (p > 0) {
		if (last_update < node[p].last_update) {
			last_update = node[p].last_update;
			color = node[p].color;
		}
		p = node[p].p_id;
	}
	cout << color << endl;
}

int dfs(int id, int color, int ut) {
	if (node[id].last_update > ut) {
		ut = node[id].last_update;
		color = (1 << node[id].color);
	}
	int now_color = color;
	for (auto k : node[id].child) {
		color |= dfs(k, now_color, ut);
	}

	int cnt = 0;
	for (int i = 1; i <= 5; i++) {
		if ((color & (1 << i)) > 0) cnt++;
	}

	sum += cnt * cnt;
	return color;
}

void query_score() {
	sum = 0;
	for (int root : roots) {
		dfs(root, (1 << node[root].color), node[root].last_update);
	}
	cout << sum << endl;
}


int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int q; cin >> q; // 10만번, n = 100,000
	while (q--) {
		int cmd; cin >> cmd;
		if (cmd == 100) add_node();
		else if (cmd == 200) change_color();
		else if (cmd == 300) query_color();
		else if (cmd == 400) query_score();
	}
}