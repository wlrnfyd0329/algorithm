#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int T, N;
int dist[20005];
int p[20005];

int find(int x) {
    if (p[x] < 0) {
        return x;
    }
    int idx = find(p[x]);
    dist[x] += dist[p[x]];
    return p[x] = idx;
}

void uni(int u, int v) {
    dist[u] = abs(u - v) % 1000;
    p[u] = v;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for (int tc = 1; tc <= T; tc++)
    {
        cin >> N;
        for(int i = 1; i <= N; i++) {
            p[i] = -1;
            dist[i] = 0;
        }
        while (true)
        {
            char cmd;
            int i, j;
            cin >> cmd;
            if (cmd == 'O')
            {
                break;
            }
            else if (cmd == 'E')
            {
                cin >> i;
                find(i);
                cout << dist[i] << "\n";
            }
            else
            {
                cin >> i >> j;
                uni(i, j);
            }
        }
    }
}