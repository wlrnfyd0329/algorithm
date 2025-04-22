// 유명한 knapsack 문제다.

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N, K;
struct Thing {
	int w;
	int v;
};
vector<Thing> things;
int dp[105][100'005];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
	cin >> N >> K;
	things = vector<Thing> (N + 1);
	for (int i = 1; i <= N; i++) {
		int w, v;
		cin >> w >> v;
		things[i] = {w, v};
	}

	for(int n = 1; n <= N; n++) {
		for(int w = 0; w <= K; w++) {
			if (w < things[n].w) dp[n][w] = dp[n - 1][w];
			else dp[n][w] = max(dp[n - 1][w], dp[n - 1][w - things[n].w] + things[n].v);
		}
	}

	cout << dp[N][K];
}