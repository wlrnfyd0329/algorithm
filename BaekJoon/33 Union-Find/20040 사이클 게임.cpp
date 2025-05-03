#include <iostream>
#include <algorithm>
#include <vector>
#define endl "\n"

using namespace std;

int n, m;
vector<int> p;

int find(int x) {
    if (p[x] < 0) return x;
    return p[x] = find(p[x]);
}

bool uni(int u, int v) {
    u = find(u);
    v = find(v);
    if (u == v) return false;
    if (p[u] < p[v]) swap(u, v);
    if (p[u] == p[v]) p[v]--;
    p[u] = v;
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    p = vector<int> (n, -1);
    for(int i = 1; i <= m; i++) {
        int s, e;
        cin >> s >> e;
        if (!uni(s, e)) {
            cout << i;
            return 0;
        }
    }

    cout << 0;
}