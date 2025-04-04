#include <iostream>
#include <vector>
#include <string.h>
#define endl "\n"

using namespace std;

int N, L;
int p[300'005];

int find(int x) {
    if (p[x] <= 0) return x;
    return p[x] = find(p[x]);
}

bool uni(int u, int v) {
    u = find(u);
    v = find(v);
    if (u == v) {
        p[u] = 0;
        return false;
    }
    if (p[u] == 0 || p[v] == 0) {
        p[u] = 0;
        p[v] = 0;
        return false;
    }
        
    if (p[u] < p[v]) swap(u, v);
    if (p[u] == p[v]) p[v]--;
    p[u] = v;
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> L;
    memset(p, -1, sizeof(p));

    for(int i = 0; i < N; i++) {
        int a, b;
        cin >> a >> b;
        if (p[find(a)] == 0 && p[find(b)] == 0) cout << "SMECE" << endl;
        else {
            uni(a, b);
            cout << "LADICA" << endl;
        }
    }
}