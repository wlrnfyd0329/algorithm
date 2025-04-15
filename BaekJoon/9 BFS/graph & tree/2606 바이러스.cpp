#include <iostream>
#include <queue>
#include <vector>
#define endl "\n"

using namespace std;

int N, M;
bool vis[105];
vector<int> graph[105];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    for(int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    queue<int> q;
    vis[1] = 1;
    q.push(1);
    int cnt = 0;
    while(!q.empty()) {
        int cur = q.front(); q.pop();
        for(auto nxt : graph[cur]) {
            if(vis[nxt]) continue;
            vis[nxt] = true;
            q.push(nxt);
            cnt++;
        }
    }
    cout << cnt;
    
}