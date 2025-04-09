// 트리 DP 문제로 각 트리에서 전파하는 힘이 어떻게 겹쳐서 같이 움직이는지 생각해서
// 테이블을 만들어야 한다.
// 어렵다.

#include <iostream>
#include <algorithm>
#define endl "\n"

using namespace std;

const int MAX = 100'005;
int N, Q;
int parent[MAX];
int power[MAX];
int isOFF[MAX];
int val[MAX]; // 각 채팅방의 알림을 받을 수 있는 채팅방 수 (자기 자신은 세면 안됨)
int chat[MAX][21]; // [각 채팅방 번호][내가 부모에 전파해야 되는 힘] = 전파해야 되는 채팅방 개수

void init() {
	for (int i = 1; i <= N; i++) {
		cin >> parent[i];
		isOFF[i] = false;
	}
	
	for (int i = 1; i <= N; i++) {
		cin >> power[i];
		power[i] = min(power[i], 20);
	}

	for (int i = 1; i <= N; i++) { // O(N) => 2,000,000
		int p = parent[i];
		chat[i][power[i]]++;
		for (int pwr = power[i] - 1; pwr >= 0; pwr--) {
			if (p == 0) break;
			chat[p][pwr]++;
			val[p]++; // 모든 채팅 수
			p = parent[p];
		}
	}
}

void alarm(int c) { // O(1) => 20 * 20 => 400
	if (isOFF[c]) { // 전파 금지 상태
		int p = parent[c];
		int num = 1;
		while (p) {
			for (int i = num; i <= 20; i++) {
				chat[p][i - num] += chat[c][i];
				val[p] += chat[c][i];
			}
			if (isOFF[p]) break;
			p = parent[p];
			num++;
		}
	}
	else { // 전파 허용 상태
		int p = parent[c];
		int num = 1;
		while (p) {
			for (int i = num; i <= 20; i++) {
				chat[p][i - num] -= chat[c][i];
				val[p] -= chat[c][i];
			}
			if (isOFF[p]) break;
			p = parent[p];
			num++;
		}
	}
	isOFF[c] = !isOFF[c];
}

void change_power(int c) { // O(1) => 20 + 20 => 40
	int new_pwr; cin >> new_pwr;
	new_pwr = min(new_pwr, 20);
	
	int p = parent[c];
	chat[c][power[c]]--;
	if (!isOFF[c]) {
		for (int pwr = power[c] - 1; pwr >= 0; pwr--) {
			if (p == 0) break;
			chat[p][pwr]--;
			val[p]--; // 모든 채팅 수
			if (isOFF[p]) break;
			p = parent[p];
		}
	}

	power[c] = new_pwr;

	p = parent[c];
	chat[c][power[c]]++;
	if (!isOFF[c]) {
		for (int pwr = power[c] - 1; pwr >= 0; pwr--) {
			if (p == 0) break;
			chat[p][pwr]++;
			val[p]++; // 모든 채팅 수
			if (isOFF[p]) break;
			p = parent[p];
		}
	}
}

void swap_parent(int c1) { // O(1) => 1,600 => 160,000,000
	int c2; cin >> c2;
	bool bef_isOFF1 = isOFF[c1];
	bool bef_isOFF2 = isOFF[c2];

	if (!isOFF[c1]) alarm(c1); // O(1) => 20 * 20 => 400
	if (!isOFF[c2]) alarm(c2); // O(1) => 20 * 20 => 400

	swap(parent[c1], parent[c2]);

	if (!bef_isOFF1) alarm(c1); // O(1) => 20 * 20 => 400
	if (!bef_isOFF2) alarm(c2); // O(1) => 20 * 20 => 400
}


void query(int c) { // O(1) => 1
	cout << val[c] << endl;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> Q;
	while (Q--) {
		int cmd, c; cin >> cmd;
		if (cmd == 100) init();
		else {
			cin >> c;
			if (cmd == 200) alarm(c);
			if (cmd == 300)	change_power(c);
			if (cmd == 400)	swap_parent(c);
			if (cmd == 500)	query(c);
		}
	}
}