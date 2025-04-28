// n과 k가 같을 때를 생각하지 못했다.
// 방문을 시작할 때, 항상 처리를 잘해줘야 한다.

#include <iostream>
#include <queue>
#include <vector>
#define endl "\n"

using namespace std;

int n, k;
vector<int> sec (200'005, 0x3f3f3f3f);
vector<int> cnt (200'005, 0);

int dx[3] = {1, 1, 2};
int dy[3] = {-1, 1, 0};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k;
    queue<int> q;
    q.push(n);
    sec[n] = 0;
    cnt[n] = 1;
    while(!q.empty()) {
        auto cur = q.front(); q.pop();
        for(int i = 0; i < 3; i++) {
            int now = dx[i] * cur + dy[i];
            if (now < 0 || now > 200'000) continue;
            if (sec[now] > sec[cur] + 1) {
                sec[now] = sec[cur] + 1;
                cnt[now] = 1;
                q.push(now);
            }
            else if (sec[now] == sec[cur] + 1) {
                cnt[now]++;
                q.push(now);
            }
        }
    }
    cout << sec[k] << endl << cnt[k];
}