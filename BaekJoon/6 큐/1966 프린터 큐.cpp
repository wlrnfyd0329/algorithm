#include <iostream>
#include <queue>
#include <algorithm>
#define endl "\n"

using namespace std;

int T, n, m;
int important[105];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        cin >> n >> m;
        queue<int> q;
        for(int i = 0; i < n; i++) {
            cin >> important[i];
            q.push(i);
        }
        int cnt = 0;
        while(true) {
            int cur = q.front(); q.pop();

            bool isPrint = true;
            for(int i = 0; i < n; i++) {
                if (important[i] > important[cur]) {
                    q.push(cur);
                    isPrint = false;
                    break;;
                }
            }

            if (!isPrint) continue;
            important[cur] = 0;
            cnt++;
            if (cur == m) break;
        }
        cout << cnt << endl;
    }
}