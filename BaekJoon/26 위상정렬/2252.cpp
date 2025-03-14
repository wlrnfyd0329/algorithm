#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, m;
vector<int> a[32005], result;
int indegree[32005];
queue<int> q;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        a[u].push_back(v);
        indegree[v]++;
    }
    
    for(int i = 1; i <= n; i++) {
        if (indegree[i] == 0) q.push(i);
    }

    while(!q.empty()) {
        auto cur = q.front();
        q.pop();
        result.push_back(cur);
        for(auto k : a[cur]) {
            indegree[k]--;
            if (indegree[k] == 0) q.push(k);
        }
    }

    for(auto k : result) {
        cout << k << " ";
    }
}