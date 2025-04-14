#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Road {
    int cost;
    int st;
    int en;

    bool operator<(const Road &other) const {
        if (cost == other.cost) {
            if (st == other.st) return en > other.en;
            else return st > other.st;
        }
        return cost > other.cost;
    }
};

bool cmp(const Road &a, const Road &b) {
    if (a.cost == b.cost) {
        if (a.st == b.st) return a.en < b.en;
        else return a.st < b.st;
    }
    return a.cost < b.cost;
}

int n, m;
vector<Road> prim[100'005];
vector<Road> kruskal;
int vis[100'005];

int find(int x) {
    if (vis[x] < 0) {
        return x;
    }
    return vis[x] = find(vis[x]);
}

bool uni(int u, int v) {
    u = find(u);
    v = find(v);
    if (u == v) return false;
    if (vis[u] < vis[v]) swap(u, v);
    if (vis[u] == vis[v]) vis[v]--;
    vis[u] = v;
    return true;
}

void kruskal_algo() {
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        vis[i] = -1;
    }
    for(int i = 0; i < m; i++) {
        int st, en, cost;
        cin >> st >> en >> cost;
        kruskal.push_back({cost, st, en});
    }
    sort(kruskal.begin(), kruskal.end(), cmp);
    int cnt = 0;
    int total = 0;
    int maxcost = 0;
    for(int i = 0; i < m; i++) {
        Road road = kruskal[i];
        if (!uni(road.st, road.en)) continue;
        total += road.cost;
        maxcost = max(maxcost, road.cost);
        cnt++;
        if (cnt == n - 1) break;
    }

    cout << total - maxcost;
}

void prim_algo() {
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        vis[i] = 0;
    }
    for(int i = 0; i < m; i++) {
        int st, en, cost;
        cin >> st >> en >> cost;
        prim[st].push_back({cost, st, en});
        prim[en].push_back({cost, en, st});
    }

    priority_queue<Road> pq;
    vis[1] = 1;
    int cnt = 0;
    int total = 0;
    int maxcost = 0;
    for(auto nxt : prim[1]) {
        pq.push(nxt);
    }
    while(cnt < n - 1) {
        Road road =pq.top();
        pq.pop();
        if(vis[road.en]) continue;
        total += road.cost;
        maxcost = max(maxcost, road.cost);
        cnt++;
        vis[road.en] = 1;
        for(auto nxt : prim[road.en]) {
            if (vis[nxt.en]) continue;
            pq.push(nxt);
        }
    }
    cout << total - maxcost;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    //kruskal_algo();
    prim_algo();
}