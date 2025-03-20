#include <iostream>
#include <vector>
#define endl "\n"

using namespace std;

int T, n, k, m;
vector<int> p;

int find(int x) {
    if (p[x] < 0) {
        return x;
    }
    return p[x] = find(p[x]);
}

bool uni(int u, int v) {
    u = find(u);
    v = find(v);
    if (u == v) return false;
    if (p[u] < p[v]) swap(u, v);
    p[v] += p[u];
    //if (p[u] == p[v]) p[v]--;
    p[u] = v;
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        cout << "Scenario " << tc << ":" << endl;
        cin >> n;
        p = vector<int>(n, -1);
        cin >> k;
        for(int i = 0; i < k; i++) {
            int a, b;
            cin >> a >> b;
            uni(a, b);
        }
        cin >> m;
        for(int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            if (find(u) == find(v)) cout << 1 << endl;
            else cout << 0 << endl;
        }
        cout << endl;
    }
}