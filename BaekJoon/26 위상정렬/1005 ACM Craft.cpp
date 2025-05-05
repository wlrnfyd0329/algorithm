// 위상 정렬을 사용하고 해당 시간의 최댓값을 저장해서 출력하면 되는 문제였다.
// 하나가 완성될 때까지 건물을 짓지 못하기에 최댓값을 출력해야 한다.

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#define X first
#define Y second
#define endl "\n"

using namespace std;

int N, K, W;
int cost[1005];
vector<int> indgree;
vector<int> ans;
vector<vector<int>> building;

void init() {
    cin >> N >> K;
    indgree = vector<int>(N + 1, 0);
    ans = vector<int>(N + 1, 0);
    building = vector<vector<int>>(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> cost[i];
    }
    for (int i = 0; i < K; i++) {
        int x, y; cin >> x >> y;
        indgree[y]++;
        building[x].push_back(y);
    }
    cin >> W;
}

int solve() {
    queue<int> q;
    for (int i = 1; i <= N; i++) {
        ans[i] = max(ans[i], cost[i]);
        if (!indgree[i]) q.push(i);
    }

    while (!q.empty()) {
        auto cur = q.front(); q.pop();

        if (cur == W) return ans[cur];

        for (auto nxt : building[cur]) {
            ans[nxt] = max(ans[nxt], ans[cur] + cost[nxt]);
            if (--indgree[nxt] == 0) {
                q.push(nxt);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        init();
        cout << solve() << endl;
    }
}