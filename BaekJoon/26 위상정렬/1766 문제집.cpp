#include <iostream>
#include <queue>
#include <vector>
#define endl "\n"

using namespace std;

int n, m;
int indgree[32005];
vector<int> tree[32005];
bool vis[32005];
priority_queue<int, vector<int>, greater<int>> pq;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        indgree[b]++;
        tree[a].push_back(b);
    }

    for(int i = 1; i <= n; i++) {
        if (!indgree[i]) pq.push(i);
    }

    while(!pq.empty()) {
        int cur = pq.top(); pq.pop();
        cout << cur << " ";
        for(int nxt : tree[cur]) {
            if (--indgree[nxt] == 0) {
                pq.push(nxt);
            }
        }
    }
}