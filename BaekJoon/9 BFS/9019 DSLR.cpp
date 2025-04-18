#include <iostream>
#include <cstring>
#include <string>
#include <queue>
#define endl "\n"

using namespace std;

int T, x, y;
int board[10005];
struct Node {
	int v;
	string s;
};

int D(int n) {
	return 2 * n % 10000;
}

int S(int n) {
	if (n == 0) return 9999;
	return n - 1;
}

int L(int n) {
	int num = n / 1000;
	n %= 1000;
	n *= 10;
	n += num;
	return n;
}

int R(int n) {
	int num = n % 10;
	n /= 10;
	n += num * 1000;
	return n;
}

void solve(int a, int b) {
	queue<Node> q;
	board[a] = 1;
	q.push({a, ""});

	while(!q.empty()) {
		Node cur = q.front(); q.pop();
		
		if (cur.v == b) {
			cout << cur.s << endl;
			return;
		}	

		if (!board[D(cur.v)]) {
			board[D(cur.v)] = 1;
			q.push({D(cur.v), cur.s + "D"});
		}
		if (!board[S(cur.v)]) {
			board[S(cur.v)] = 1;
			q.push({S(cur.v), cur.s + "S"});
		}
		if (!board[L(cur.v)]) {
			board[L(cur.v)] = 1;
			q.push({L(cur.v), cur.s + "L"});
		}
		if (!board[R(cur.v)]) {
			board[R(cur.v)] = 1;
			q.push({R(cur.v), cur.s + "R"});
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> T;
	for(int tc = 1; tc <= T; tc++) {
		memset(board, 0, sizeof(board));
		cin >> x >> y;
		solve(x, y);
	}
}