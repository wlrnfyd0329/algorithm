#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 987654321;
int n, m, x;
vector<pair<int, int>> come[1005];
vector<pair<int, int>> go[1005];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
int comed[1005];
int god[1005];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    fill(comed, comed+1005, INF);
    fill(god, god + 1005, INF);
    cin >> n >> m >> x;
    for(int i = 0; i < m; i++) {
        int s, e, t;
        cin >> s >> e >> t;
        come[s].push_back({t, e});
        go[e].push_back({t, s});
    }   
    comed[x] = 0;
    pq.push({comed[x], x});

    while(!pq.empty()) {
        auto cur = pq.top(); pq.pop();
        if (comed[cur.second] < cur.first) continue;
        for(auto k : come[cur.second]) {
            if (comed[k.second] <= k.first + comed[cur.second]) continue;
            comed[k.second] = k.first + comed[cur.second];
            pq.push(k);
        }
    }

    god[x] = 0;
    pq.push({god[x], x});

    while (!pq.empty())
    {
        auto cur = pq.top();
        pq.pop();
        if (god[cur.second] < cur.first)
            continue;
        for (auto k : go[cur.second])
        {
            if (god[k.second] <= k.first + god[cur.second])
                continue;
            god[k.second] = k.first + god[cur.second];
            pq.push(k);
        }
    }

    for(int i = 1; i <= n; i++) {
        comed[i] += god[i];
    }

    cout << *max_element(comed + 1, comed + n + 1);
    
}