#include <iostream>
#include <vector>
#define endl "\n"

using namespace std;

vector<int> p;
vector<int> d;

int find(int x) {
    if (p[x] < 0) return x;
    // 아래 과정을 진행하여 p[x]의 거리를 최신화 시켜야 한다.
    // 계속 union만 한다면 d[p[x]]는 그냥 연결된 거리 밖에 없을 것이기 때문이다.
    int idx = find(p[x]);
    d[x] += d[p[x]];
    return p[x] = idx;
}

void uni(int u, int v) {
    d[u] = abs(u - v) % 1000;
    p[u] = v;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        int N; cin >> N;
        p = vector<int> (N + 1, -1);
        d = vector<int> (N + 1, 0);
        while(1) {
            char cmd; cin >> cmd;
            int i, j;
            if (cmd == 'E') {
                cin >> i;
                find(i);
                cout << d[i] << endl;
            }
            if (cmd == 'I') {
                cin >> i >> j;
                uni(i, j);
            }
            if (cmd == 'O') break;
        }
    }
}