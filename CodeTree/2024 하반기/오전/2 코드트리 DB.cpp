// dynamic segment tree 문제다.
// 중요한 cnt를 사용해서 이분탐색 느낌으로 k번째 원소를 찾는 것이 포인트였다.

#include <iostream>
#include <string>
#include <unordered_map>
#define endl "\n"

typedef long long ll;
using namespace std;

unordered_map<string, int> name2value;
unordered_map<int, string> value2name;

struct Node {
	Node *left, *right;
	ll value, cnt;
	Node() {
		left = right = nullptr;
		value = cnt = 0;
	}
} *root;

void update(Node *node, ll start, ll end, ll idx, ll value) {
	if (start == end) {
		node->value = value;
		if (value == 0) node->cnt = 0;
		else node->cnt = 1;
		return;
	}
	ll mid = (start + end) >> 1;
	if (idx <= mid) {
		if (!node->left) node->left = new Node();
		update(node->left, start, mid, idx, value);
	}
	else {
		if (!node->right) node->right = new Node();
		update(node->right, mid + 1, end, idx, value);
	}
	ll tmpv1 = (node->left) ? node->left->value : 0;
	ll tmpv2 = (node->right) ? node->right->value : 0;
	node->value = tmpv1 + tmpv2;
	ll tmpc1 = (node->left) ? node->left->cnt : 0;
	ll tmpc2 = (node->right) ? node->right->cnt : 0;
	node->cnt = tmpc1 + tmpc2;
}

ll find(Node *node, ll start, ll end, ll cnt) {
	if (!node) return 0;
	if (start == end) {
		return node->value;
	}
	ll mid = (start + end) >> 1;
	ll tmpc1 = (node->left) ? node->left->cnt : 0;
	ll tmpc2 = (node->right) ? node->right->cnt : 0;
	if (cnt <= tmpc1) {
		return find(node->left, start, mid, cnt);
	}
	else {
		return find(node->right, mid + 1, end, cnt - tmpc1);
	}
}

ll sum(Node *node, ll start, ll end, ll left, ll right) {
	if (!node || right < start || end < left) return 0;
	if (left <= start && end <= right) return node->value;
	ll mid = (start + end) >> 1;
	return sum(node->left, start, mid, left, right) + sum(node->right, mid + 1, end, left, right);
}

void init() {
	name2value.clear();
	value2name.clear();
	root = new Node();
}



int insert() {
	string name;
	int value;
	cin >> name >> value;
	if (name2value.find(name) != name2value.end()) return 0;
	if (value2name.find(value) != value2name.end()) return 0;
	name2value[name] = value;
	value2name[value] = name;
	update(root, 1, 1'000'000'000, value, value);
	return 1;
}

int remove() {
	string name;
	cin >> name;
	if (name2value.find(name) == name2value.end()) return 0;
	int value = name2value[name];
	name2value.erase(name);
	value2name.erase(value);
	update(root, 1, 1'000'000'000, value, 0);
	return value;
}

string ranking() {
	int k; cin >> k;
	if (value2name.size() < k) return "None";
	return value2name[find(root, 1, 1'000'000'000, k)];
}

ll sum() {
	int k; cin >> k;
	return sum(root, 1, 1'000'000'000, 1, k);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T; cin >> T;
	for (int i = 0; i < T; i++) {
		string cmd; cin >> cmd;
		if (cmd == "init") {
			init();
		}
		if (cmd == "insert") {
			cout << insert() << endl;
		}
		if (cmd == "delete") {
			cout << remove() << endl;
		}
		if (cmd == "rank") {
			cout << ranking() << endl;
		}
		if (cmd == "sum") {
			cout << sum() << endl;
		}
	}
}