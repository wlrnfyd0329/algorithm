// LCA2 모르면 틀려야 함....

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int n, result;
int depth[100001];
int parent[100001];
vector<int> tree[100001];
vector<int> order;
int dist[100001];

void init() {
    result = 0;
    fill(depth, depth + 100000, 0);
    fill(dist, dist + 100000, 0);
    order.clear();
    for(int i = 1; i <= n; i++) {
        tree[i].clear();
    }
}

int visit(int index) {
    int start = order[index - 1];
    int end = order[index];
    if (depth[start] == depth[end]) {
        if (parent[start] == parent[end]) {
            return 2;
        }
        else {
            return dist[index - 1] + 1;
        }
    }
    else {
        if (start == parent[end]) {
            return 1;
        }
        else {
            return dist[index - 1] + 1;
        }
    }
}

void bfs() {
    queue<int> q;
    order.push_back(1);
    q.push(1);
    while(!q.empty()) {
        int pnt = q.front(); q.pop();
        for(auto k : tree[pnt]) {
            q.push(k);
            order.push_back(k);
            depth[k] = depth[pnt] + 1;
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        cin >> n;
        init();
        for(int i = 2; i <= n; i++) {
            int pnt;
            cin >> pnt;
            parent[i] = pnt;
            tree[pnt].push_back(i);
        }
        bfs();
        for(int i = 1; i < order.size(); i++) {
            dist[i] = visit(i);
            cout << order[i-1] << " " << order[i] << " " << dist[i] << "\n";
            result += dist[i];
        }
        cout << "#" << tc << " " << result << "\n";
    }
}