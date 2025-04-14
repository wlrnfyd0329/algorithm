#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    
    for(int tc = 1; tc <= T; tc++) {
        int N, M, result = 0;
        vector<int> v[1005];
        int chk[1005];
        queue<int> q;
        fill(chk, chk + 1005, 0);
        cin >> N >> M;
        for(int i = 0; i < M; i++) {
            int a, b;
            cin >> a >> b;
            v[a].push_back(b);
            v[b].push_back(a);
        }

        chk[1] = 1;
        for(auto k : v[1]) {
            q.push(k);
        }
        while(!q.empty()) {
            auto cur = q.front(); q.pop();
            if(chk[cur]) continue;
            result++;
            chk[cur] = 1;
            for(auto k : v[cur]) {
                if (chk[k]) continue;
                q.push(k);
            }
        }
        cout << result << endl;
    }
}