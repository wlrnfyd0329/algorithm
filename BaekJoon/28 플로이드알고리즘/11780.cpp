#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
int city[105][105];
int nxt[105][105];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    fill(city[0], &city[104][105], -1);
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        if (city[a][b] == -1) {
            city[a][b] = c;
        }
        else {
            city[a][b] = min(city[a][b], c);
        }
        nxt[a][b] = b;
    }

    for(int i = 1; i <= n; i++) {
        city[i][i] = 0;
    }

    for(int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                int fp = city[i][k];
                int sp = city[k][j];
                if (fp == -1 || sp == -1) continue;
                if (city[i][j] == -1) {
                    city[i][j] = fp + sp;
                    nxt[i][j] = nxt[i][k];
                }
                else {
                    if (city[i][j] > fp + sp) {
                        city[i][j] = fp + sp;
                        nxt[i][j] = nxt[i][k];
                    }
                }
            }
        }
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if (city[i][j] == -1) cout << "0 ";
            else cout << city[i][j] << " ";
        }
        cout << "\n";
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if (city[i][j] == -1 || city[i][j] == 0) {
                cout << "0\n";
                continue;
            }
            vector<int> v;
            int tmp = i;
            while(tmp != j) {
                v.push_back(tmp);
                tmp = nxt[tmp][j];
            }
            v.push_back(j);
            
            cout << v.size() << " ";
            for (auto k : v)
            {
                cout << k << " ";
            }
            cout << "\n";
        }
    }
}

// 포인트는 nxt[i][j] 가 nxt[i][k]로 가야한다는 것이다. 왜냐면 최단 경로는 반드시 k를 지나는 것은 확실하기 때문이다.
// 그리고 나중에 경로를 찾아갈때는 결국 j로 가야한 다는 것을 기억해야 한다.