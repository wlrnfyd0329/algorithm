// union-find로 그룹을 만들고
// knapsack 알고리즘으로 K값으로 가질 수 있는 최대 값을 구한다

#include <iostream>
#include <algorithm>
#include <vector>
#define endl "\n"

using namespace std;

int N, M, K, ans_cnt, ans_pcnt;
int p[30005];

struct Node
{
    int person_cnt = 1;
    int candy_cnt;
} cnt[30005];

vector<Node> group;

int dp[30005][3005];

int find(int x) {
    if (p[x] < 0) return x;
    return p[x] = find(p[x]);
}

bool uni(int u, int v) {
    u = find(u);
    v = find(v);
    if (u == v) return false;
    if (p[u] < p[v]) swap(u, v);
    if (p[u] == p[v]) p[v]--;
    cnt[v].candy_cnt += cnt[u].candy_cnt;
    cnt[v].person_cnt += cnt[u].person_cnt;
    p[u] = v;
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ans_cnt = ans_pcnt = 0;
    cin >> N >> M >> K;
    for(int i = 1; i <= N; i++) {
        cin >> cnt[i].candy_cnt;
        p[i] = -1;
    }

    for(int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        uni(a, b);
    }

    group.push_back({});
    for(int i = 1; i <= N; i++) {
        if (p[i] < 0) {
            group.push_back(cnt[i]);
        }
    }

    for(int i = 1; i < group.size(); i++) {
        for(int j = 1; j < K; j++) {
            if (j >= group[i].person_cnt) dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - group[i].person_cnt] + group[i].candy_cnt);
            else dp[i][j] = dp[i - 1][j];
        }
    }

    cout << dp[group.size() - 1][K - 1];
}