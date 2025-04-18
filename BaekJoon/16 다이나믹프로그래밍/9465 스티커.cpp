#include <iostream>
#include <cstring>
#define endl "\n"

using namespace std;

int T;
int board[2][100'005];
int sum[2][100'005];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> T;
	for(int tc = 1; tc <= T; tc++) {
		int n, ans = 0;
		cin >> n;
		for(int i = 0; i < 2; i++) {
			for(int j = 0; j < n; j++) {
				int num; cin >> num;
				board[i][j] = num;
			}
		}
		memset(sum, 0, sizeof(sum));
		sum[0][0] = board[0][0];
		sum[1][0] = board[1][0];
		for(int j = 0; j < n; j++) {
			for(int i = 0; i < 2; i++) {
				sum[i][j + 1] = max(sum[i][j + 1], sum[!i][j] + board[i][j + 1]);
				sum[i][j + 2] = max(sum[i][j + 2], sum[!i][j] + board[i][j + 2]);
			}
		}
		for(int i = 0; i < 2; i++) {
			for(int j = n - 2; j < n; j++) {
				ans = max(ans, sum[i][j]);
			}
		}
		cout << ans << endl;
	}
}