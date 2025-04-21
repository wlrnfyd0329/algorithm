// dp가 항상 모든 원래 배열 크기를 가질 필요는 없다.
// 새로 업데이트 시키면 적은 배열만으로도 해결할 수 있다.

#include <iostream>
#include <algorithm>
#define endl "\n"

using namespace std;

int N;
int board[100'005][3];
int new_vis[3][2]; // [2] : 최대, 최소
int old_vis[3][2];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> board[i][j];
		}
	}
	
	for (int i = 0; i < 3; i++) {
		old_vis[i][0] = old_vis[i][1] = board[1][i];
		new_vis[i][0] = 0;
		new_vis[i][1] = 0x3f3f3f3f;
	}

	for (int i = 2; i <= N; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = -1; k <= 1; k++) {
				if (j + k < 0 || j + k >= 3) continue;
				new_vis[j + k][0] = max(new_vis[j + k][0], old_vis[j][0] + board[i][j + k]);
				new_vis[j + k][1] = min(new_vis[j + k][1], old_vis[j][1] + board[i][j + k]);
			}
		}

		for(int j = 0; j < 3; j++) {
			old_vis[j][0] = new_vis[j][0];
			old_vis[j][1] = new_vis[j][1];
			new_vis[j][0] = 0;
			new_vis[j][1] = 0x3f3f3f3f;
		}
	}
	cout << max({ old_vis[0][0], old_vis[1][0], old_vis[2][0] }) << " " << min({ old_vis[0][1], old_vis[1][1], old_vis[2][1] });
}