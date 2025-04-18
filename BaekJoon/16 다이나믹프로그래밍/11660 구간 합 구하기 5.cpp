// 구간 합 구하는 DP

#include <iostream>
#define endl "\n"

using namespace std;

int N, M;
int board[1030][1030];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> M;
	for(int i = 1; i <= N; i++) {
		for(int j = 1; j <= N; j++) {
			cin >> board[i][j];
			board[i][j] += board[i][j - 1];
		}
	}
	
	while(M--) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		if (x1 == x2 && y1 == y2) cout << board[x2][y2] - board[x2][y2 - 1] << endl;
		else {
			int sum = 0;
			for(int i = x1; i <= x2; i++) {
				sum += board[i][y2] - board[i][y1 - 1];
			}
			cout << sum << endl;
		}
	}
}