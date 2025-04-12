// 산타의 선물 공장과 똑같은 문제 였다.

#include <iostream>

using namespace std;

int n, m;

struct Node {
	Node* nxt, * prv;
	int value;

	int query() {
		int a, b;
		a = prv->value == 0 ? -1 : prv->value;
		b = nxt->value == 0 ? -1 : nxt->value;
		return a + 2 * b;
	}
} node[100'005];

struct List {
	Node head;
	Node tail;
	int cnt = 0;

	void static link(Node* front, Node* back) {
		front->nxt = back;
		back->prv = front;
	}

	void init() {
		link(&head, &tail);
	}

	void erase(Node* node) {
		link(node->prv, node->nxt);
		cnt--;
	}

	bool empty() {
		return head.nxt == &tail;
	}

	void push_back(Node* node) {
		link(tail.prv, node);
		link(node, &tail);
		cnt++;
	}

	void push_front(Node* node) {
		link(node, head.nxt);
		link(&head, node);
		cnt++;
	}

	int move(List *dst) { // dst로 옮기기
		if (empty()) return dst->cnt;
		dst->cnt += cnt;
		cnt = 0;
		link(tail.prv, dst->head.nxt);
		link(&dst->head, head.nxt);
		init();
		return dst->cnt;
	}

	int exchange(List *dst) {
		if (empty() && dst->empty()) return 0;
		else if (empty()) {
			Node* target = dst->head.nxt;
			dst->erase(target);
			push_front(target);
		}
		else if (dst->empty()) {
			Node* target = head.nxt;
			erase(target);
			dst->push_front(target);
		}
		else {
			Node* src_target = head.nxt;
			Node* dst_target = dst->head.nxt;
			erase(src_target);
			dst->erase(dst_target);
			push_front(dst_target);
			dst->push_front(src_target);
		}
		return dst->cnt;
	}

	int split(List *dst) {
		Node* standard = &head;
		for (int i = 0; i < cnt / 2; i++) {
			standard = standard->nxt;
		}
		dst->cnt += cnt / 2;
		cnt -= cnt / 2;
		Node* nxt_standard = standard->nxt;
		link(standard, dst->head.nxt);
		link(&dst->head, head.nxt);
		link(&head, nxt_standard);
		return dst->cnt;
	}

	int query() {
		int a, b;
		if (empty()) {
			a = -1;
			b = -1;
		}
		else {
			a = head.nxt->value;
			b = tail.prv->value;
		}
		return a + 2 * b + 3 * cnt;
	}

} belt[100'005];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int q; cin >> q;
	while (q--) {
		int cmd, m_src, m_dst, num; cin >> cmd;
		if (cmd == 100) {
			cin >> n >> m;
			for (int i = 1; i <= n; i++) {
				belt[i].init();
			}
			for (int i = 1; i <= m; i++) {
				cin >> num;
				node[i].value = i;
				belt[num].push_back(&node[i]);
			}
		}
		if (cmd == 200) {
			cin >> m_src >> m_dst;
			cout << belt[m_src].move(&belt[m_dst]) << endl;
		}
		if (cmd == 300) {
			cin >> m_src >> m_dst;
			cout << belt[m_src].exchange(&belt[m_dst]) << endl;
		}
		if (cmd == 400) {
			cin >> m_src >> m_dst;
			cout << belt[m_src].split(&belt[m_dst]) << endl;
		}
		if (cmd == 500) {
			cin >> num;
			cout << node[num].query() << endl;
		}
		if (cmd == 600) {
			cin >> num;
			cout << belt[num].query() << endl;
		}
	}
}