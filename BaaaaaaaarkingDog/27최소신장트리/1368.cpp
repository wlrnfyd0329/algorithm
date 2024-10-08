#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
#include <algorithm>

using namespace std;

int n, result, cnt;
vector<pair<int, int>> v[305];
bool chk[305];
priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq; // (간선 비용, 첫번째 간선 위치, 두번째 간선 위치)

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for(int i = 1; i <= n; i++) {
        int cost;
        cin >> cost;
        v[0].push_back({cost, i});
        v[i].push_back({cost, 0});
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            int cost;
            cin >> cost;
            if (cost != 0) {
                v[i].push_back({cost, j});
            }
        }
    }
    chk[0] = 1;
    for(auto cur : v[0]) {
        pq.push({cur.first, 0, cur.second});
    }
    while(cnt < n){
        int c, a, b;
        tie(c, a, b) = pq.top(); pq.pop();
        if (chk[b]) continue;
        chk[b] = true;
        cnt++;
        result += c;
        for(auto cur : v[b]) {
            pq.push({cur.first, b, cur.second});
        }
    }
    cout << result;
}

// 0번 노드를 만들어서 각 노드에 우물을 파는 것을 새로운 간선의 값으로 설정하는 것이 포인트이다.