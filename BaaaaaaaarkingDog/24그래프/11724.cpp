#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

/* BFS 풀이
int n, m, cnt;
bool vis[1005];
vector<int> a[1005];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    for(int i = 0; i < m; i++){
        int u,v;
        cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    queue<int> q;
    for(int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        vis[i] = true;
        q.push(i);
        while(!q.empty()) {
            auto cur = q.front();
            q.pop();
            for (auto k : a[cur])
            {
                if (vis[k]) continue;
                vis[k] = true;
                q.push(k);
            }
        }
        cnt++;
    }
    cout << cnt;
}
*/

/* DFS 비재귀 풀이
int n, m, cnt;
bool vis[1005];
vector<int> a[1005];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    stack<int> s;
    for(int i = 1; i <= n; i++) {
        if(vis[i]) continue;
        vis[i] = true;
        s.push(i);
        while(!s.empty()) {
            auto cur = s.top();
            s.pop();
            for(auto k : a[cur]) {
                if (vis[k]) continue;
                vis[k] = true;
                s.push(k);
            }
        }
        cnt++;
    }
    cout << cnt;
}
*/

// DFS 재귀 풀이
int n, m, cnt;
bool vis[1005];
vector<int> a[1005];

void dfs(int cur) {
    vis[cur] = true;
    for(auto k : a[cur]) {
        if(vis[k]) continue;
        dfs(k);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    for(int i = 1; i <= n; i++) {
        if(vis[i]) continue;
        dfs(i);
        cnt++;
    }
    cout << cnt;
}