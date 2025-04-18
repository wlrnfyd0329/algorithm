#include <iostream>
#define endl "\n"

using namespace std;

int N;
int board[505][505];
int dp[505][505];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> N;
	for(int i = 1; i <= N; i++) {
		for(int j = 1; j <= i; j++) {
			cin >> board[i][j];
		}
	}
	dp[1][1] = board[1][1];
	for(int i = 1; i <= N; i++) {
		for(int j = 1; j <= i; j++) {
			dp[i + 1][j] = max(dp[i + 1][j], dp[i][j] + board[i + 1][j]);
			dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j] + board[i + 1][j + 1]);
		}
	}

	int ans = 0;
	for(int i = 1; i <= N; i++) {
		ans = max(ans, dp[N][i]);
	}
	cout << ans;
}