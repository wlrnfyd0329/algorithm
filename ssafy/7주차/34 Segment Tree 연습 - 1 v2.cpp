#include <iostream>
#include <vector>
#include <algorithm>
#define endl "\n"

using namespace std;

int T, N, Q;
vector<int> arr;

struct Node {
	Node *left, *right;
	int max_v, min_v;
	Node() {
		left = right = nullptr;
		max_v = min_v = 0;
	}
} *root = new Node();

void init(Node *node, int start, int end) {
	if (start == end) {
		node->max_v = arr[start];
		node->min_v = arr[start];
		return;
	}
	int mid = (start + end) >> 1;
	if (!node->left) node->left = new Node();
	init(node->left, start, mid);
	if (!node->right) node->right = new Node();
	init(node->right, mid + 1, end);
	node->max_v = max(node->left->max_v, node->right->max_v);
	node->min_v = min(node->left->min_v, node->right->min_v);
}

void update(Node *node, int start, int end, int idx, int value) {
	if (!node) return;
	if (start == end) {
		node->max_v = value;
		node->min_v = value;
		return;
	}
	int mid = (start + end) >> 1;
	if (idx <= mid) {
		update(node->left, start, mid, idx, value);
	}
	else {
		update(node->right, mid + 1, end, idx, value);
	}
	node->max_v = max(node->left->max_v, node->right->max_v);
	node->min_v = min(node->left->min_v, node->right->min_v);
}

pair<int, int> query(Node *node, int start, int end, int left, int right) {
	if (!node || right < start || end < left) return { -1, 1'000'000'005 };
	if (left <= start && end <= right) return { node->max_v, node->min_v };
	int mid = (start + end) >> 1;
	pair<int, int> lf = query(node->left, start, mid, left, right);
	pair<int, int> rg = query(node->right, mid + 1, end, left, right);
	return { max(lf.first, rg.first), min(lf.second, rg.second) };
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cout << "#" << tc << " ";
		arr.clear();
		cin >> N >> Q;
		for (int i = 0; i < N; i++) {
			int num; cin >> num;
			arr.push_back(num);
		}

		init(root, 0, N - 1);

		while (Q--) {
			int cmd, a, b;
			cin >> cmd >> a >> b;
			if (cmd == 0) {
				update(root, 0, N - 1, a, b);
			}
			else {
				pair<int, int> node = query(root, 0, N - 1, a, b - 1);
				cout << node.first - node.second << " ";
			}
		}
		cout << endl;
	}
}