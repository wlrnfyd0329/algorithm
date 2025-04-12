// empty인 경우 고려 안해줬다.
// W 범위를 잘 못 봐서 더했을 때, long long을 안해줬다.
// 제일 앞에 있는 박스는 앞으로 당겨올 필요가 없는데 고려를 안해줬다.
// List 구현시 항상 포인터를 넘겨줘야지 제대로 값이 담긴다.
// init, insert, erase, empty, link는 항상 구현하자

#include <iostream>
#include <unordered_map>
#define endl "\n"

using namespace std;

int n, m;

int p[15];

int find(int x) {
	if (p[x] == x) return x;
	return p[x] = find(p[x]);
}

struct Node {
	Node* nxt, *prv;
	int id;
	int w;
	int belt;
} box[100'005];

unordered_map<int, Node*> table;

struct List {
	Node head;
	Node tail;
	bool isBroken = false;

	void static link(Node* front, Node* back) {
		front->nxt = back;
		back->prv = front;
	}

	void init() {
		link(&head, &tail);
	}

	void insert(Node *node) { // 뒤로 집어넣기
		link(tail.prv, node);
		link(node, &tail);
	}

	void static erase(Node *node) {
		link(node->prv, node->nxt);
	}

	bool empty() {
		return head.nxt == &tail;
	}

	int get(int w_max) {
		if (empty()) return 0;
		Node *target = head.nxt;
		if (target->w <= w_max) {
			table.erase(target->id);
			erase(head.nxt);
			return target->w;
		}
		else {
			erase(target);
			insert(target);
			return 0;
		}
	}

	void check(Node *node) {
		if (node == head.nxt) return;
		link(tail.prv, head.nxt);
		link(node->prv, &tail);
		link(&head, node);
	}

	void move(List *list) {
		isBroken = true;
		if (empty()) return;
		link(list->tail.prv, head.nxt);
		link(tail.prv, &list->tail);
		init();
	}

} belt[15];

void create() { // n개의 물건, m개의 벨트, 정확한 n/m의 물건
	cin >> n >> m;
	int cnt = n / m;
	for (int i = 0; i < n; i++) {
		cin >> box[i].id;
		table[box[i].id] = &box[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> box[i].w;
	}
	for (int i = 1; i <= m; i++) {
		p[i] = i;
		belt[i].init();
	}

	int belt_idx = 1;
	int box_idx = 0;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n / m; j++) {
			box[box_idx].belt = belt_idx;
			belt[belt_idx].insert(&box[box_idx++]);
		}
		belt_idx++;
	}
}

void get_off() { // 맨 앞에 w_max보다 적다면 하차, 아니면 뒤로 보내기, 하차된 상자 무게 출력
	int w_max; cin >> w_max;
	long long sum = 0;
	for (int i = 1; i <= m; i++) {
		if (belt[i].isBroken) continue;
		sum += belt[i].get(w_max);
	}
	cout << sum << endl;
}

void remove_stuff() { // r_id 삭제 있으면 r_id, 없으면 -1 삭제하고 뒤에 앞으로 당겨옴
	int r_id; cin >> r_id;
	if (table.find(r_id) == table.end()) {
		cout << -1 << endl;
		return;
	}
	List::erase(table[r_id]);
	table.erase(r_id);
	cout << r_id << endl;
}

void check_stuff() { // f_id 주어짐 해당하는 상자가 놓여있는 벨트의 번호를 출력, 없으면 -1, 상자가 있을 때, 해당 상자 위에 있는 상자를 모두 앞으로 가져옴. 
	int f_id; cin >> f_id;
	if (table.find(f_id) == table.end()) {
		cout << -1 << endl;
		return;
	}
	belt[find(table[f_id]->belt)].check(table[f_id]);
	cout << find(table[f_id]->belt) << endl; 
}

void belt_error() { // 벨트가 고장나면 다시는 사용할 수 없게 됨. b_num의 오른쪽 벨트 부터 보면서 상자를 아래부터 하나씩 옮겨줌. 망가져있으면 -1, 정상적으로는 b_num
	int b_num; cin >> b_num;
	int n_num = b_num;
	if (belt[b_num].isBroken) {
		cout << -1 << endl;
		return;
	}
	while (1) {
		if (++n_num > m) n_num = 1;
		if (belt[n_num].isBroken) continue;
		p[b_num] = n_num;
		belt[b_num].move(&belt[n_num]);
		cout << b_num << endl;
		break;
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int q; cin >> q; // 10만번, n = 100,000
	while (q--) {
		int cmd; cin >> cmd;
		if (cmd == 100) create();
		else if (cmd == 200) get_off();
		else if (cmd == 300) remove_stuff();
		else if (cmd == 400) check_stuff();
		else if (cmd == 500) belt_error();
	}
}