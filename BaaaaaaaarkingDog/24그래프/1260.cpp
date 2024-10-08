#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

int n, m, start;
vector<int> a[1005], da[1005];
bool bvis[1005], dvis[1005];

void dfs(int num) {
    stack<int> s;
    s.push(num);
    while(!s.empty()) {
        auto cur = s.top();
        s.pop();
        if(dvis[cur]) continue;
        cout << cur << " ";
        dvis[cur] = true;
        for(auto k : da[cur]) {
            if(dvis[k]) continue;
            s.push(k);
        }
    }
}

void bfs(int num) {
    queue<int> q;
    bvis[num] = true;
    q.push(num);
    while(!q.empty()) {
        auto cur = q.front();
        q.pop();
        cout << cur << " ";
        for(auto k : a[cur]) {
            if(bvis[k]) continue;
            bvis[k] = true;
            q.push(k);
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> start;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    for (int  i = 1; i <= n; i++) {
        sort(a[i].begin(), a[i].end());
        da[i] = a[i];
        reverse(da[i].begin(), da[i].end());
    }
    dfs(start);
    cout << "\n";
    bfs(start);
}