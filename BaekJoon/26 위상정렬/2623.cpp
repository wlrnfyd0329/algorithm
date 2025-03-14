#include <iostream>
#include <queue>
#include <vector>

using namespace std;

vector<int> v[1005], result;
int indegree[1005];
queue<int> q;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    
    for(int i = 0; i < m; i++) {
        int cnt;
        cin >> cnt;
        int a;
        cin >> a;
        for(int j = 1; j < cnt; j++) {
            int b;
            cin >> b;
            v[a].push_back(b);
            indegree[b]++;
            a = b;
        }
    }

    for(int i = 1; i <= n; i++) {
        if (!indegree[i]) q.push(i);
    }

    while(!q.empty()) {
        auto cur = q.front(); q.pop();
        result.push_back(cur);
        for(auto k : v[cur]) {
            if(--indegree[k] == 0) q.push(k);
        }
    }

    if (result.size() == n) {
        for(auto k : result) {
            cout << k << endl;
        }
    }
    else {
        cout << 0;
    }

    
}   