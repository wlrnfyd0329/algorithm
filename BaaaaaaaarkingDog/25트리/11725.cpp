#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, p[100005];;
vector<int> a[100005];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    queue<int> q;
    q.push(1);
    while(!q.empty()) {
        auto cur = q.front();
        q.pop();
        for(auto k : a[cur]) {
            if (k == p[cur]) continue;
            p[k] = cur;
            q.push(k);
        }
    }
    for(int i = 2; i <= n; i++) {
        cout << p[i] << "\n";
    }
}

